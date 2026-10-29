/*
  ============================================================================
   XIAO HEFTIG SYNTH  —  voor de Seeed XIAO MIDI Synthesizer
                         (XIAO ESP32-C3 + SAM2695 General MIDI-chip)
  ============================================================================

  De synthstukken zijn gewone C++. De XIAO Flitser compileert ze in de browser
  naar bytecode; de ESP32-C3 voert die uit met de VM in vm.h en stuurt MIDI
  naar de SAM2695, die het afspeelt via zijn DAC op de stereo-jack en speaker.

  Ingebouwd (voorbeelden.h): 3 techno, 12 complexe algoritmische stukken en
  256 bytebeats. Eigen stukken staan in /synth als naam.cpp + naam.sbc; een
  eigen stuk met de naam van een ingebouwd stuk gaat daarvoor.

  Bij het opstarten speelt een DEMO: alle stukken achter elkaar, elk 'maten'
  maten lang, heftig beginnend met techno.

  ---------------------------------------------------------------------------
  AANSLUITINGEN (op het bord al bedraad, behalve DIN-MIDI in)
  ---------------------------------------------------------------------------
    D6  / GPIO21   UART TX  -> SAM2695 MIDI in (31250 baud)
    D7  / GPIO20   UART RX  <- DIN-MIDI in, via optocoupler (6N138/H11L1)
    D3  / GPIO5    knop A  -> vorige stuk
    D2  / GPIO4    knop B  -> volgende stuk  (1,2 s vasthouden = demo)
    D1  / GPIO3    knop C  -> luider         (vasthouden = herhalen)
    D0  / GPIO2    knop D  -> zachter
    USB            seriële poort: XIAO Flitser (115200)

  ---------------------------------------------------------------------------
  USB-PROTOCOL (tekstregels, eindigen op \n)
  ---------------------------------------------------------------------------
    INFO                 -> OK <versie> <stuk> <volume> <demo 0/1>
    LS                   -> F <naam> <grootte> <v|u|a> ... OK
                            (v = ingebouwd, u = eigen, a = aangepast ingebouwd)
    GET <naam>           -> DATA <lengte>\n<C++-bron>\nOK
    PUT <naam>.cpp <len>\n<bytes>   -> OK
    PUT <naam>.sbc <len>\n<bytes>   -> OK  of  ERR 0 <melding>
    PLAY <naam>          -> OK  of  ERR <regel> <melding>
    DEL <naam> | STOP | DEMO | VOL <0..127>   -> OK
    Meldingen beginnen met '# ': SPEELT, FOUT <naam> regel <n> <tekst>, PRINT <naam> <waarde>
  ============================================================================
*/

#include <Arduino.h>
#include <LittleFS.h>
#include <vector>
#include <algorithm>
#include "vm.h"
#include "voorbeelden.h"

#define VERSIE "heftig-c3-2"

// ------------------------------------------------------------------ pinnen --
const int MIDI_TX = 21;                 // D6 -> SAM2695
const int MIDI_RX = 20;                 // D7 <- DIN-MIDI
enum Functie { VORIGE, VOLGENDE, LUIDER, ZACHTER };
const int KNOP_PIN[4]         = { 5, 4, 3, 2 };
const Functie KNOP_FUNCTIE[4] = { VORIGE, VOLGENDE, LUIDER, ZACHTER };
const char *const FUNCTIE_NAAM[4] = { "vorige", "volgende", "luider", "zachter" };

const char *MAP = "/synth";

// ---------------------------------------------------------------- toestand --
muziek::Muziek mz;
vm::Machine machine;
std::vector<String> namen;              // alle stukken: ingebouwd (demovolgorde), dan eigen
int huidig = -1;
bool speelt = false;
bool demo = true;
uint8_t volume = 100;
uint32_t stapNr = 0;
uint32_t volgendeStapUs = 0;

// ------------------------------------------------------------- meldingen ----
void meld(const String &s) { if (Serial) { Serial.print("# "); Serial.println(s); } }

// ------------------------------------------------------------------- MIDI ---
static void midiUit(const uint8_t *b, int n) { Serial0.write(b, n); }
static void printUit(int32_t v) {
  meld("PRINT " + (huidig >= 0 && huidig < (int)namen.size() ? namen[huidig] : String("-")) + " " + String((long)v));
}

void zetVolume(int v) {
  volume = (uint8_t)(v < 0 ? 0 : v > 127 ? 127 : v);
  const uint8_t mv[] = { 0xF0, 0x7F, 0x7F, 0x04, 0x01, 0x00, volume, 0xF7 };   // GM master volume
  Serial0.write(mv, sizeof mv);
}

void gmReset() {
  const uint8_t gm[] = { 0xF0, 0x7E, 0x7F, 0x09, 0x01, 0xF7 };                   // GM System On
  Serial0.write(gm, sizeof gm);
  Serial0.flush();
  delay(60);
  zetVolume(volume);
}

// --------------------------------------------------------------- bestanden --
bool geldigeNaam(const String &n) {
  if (n.length() < 1 || n.length() > 31) return false;
  for (size_t i = 0; i < n.length(); i++) {
    char c = n[i];
    if (!(isalnum((unsigned char)c) || c == '_' || c == '-')) return false;
  }
  return true;
}
String basis(String n) {
  if (n.endsWith(".cpp") || n.endsWith(".sbc")) n.remove(n.length() - 4);
  return n;
}
String pad(const String &n, const char *ext) { return String(MAP) + "/" + n + ext; }
int ingebouwdIndex(const String &n) {
  for (int i = 0; i < N_INGEBOUWD; i++) if (n == INGEBOUWD[i].naam) return i;
  return -1;
}
bool eigenBestaat(const String &n, const char *ext) { return LittleFS.exists(pad(n, ext)); }

void leesNamen() {
  namen.clear();
  for (int i = 0; i < N_INGEBOUWD; i++) namen.push_back(INGEBOUWD[i].naam);
  std::vector<String> eigen;
  File d = LittleFS.open(MAP);
  if (d && d.isDirectory()) {
    for (File f = d.openNextFile(); f; f = d.openNextFile()) {
      String n = f.name();
      int slash = n.lastIndexOf('/');
      if (slash >= 0) n = n.substring(slash + 1);
      if (!f.isDirectory() && n.endsWith(".sbc")) {
        n = basis(n);
        if (geldigeNaam(n) && ingebouwdIndex(n) < 0) eigen.push_back(n);
      }
    }
  }
  std::sort(eigen.begin(), eigen.end(), [](const String &a, const String &b) { return a < b; });
  for (auto &n : eigen) namen.push_back(n);
}

bool leesBytes(const String &p, std::vector<uint8_t> &uit) {
  File f = LittleFS.open(p, "r");
  if (!f) return false;
  uit.resize(f.size());
  size_t n = f.read(uit.data(), uit.size());
  f.close();
  return n == uit.size();
}

static int b64waarde(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= 'a' && c <= 'z') return c - 'a' + 26;
  if (c >= '0' && c <= '9') return c - '0' + 52;
  if (c == '+') return 62;
  if (c == '/') return 63;
  return -1;
}
void base64(const char *s, std::vector<uint8_t> &uit) {
  uit.clear();
  uint32_t acc = 0; int bits = 0;
  for (; *s; s++) {
    int v = b64waarde(*s);
    if (v < 0) continue;
    acc = (acc << 6) | (uint32_t)v; bits += 6;
    if (bits >= 8) { bits -= 8; uit.push_back((uint8_t)(acc >> bits)); }
  }
}

// de bytecode van een stuk: eigen bestand gaat voor ingebouwd
bool bytecodeVan(const String &n, std::vector<uint8_t> &bc) {
  if (eigenBestaat(n, ".sbc")) return leesBytes(pad(n, ".sbc"), bc);
  int i = ingebouwdIndex(n);
  if (i < 0) return false;
  base64(INGEBOUWD[i].bytecode64, bc);
  return bc.size() == INGEBOUWD[i].lengte;
}

// ------------------------------------------------------------- afspelen -----
String foutTekst() { return String(machine.foutRegel) + " " + machine.fout.c_str(); }

// laadt en start een stuk; geeft "" of "<regel> <melding>"
String speel(const String &naam) {
  std::vector<uint8_t> bc;
  if (!geldigeNaam(naam) || !bytecodeVan(naam, bc)) return "0 stuk niet gevonden";
  speelt = false;
  mz.allesUit();
  for (size_t i = 0; i < namen.size(); i++) if (namen[i] == naam) huidig = (int)i;
  mz.seed(esp_random());
  gmReset();
  if (!machine.laad(bc.data(), bc.size()) || !machine.start()) { mz.allesUit(); return foutTekst(); }
  if (machine.g(vm::G_VOL) != 100) zetVolume(machine.g(vm::G_VOL));
  machine.g(vm::G_VOL) = volume;
  stapNr = 0;
  volgendeStapUs = micros();
  speelt = true;
  meld("SPEELT " + naam);
  return "";
}

void speelIndex(int i) {
  if (namen.empty()) return;
  int n = (int)namen.size();
  for (int poging = 0; poging < n; poging++) {
    huidig = (((i + poging) % n) + n) % n;
    String f = speel(namen[huidig]);
    if (!f.length()) return;
    meld("FOUT " + namen[huidig] + " regel " + f);
    if (!demo) return;
  }
}

void stop() { speelt = false; mz.allesUit(); }

int32_t klem(int32_t v, int32_t lo, int32_t hi) { return v < lo ? lo : v > hi ? hi : v; }

uint32_t stapDuurUs(uint32_t t) {
  uint32_t basisUs = 15000000UL / (uint32_t)klem(machine.g(vm::G_BPM), 20, 400);
  int32_t sw = (int32_t)basisUs * klem(machine.g(vm::G_SWING), 0, 60) / 200;
  return (t & 1) ? basisUs - sw : basisUs + sw;
}

void afspelen() {
  if (!speelt) return;
  uint32_t nu = micros();
  if ((int32_t)(nu - volgendeStapUs) < 0) return;
  if ((int32_t)(nu - volgendeStapUs) > 500000) volgendeStapUs = nu;     // niet inhalen na een pauze

  if (demo && (stapNr & 15) == 0 && (int32_t)(stapNr >> 4) >= klem(machine.g(vm::G_MATEN), 1, 1000)) {
    speelIndex(huidig + 1);
    return;
  }
  machine.g(vm::G_VOL) = volume;
  if (!machine.stap(stapNr)) {
    meld("FOUT " + namen[huidig] + " regel " + foutTekst());
    stop();
    if (demo) speelIndex(huidig + 1);
    return;
  }
  if (machine.g(vm::G_VOL) != volume) zetVolume(machine.g(vm::G_VOL));
  volgendeStapUs += stapDuurUs(stapNr);
  stapNr++;
}

// ------------------------------------------------------------- DIN-MIDI in --
struct { uint8_t status, d[2], n; bool sysex; } din;

static inline uint8_t dataLen(uint8_t st) { uint8_t t = st & 0xF0; return (t == 0xC0 || t == 0xD0) ? 1 : 2; }

void dinByte(uint8_t b) {
  if (b >= 0xF8) return;                               // clock e.d. niet doorgeven
  if (din.sysex) {
    if (!(b & 0x80)) { Serial0.write(b); return; }
    Serial0.write(0xF7);
    din.sysex = false;
    if (b == 0xF7) return;
  }
  if (b == 0xF0) { din.sysex = true; din.status = 0; Serial0.write(b); return; }
  if (b & 0x80) { din.status = b < 0xF0 ? b : 0; din.n = 0; return; }
  if (!din.status) return;
  din.d[din.n++] = b;
  if (din.n < dataLen(din.status)) return;
  din.n = 0;
  uint8_t msg[3] = { din.status, din.d[0], din.d[1] };
  Serial0.write(msg, 1 + dataLen(din.status));        // thru naar de SAM2695
  if ((din.status & 0xF0) == 0x90 && din.d[1] > 0 && machine.isGeladen()) machine.g(vm::G_NOOTIN) = din.d[0];
}

// --------------------------------------------------------------- knoppen ----
struct Knop { bool neer; uint32_t sinds, ingedrukt, herhaald; bool lang; };
Knop knop[4];

void doeFunctie(Functie f) {
  switch (f) {
    case VORIGE:   demo = false; speelIndex(huidig - 1); break;
    case VOLGENDE: demo = false; speelIndex(huidig + 1); break;
    case LUIDER:   zetVolume(volume + 8); meld("volume " + String(volume)); break;
    case ZACHTER:  zetVolume(volume - 8); meld("volume " + String(volume)); break;
  }
}

void knoppen() {
  uint32_t nu = millis();
  for (int i = 0; i < 4; i++) {
    Knop &k = knop[i];
    bool neer = digitalRead(KNOP_PIN[i]) == LOW;
    if (neer != k.neer && nu - k.sinds > 25) {
      k.neer = neer; k.sinds = nu;
      if (neer) {
        k.ingedrukt = k.herhaald = nu; k.lang = false;
        meld("knop GPIO" + String(KNOP_PIN[i]) + ": " + FUNCTIE_NAAM[KNOP_FUNCTIE[i]]);
        doeFunctie(KNOP_FUNCTIE[i]);
      }
    }
    if (k.neer) {
      Functie f = KNOP_FUNCTIE[i];
      if ((f == LUIDER || f == ZACHTER) && nu - k.ingedrukt > 400 && nu - k.herhaald > 120) { k.herhaald = nu; doeFunctie(f); }
      if (f == VOLGENDE && !k.lang && nu - k.ingedrukt > 1200) { k.lang = true; demo = true; meld("demo"); speelIndex(0); }
    }
  }
}

// ------------------------------------------------------------- USB-protocol -
String regel;

bool ontvang(uint8_t *buf, size_t n, uint32_t ms) {
  size_t got = 0;
  uint32_t t0 = millis();
  while (got < n) {
    int c = Serial.read();
    if (c >= 0) { buf[got++] = (uint8_t)c; t0 = millis(); continue; }
    if (millis() - t0 > ms) return false;
    afspelen();                                          // de muziek loopt door tijdens het ontvangen
    delay(1);
  }
  return true;
}

void antwoord(const String &s) { Serial.println(s); }

void stuurData(const uint8_t *d, size_t n) {
  Serial.print("DATA " + String((unsigned long)n) + "\n");
  for (size_t o = 0; o < n; o += 256) {
    Serial.write(d + o, std::min((size_t)256, n - o));
    afspelen();
  }
  Serial.print("\nOK\n");
}

void commando(String c) {
  c.trim();
  int sp = c.indexOf(' ');
  String cmd = sp < 0 ? c : c.substring(0, sp);
  String arg = sp < 0 ? "" : c.substring(sp + 1);
  cmd.toUpperCase();

  if (cmd == "INFO") {
    antwoord("OK " VERSIE " " + (huidig >= 0 && huidig < (int)namen.size() ? namen[huidig] : String("-")) +
             " " + String(volume) + " " + String(demo ? 1 : 0));
  } else if (cmd == "LS") {
    leesNamen();
    for (auto &n : namen) {
      int ib = ingebouwdIndex(n);
      bool eigen = eigenBestaat(n, ".cpp");
      size_t grootte = 0;
      if (eigen) { File f = LittleFS.open(pad(n, ".cpp"), "r"); if (f) { grootte = f.size(); f.close(); } }
      else if (ib >= 0) grootte = strlen(INGEBOUWD[ib].bron);
      antwoord("F " + n + " " + String((unsigned long)grootte) + " " + (ib < 0 ? "u" : eigen ? "a" : "v"));
      afspelen();
    }
    antwoord("OK");
  } else if (cmd == "GET") {
    String n = basis(arg);
    std::vector<uint8_t> d;
    if (geldigeNaam(n) && eigenBestaat(n, ".cpp") && leesBytes(pad(n, ".cpp"), d)) { stuurData(d.data(), d.size()); return; }
    int ib = geldigeNaam(n) ? ingebouwdIndex(n) : -1;
    if (ib < 0) { antwoord("ERR 0 stuk niet gevonden"); return; }
    stuurData((const uint8_t *)INGEBOUWD[ib].bron, strlen(INGEBOUWD[ib].bron));
  } else if (cmd == "PUT") {
    int sp2 = arg.lastIndexOf(' ');
    String bestand = arg.substring(0, sp2);
    long len = arg.substring(sp2 + 1).toInt();
    bool isCpp = bestand.endsWith(".cpp"), isSbc = bestand.endsWith(".sbc");
    String n = basis(bestand);
    if (sp2 < 0 || len <= 0 || len > 65535) { antwoord("ERR 0 ongeldige lengte (max 64 KB)"); return; }
    std::vector<uint8_t> buf(len);
    // altijd eerst alle aangekondigde bytes lezen, anders raakt het protocol uit de pas
    if (!ontvang(buf.data(), len, 3000)) { antwoord("ERR 0 ontvangst afgebroken"); return; }
    if (!(isCpp || isSbc) || !geldigeNaam(n)) {
      antwoord("ERR 0 ongeldige naam (naam.cpp of naam.sbc, letters/cijfers/_/-, max 31 tekens)");
      return;
    }
    if (isSbc) {                                         // eerst controleren, dan pas opslaan
      vm::Machine proef;
      muziek::Muziek stil;
      proef.mz = &stil;
      if (!proef.laad(buf.data(), len)) { antwoord("ERR " + String(proef.foutRegel) + " " + proef.fout.c_str()); return; }
    }
    LittleFS.mkdir(MAP);
    File f = LittleFS.open(pad(n, isCpp ? ".cpp" : ".sbc"), "w");
    if (!f) { antwoord("ERR 0 kan niet schrijven"); return; }
    size_t w = f.write(buf.data(), len);
    f.close();
    if (w != (size_t)len) { antwoord("ERR 0 geheugen vol"); return; }
    leesNamen();
    antwoord("OK");
  } else if (cmd == "PLAY") {
    leesNamen();
    demo = false;
    String f = speel(basis(arg));
    antwoord(f.length() ? "ERR " + f : "OK");
  } else if (cmd == "DEL") {
    String n = basis(arg);
    if (!geldigeNaam(n)) { antwoord("ERR 0 ongeldige naam"); return; }
    bool weg = LittleFS.remove(pad(n, ".cpp"));
    weg = LittleFS.remove(pad(n, ".sbc")) || weg;
    leesNamen();
    antwoord(weg ? "OK" : "ERR 0 geen eigen bestand met die naam");
  } else if (cmd == "STOP") {
    demo = false; stop(); antwoord("OK");
  } else if (cmd == "DEMO") {
    demo = true; speelIndex(0); antwoord("OK");
  } else if (cmd == "VOL") {
    zetVolume(arg.toInt()); antwoord("OK");
  } else if (cmd.length()) {
    antwoord("ERR 0 onbekend commando " + cmd);
  }
}

void usb() {
  while (Serial.available()) {
    char ch = (char)Serial.read();
    if (ch == '\n') { String c = regel; regel = ""; commando(c); }
    else if (ch != '\r' && regel.length() < 200) regel += ch;
  }
}

// ----------------------------------------------------------------- setup ----
void setup() {
  Serial.setRxBufferSize(4096);
  Serial.begin(115200);
  Serial.setTxTimeoutMs(0);                              // nooit blokkeren zonder USB-host

  Serial0.setTxBufferSize(1024);
  Serial0.begin(31250, SERIAL_8N1, MIDI_RX, MIDI_TX);

  for (int i = 0; i < 4; i++) pinMode(KNOP_PIN[i], INPUT_PULLUP);

  mz.midi = midiUit;
  machine.mz = &mz;
  machine.print = printUit;

  delay(300);                                            // SAM2695 laten opstarten
  if (!LittleFS.begin(true)) meld("bestandssysteem niet beschikbaar");
  LittleFS.mkdir(MAP);
  leesNamen();

  meld("XIAO Heftig Synth " VERSIE " — " + String(N_INGEBOUWD) + " ingebouwde stukken, " +
       String((int)namen.size() - N_INGEBOUWD) + " eigen");
  demo = true;
  speelIndex(0);
}

void loop() {
  usb();
  while (Serial0.available()) dinByte((uint8_t)Serial0.read());
  knoppen();
  afspelen();
}
