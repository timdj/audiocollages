// voorbeelden.h — GEGENEREERD door maak_voorbeelden.js, niet met de hand aanpassen.
// 271 ingebouwde voorbeelden in demovolgorde: C++-bron + bytecode (base64).
// Een eigen bestand in /synth met dezelfde naam gaat voor het ingebouwde.
#pragma once
#include <cstdint>

struct Ingebouwd { const char *naam; const char *bron; const char *bytecode64; uint16_t lengte; };

static const Ingebouwd INGEBOUWD[] = {
  { "techno_1_industrieel", R"SYN(// TECHNO 1 — INDUSTRIEEL, 145 BPM
// Harde kick met rommel, metalen hats, ratelende snares en orkeststoten.
// Bouwt op in blokken van 8 maten, met een breakdown in maat 24-27.

constexpr int BAS = 31;                       // G1
const char *KICK  = "x...x...x...x..x";
const char *HATS  = "..x.x.x...x.x.xx";
const char *SNARE = "....x.......x.x.";
const char *BASLIJN[4] = { "..0..0..0..0..07", "..0..0..3..0..5.",
                           "..0..0..0..0.a.7", "..C..0..0..0..07" };

void start() {
  bpm = 145;
  maten = 32;
  instrument(10, 16);                         // power-drumkit
  instrument(2, 38);                          // synth bass 1
  instrument(3, 55);                          // orchestra hit
  instrument(4, 102);                         // FX: echo drops
  instrument(5, 30);                          // distortion guitar
  cc(2, 91, 10);
  cc(3, 91, 90);
  cc(4, 91, 110);
  cc(5, 91, 40);
}

void stap() {
  int sectie = m / 8;
  bool breakdown = m >= 24 && m < 28;
  if (!breakdown) {
    if (pat(KICK, s)) drum(36, 127);
    if (s % 4 == 2) drum(35, 70);             // rommel na de kick
  }
  if (m >= 2) drum(s % 4 == 2 ? 46 : 42, pat(HATS, s) ? 110 : 45);
  if (m >= 4 && pat(SNARE, s)) drum(40, 120);
  if (m % 8 == 7 && s >= 8) drum(38, 60 + s * 4);   // roffel naar de volgende sectie
  int st = toon(BASLIJN[sectie % 4], s);
  if (m >= 1 && st > -100 && !breakdown)
    noot(2, BAS + st + noot_in - 60, s % 4 == 3 ? 127 : 100);
  if (m >= 8 && s == 0 && m % 2 == 0) noot(3, m % 4 == 0 ? 55 : 58, 127, 4);
  if (breakdown) {
    bend(4, sinus(t * 4) * 60);
    if (s % 4 == 0) noot(4, 60 + s, 90, 4);
  }
  if (m >= 16 && !breakdown && pat("x..x..x...x..x..", s))
    noot(5, 43 + toon("0..3..5...7..a..", s), 80);
}
)SYN", "U0JDMQEAEQADAAAAAQACAAkAmQIkAAAAAABIAAAAqAAAAxAAeC4uLnguLi54Li4ueC4ueBAALi54LngueC4uLngueC54eBAALi4uLnguLi4uLi4ueC54LhAALi4wLi4wLi4wLi4wLi4wNxAALi4wLi4wLi4zLi4wLi41LhAALi4wLi4wLi4wLi4wLmEuNxAALi5DLi4wLi4wLi4wLi4wNxAAeC4ueC4ueC4uLnguLnguLhAAMC4uMy4uNS4uLjcuLmEuLgEfEQkABAMAABEKAAQDAQARCwAEAwIAEQwABAEAAwMAFQ0ABAAEAQEDBAAVDQAEAAQBAgMFABUNAAQABAEDAwYAFQ0ABAAEVgKRAAAAEQQABAEgEQYABAEKARBXBAIEAQIBJlcEAgQBAwE3VwQCBAEEAWZXBAIEAQUBHlcEAgQBAgFbAQpXAwMEAQMBWwFaVwMDBAEEAVsBblcDAwQBBQFbAShXAwMEVhACAAEIMxMABBACAAEYSFHEABACAAEcQiRQxgABACQTAQQSAT9R/AAQCgAQAQBXBwJR5gABJAF/AQFXAQMEEAEAAQQ1AQJAUfwAASMBRgEBVwEDBBACAAECSFExARABAAEENQECQFEWAQEuUBgBASoQCwAQAQBXBwJRKQEBblArAQEtAQFXAQMEEAIAAQRIUUcBEAwAEAEAVwcCJFBJAQEAUVYBASgBeAEBVwEDBBACAAEINQEHQFFsARABAAEISCRQbgEBAFGCAQEmATwQAQABBDIwAQFXAQMEEgABBDUUDQAEABABAFcIAhMCBBACAAEBSFGoARICAWQ9RiRQqgEBAFG0ARIBPyRQtgEBAFHhAQECEAkAEgIwEAcAMAE8MRABAAEENQEDQFHZAQF/UNsBAWQBAVcABAQQAgABCEhR9AEQAQABAEAkUPYBAQBRBgIQAgABAjUBAEAkUAgCAQBRKAIBAxACAAEENQEAQFEeAgE3UCACAToBfwEEVwAEBBIBUVsCAQQQAAABBDJXDAEBPDJXBgIEEAEAAQQ1AQBAUVsCAQQBPBABADABWgEEVwAEBBACAAEQSFFrAhIBPyRQbQIBAFF9AgMHABABAFcHAiRQfwIBAFGYAgEFASsDCAAQAQBXCAIwAVABAVcABARWAAAFAAYABgANAAcAFAAIABsACQAxAAoASAAMAEgADQBRAA4AVwAPAF8AEABnABEAbwASAHcAEwB/ABQAiQAVAJMAFgCdABcAqAAaAKgAGwCxABwAygAdANAAHgDmAB8A/AAhADEBIgBWASMAggEkAJUBJQC5ASYA4QEnACgCKAAtAikAPwIqAFsCLACCAi0A", 1005 },
  { "bytebeat_001", R"SYN(// BYTEBEAT 001 — 42 melodie · akkoorden
// formule: t*(42&t>>10)
//
// Een bytebeat is één regel C: normaal rekent een computer hem 8000 keer
// per seconde uit en is de uitkomst direct de geluidsgolf. Hier wordt de
// formule elke zestiende noot bemonsterd; de bits worden noten, akkoorden
// en drums op de SAM2695. Verander de formule en hoor wat er gebeurt.

uint8_t bb(uint32_t t) { return t*(42&t>>10); }

void start() {
  bpm = 125;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 41);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AAQAAAAAAABAAEBDwAAADYAAANWEgABKhIAAQo5OjIgVVYBfREEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwEpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRgwABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK2ABIBAUE6AUFAJFC4AAEBUcUAASQBcwEBVwEDBBIBAQM4AQM6AQJAUd0AAScBWgEBVwEDBBABAAECNVHrAAEqUO0AASwBKBICAT86MAEBVwEDBFYBAAkADwALAA8ADAAVAA0AGwAOACMADwArABAANgATADYAFABCABUASwAWAFoAFwCDABgAngAZAMUAGgDdABsA", 354 },
  { "bytebeat_002", R"SYN(// BYTEBEAT 002 — viznut 1 · ritme
// formule: t*((t>>12|t>>8)&63&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>8)&63&t>>4); }

void start() {
  bpm = 132;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 52);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEMORIAAQg5OwE/OhIAAQQ5OjIgVVYChAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwE0VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "techno_2_acid", R"SYN(// TECHNO 2 — ACID, 138 BPM
// Een 303-achtige baslijn met accenten en glijders. Het filter ademt met
// een sinus, en elke 8 maten muteert het patroon een beetje.

constexpr int GROND = 33;                     // A1
int noten[16];
uint8_t accent[16];
uint8_t glij[16];

void maakPatroon() {
  for (int i = 0; i < 16; i++) {
    noten[i] = toon("0.C0.c3.0F.70.3.", i);
    accent[i] = pat("x..x....x..x..x.", i);
    glij[i] = pat("..x...x.....x...", i);
  }
}

void muteer() {
  int i = rnd(16);
  noten[i] = noten[i] < -100 ? schaal(rnd(8)) : -1000;
  int j = rnd(16);
  accent[j] = !accent[j];
  int k = rnd(16);
  glij[k] = !glij[k];
}

void start() {
  bpm = 138;
  maten = 32;
  instrument(2, 38);                          // synth bass 1
  instrument(3, 87);                          // bass + lead
  cc(2, 65, 127);                             // portamento aan
  cc(3, 91, 70);
  cc(3, 93, 40);
  maakPatroon();
}

void stap() {
  if (s == 0 && m > 0 && m % 8 == 0) muteer();
  if (s % 4 == 0) drum(36, 127);
  if (s % 8 == 4) drum(39, 100);
  drum(s % 4 == 2 ? 46 : 42, s % 2 == 0 ? 85 : 40);
  if (m >= 4 && pat("...x..x....x.x..", s)) drum(37, 70);
  int adem = 64 + sinus(t * 2) / 2;           // 0..127, langzaam
  filter(2, 15 + adem * 3 / 4 + (accent[s] ? 25 : 0), 110);
  cc(2, 5, glij[s] ? 35 : 0);                 // glijtijd
  if (noten[s] > -100)
    noot(2, GROND + noten[s] + noot_in - 60, accent[s] ? 127 : 80, glij[s] ? 2 : 1);
  int echo = noten[(s + 13) % 16];            // drie stappen later, octaaf hoger
  if (m >= 16 && echo > -100 && s % 2 == 1) noot(3, GROND + 24 + echo, 60);
}
)SYN", "U0JDMQEAOgAFAAAAAwAEAAQAlwIkAAAAAAAHAAABWAAAA70AAAD/AAACEAAwLkMwLmMzLjBGLjcwLjMuEAB4Li54Li4uLnguLnguLnguEAAuLnguLi54Li4uLi54Li4uEAAuLi54Li54Li4uLngueC4uASERCQAEVgEAEwAEEgABEEJRVwADAAASAFcIAhIABxUKABAABAMBABIAVwcCIBIABxUaABAABAMCABIAVwcCIBIABxUqABAABBIAAQEwEwABATEEUAwAVgEQVw0BEwAEEgAUCgAQAAFkPUJReQABCFcNAVcJAVB/AALoAwAAPRIABxUKABAABAEQVw0BEwEEEgEUGgAQAD8gEgEHFRoAEAAEARBXDQETAgQSAhQqABAAPyASAgcVKgAQAARWAooAAAARBAAEASARBgAEAQIBJlcEAgQBAwFXVwQCBAECAUEBf1cDAwQBAwFbAUZXAwMEAQMBXQEoVwMDBFQBAARWEAEAAQBAURIBEAIAAQBGJFAUAQEAUSQBEAIAAQg1AQBAJFAmAQEAUS0BVAIABBABAAEENQEAQFFDAQEkAX8BAVcBAwQQAQABCDUBBEBRWQEBJwFkAQFXAQMEEAEAAQQ1AQJAUWoBAS5QbAEBKhABAAECNQEAQFF9AQFVUH8BASgBAVcBAwQQAgABBEhRmwEDAwAQAQBXBwIkUJ0BAQBRqgEBJQFGAQFXAQMEAUAQAAABAjJXDAEBAjMwEwAEAQIBDxIAAQMyAQQzMBABABQaABAAUdkBARlQ2wEBADABblcFAwQBAgEFEAEAFCoAEABR9gEBI1D4AQEAVwMDBBABABQKABAAAWQ9RlFIAgECEAkAEAEAFAoAEAAwEAcAMAE8MRABABQaABAAUTACAX9QMgIBUBABABQqABAAUUICAQJQRAIBAVcABAQQAQABDTABEDUUCgAQABMBBBACAAEQSFFsAhIBAWQ9RiRQbgIBAFF+AhABAAECNQEBQCRQgAIBAFGWAgEDEAkAARgwEgEwATwBAVcABARWAAAFAAcACgAHAAsAFAAMACUADQA3AA4ASQALAFgAEgBYABMAYAAUAIgAFQCQABYAogAXAKoAGAC9ABsAvQAcAMYAHQDMAB4A1AAfANwAIADmACEA8AAiAPoAIwD/ACYA/wAnAC0BKABDASkAWQEqAIUBKwCqASwAvAEtAOIBLgD8AS8ACwIwAEgCMQBZAjIA", 921 },
  { "bytebeat_003", R"SYN(// BYTEBEAT 003 — schuivende knars · drone
// formule: (t*(t>>5|t>>8))>>((t>>16)&7)

uint8_t bb(uint32_t t) { return (t*(t>>5|t>>8))>>((t>>16)&7); }

int vorige = -1;

void start() {
  bpm = 139;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 63);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABBTkSAAEIOTsyEgABEDkBBzo5IFVWAosAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBP1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_004", R"SYN(// BYTEBEAT 004 — viznut 2 · melodie
// formule: t*((t>>9|t>>13)&25&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>13)&25&t>>6); }

void start() {
  bpm = 146;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 74);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEJORIAAQ05OwEZOhIAAQY5OjIgVVYCkgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFKVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "techno_3_detroit", R"SYN(// TECHNO 3 — DETROIT, 126 BPM
// Warme strijkersakkoorden, een rollende bas, synth-stabs en een melodie
// die over de akkoorden zweeft. Am7 – Fmaj7 – C – G.

const int GROND[4] = { 57, 53, 48, 55 };
const bool MINEUR[4] = { true, false, false, false };
const uint8_t MELODIE[16] = { 0, 2, 4, 7, 9, 7, 4, 2, 0, 4, 7, 11, 12, 11, 7, 4 };

int akkoordNu() { return m % 4; }

void start() {
  bpm = 126;
  maten = 32;
  instrument(2, 33);                          // fingered bass
  instrument(3, 50);                          // synth strings
  instrument(4, 62);                          // synth brass
  instrument(5, 88);                          // fantasia pad-lead
  cc(3, 91, 110);
  cc(4, 91, 60);
  cc(5, 91, 90);
  cc(5, 93, 60);
}

void stap() {
  int a = akkoordNu();
  int g = GROND[a];
  bool mi = MINEUR[a];
  if (s % 4 == 0) drum(36, 120);
  if (m >= 1 && s % 8 == 4) drum(39, 95);
  if (m >= 2) drum(s % 4 == 2 ? 46 : 42, s % 2 ? 50 : 80);
  if (m >= 6 && pat("..x...x.x.....x.", s)) drum(75, 70);   // claves
  if (s % 2 == 1) noot(2, g - 24 + (s % 4 == 3 ? 12 : 0), 100);
  if (s == 0) akkoord(3, g - 12, mi, 70, 16);
  if (m >= 4 && pat("x..x..x.........", s)) akkoord(4, g, mi, 90, 1);
  if (m >= 8 && s % 2 == 0) {
    int i = (s / 2 + m * 3) % 16;
    noot(5, g + 12 + MELODIE[i] - (mi && MELODIE[i] % 12 == 4 ? 1 : 0), 75, 2);
  }
}
)SYN", "U0JDMQEAIQAEAAAAAgADAAIA6gIdAAAAAAAFAQAADQEAAGIBAAQQAC4ueC4uLngueC4uLi4ueC4QAHguLnguLnguLi4uLi4uLi4BAAE5FQkABAAEAQEBNRUJAAQABAECATAVCQAEAAQBAwE3FQkABAAEAQABASQVDQAEAAQBAQEAJBUNAAQABAECAQAkFQ0ABAAEAQMBACQVDQAEAAQBAAEAIBURABAABAEBAQIgFREAEAAEAQIBBCAVEQAQAAQBAwEHIBURABAABAEEAQkgFREAEAAEAQUBByAVEQAQAAQBBgEEIBURABAABAEHAQIgFREAEAAEAQgBACAVEQAQAAQBCQEEIBURABAABAEKAQcgFREAEAAEAQsBCyAVEQAQAAQBDAEMIBURABAABAENAQsgFREAEAAEAQ4BByAVEQAQAAQBDwEEIBURABAABFYQAgABBDVVVgF+EQQABAEgEQYABAECASFXBAIEAQMBMlcEAgQBBAE+VwQCBAEFAVhXBAIEAQMBWwFuVwMDBAEEAVsBPFcDAwQBBQFbAVpXAwMEAQUBXQE8VwMDBFZUAQATAAQSABQJAAQAEwEEEgAUDQAEACQTAgQQAQABBDUBAEBRkwEBJAF4AQFXAQMEEAIAAQFIUakBEAEAAQg1AQRAJFCrAQEAUbgBAScBXwEBVwEDBBACAAECSFHqARABAAEENQECQFHSAQEuUNQBASoQAQABAjVR4gEBMlDkAQFQAQFXAQMEEAIAAQZIUQACAwAAEAEAVwcCJFACAgEAUQ8CAUsBRgEBVwEDBBABAAECNQEBQFE+AgECEgEBGDEQAQABBDUBA0BRMwIBDFA1AgEAMAFkAQFXAAQEEAEAAQBAUVgCAQMSAQEMMRICAUYBEFcCBQQQAgABBEhRbgIDAQAQAQBXBwIkUHACAQBRgQIBBBIBEgIBWgEBVwIFBBACAAEISFGXAhABAAECNQEAQCRQmQIBAFHpAhABAAECMxACAAEDMjABEDUTAwQBBRIBAQwwEgMUEQAQADASAlHUAhIDFBEAEAABDDUBBEAkUNYCAQBR3gIBAVDgAgEAMQFLAQJXAAQEVgAABQAoAAYAVAAHAAUBCQANAQsADQEMABMBDQAZAQ4AIQEPACkBEAAxAREAOQESAEMBEwBNARQAVwEVAGIBGABiARkAaAEaAHIBGwB9ARwAkwEdALgBHgDqAR8ADwIgAD4CIQBYAiIAgQIjAJwCJACvAiUA", 936 },
  { "bytebeat_005", R"SYN(// BYTEBEAT 005 — en-poort · akkoorden
// formule: t*(t>>11&t>>8&123&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>8&123&t>>3); }

void start() {
  bpm = 153;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 85);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQg5OgF7OhIAAQM5OjIgVVYCmQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFVVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_006", R"SYN(// BYTEBEAT 006 — dubbele zaag · ritme
// formule: (t*5&t>>7)|(t*3&t>>10)

uint8_t bb(uint32_t t) { return (t*5&t>>7)|(t*3&t>>10); }

void start() {
  bpm = 160;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 96);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABBTISAAEHOToSAAEDMhIAAQo5OjsgVVYCoAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFgVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "complex_01_euclides", R"SYN(// COMPLEX 1 — EUCLIDISCHE RITMES
// Ritmes die k slagen zo gelijk mogelijk over n stappen verdelen (Toussaint).
// Veel wereldmuziek-ritmes zijn euclidisch: E(3,8) is de tresillo, E(5,8)
// de cinquillo. Elke laag heeft een eigen lengte; elke 4 maten draaien ze.

bool euclid(int k, int n, int rot, int i) {
  return ((i + rot) * k) % n < k;
}

int laag(int k, int n, int rot) { return euclid(k, n, rot, t % n); }

void start() {
  bpm = 122;
  maten = 16;
  instrument(1, 12);                          // marimba
  instrument(2, 32);                          // acoustic bass
  cc(1, 91, 60);
}

void stap() {
  int r = m / 4;
  if (laag(3, 8, 0)) drum(36, 115);
  if (laag(5, 8, r)) drum(56, 70);           // koebel
  if (laag(7, 16, r * 3)) drum(42, 75);
  if (laag(4, 12, r)) drum(76, 90);          // hoog houtblok
  if (laag(5, 13, r * 2)) drum(77, 80);      // laag houtblok
  if (laag(5, 9, r)) noot(1, 60 + schaal(t / 9 % 5 + r), 90);
  if (laag(3, 7, 0)) noot(1, 72 + schaal(t / 7 % 8), 70);
  if (laag(2, 5, r)) noot(2, 36 + schaal(t / 5 % 3), 100, 2);
}
)SYN", "U0JDMQEACQAFAAAAAwAEAAAAOgETAAAAAAABAAQEEgADAyMAAABKAAABVhIDEgIwEgAyEgE1EgBCJFVWEgASARICEAAAEgE2VAEAVVYBehEEAAQBEBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwE8VwMDBFYQAgABBDMTAAQBAwEIAQBUAgBRaQABJAFzAQFXAQMEAQUBCBIAVAIAUX8AATgBRgEBVwEDBAEHARASAAEDMlQCAFGYAAEqAUsBAVcBAwQBBAEMEgBUAgBRrgABTAFaAQFXAQMEAQUBDRIAAQIyVAIAUccAAU0BUAEBVwEDBAEFAQkSAFQCAFHvAAEBATwQAAABCTQBBTYSADBXCQEwAVoBAVcABAQBAwEHAQBUAgBRFAEBAQFIEAAAAQc0AQg2VwkBMAFGAQFXAAQEAQIBBRIAVAIAUTkBAQIBJBAAAAEFNAEDNlcJATABZAECVwAEBFYBAAYAAQAHABIACgAjAAwAIwANACkADgAvAA8ANwAQAD8AEQBKABQASgAVAFMAFgBpABcAfwAYAJgAGQCuABoAxwAbAO8AHAAUAR0A", 432 },
  { "bytebeat_007", R"SYN(// BYTEBEAT 007 — trappen · drone
// formule: (t>>6|t|t>>((t>>16)&15))*10+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>6|t|t>>((t>>16)&15))*10+((t>>11)&7); }

int vorige = -1;

void start() {
  bpm = 167;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 107);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQY5EgA7EgASAAEQOQEPOjk7AQoyEgABCzkBBzowIFVWAqcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBa1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_008", R"SYN(// BYTEBEAT 008 — xor-storm · melodie
// formule: ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6); }

void start() {
  bpm = 122;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 38);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA8QAQAAAAAAABAAEBKgAAAFEAAANWEgASAAEIORIAAQk5OzIBLjoSAAEIOToSABIAAQ05OhIAAQY5OzwgVVYBehEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwEmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRsQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHGAAEkAXgBAVcBAwQSAgEHOgEDQFHbAAEmAV8BAVcBAwQSARICPAEBOlHwAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMAAIADYACQA+AAoARgALAFEADgBRAA8AXQAQAGYAEQB1ABIAkAATALEAFADGABUA2wAWAA==", 343 },
  { "bytebeat_009", R"SYN(// BYTEBEAT 009 — modulo-ruis · akkoorden
// formule: (t&t%255)-(t*3&t>>13&t>>6)

uint8_t bb(uint32_t t) { return (t&t%255)-(t*3&t>>13&t>>6); }

void start() {
  bpm = 129;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 49);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAEQEQAAAAAAABAAEBIQAAAEsAAANWEgASAAL/AAAANjoSAAEDMhIAAQ05OhIAAQY5OjEgVVYCgQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwExVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRmAABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLLABIBAUE6AUFAJFDNAAEBUdoAASQBcwEBVwEDBBIBAQM4AQM6AQJAUfIAAScBWgEBVwEDBBABAAECNVEAAQEqUAIBASwBKBICAT86MAEBVwEDBFYBAAQAIQAGACEABwAqAAgAMAAJADgACgBAAAsASwAOAEsADwBXABAAYAARAG8AEgCYABMAswAUANoAFQDyABYA", 375 },
  { "complex_02_polymeter", R"SYN(// COMPLEX 2 — POLYMETER 5 · 7 · 11 · 13
// Vier patronen met priemlengtes lopen tegelijk. Pas na 5·7·11·13 = 5005
// stappen klinkt alles weer precies hetzelfde: muziek die nooit herhaalt.

const uint8_t VIJF[5]     = { 0, 3, 7, 3, 10 };
const uint8_t ZEVEN[7]    = { 12, 0, 7, 0, 5, 3, 0 };
const char *ELF           = "x..x.x..x.x";
const char *DERTIEN       = "x...x..x...x.";

void start() {
  bpm = 116;
  maten = 16;
  instrument(1, 11);                          // vibrafoon
  instrument(2, 46);                          // harp
  instrument(3, 39);                          // synth bass 2
  cc(1, 91, 80);
  cc(2, 91, 90);
}

void stap() {
  noot(1, 60 + VIJF[t % 5], 70 + (t % 5 == 0 ? 40 : 0));
  if (t % 2 == 0) noot(2, 72 + ZEVEN[t / 2 % 7], 60);
  if (pat(ELF, t)) drum(38, 80);
  if (pat(DERTIEN, t)) drum(36, 110);
  if (t % 3 == 0) drum(42, 50 + (t % 7) * 8);
  if (t % 11 == 0) noot(3, 36 + VIJF[t / 11 % 5], 110, 6);
}
)SYN", "U0JDMQEAFwADAAAAAQACAAIAkwETAAAAAACTAAAAzAAAAAsAeC4ueC54Li54LngNAHguLi54Li54Li4ueC4BAAEAIBUJAAUABAEBAQMgFQkABQAEAQIBByAVCQAFAAQBAwEDIBUJAAUABAEEAQogFQkABQAEAQABDCAVDgAHAAQBAQEAIBUOAAcABAECAQcgFQ4ABwAEAQMBACAVDgAHAAQBBAEFIBUOAAcABAEFAQMgFQ4ABwAEAQYBACAVDgAHAAQDAAARFQAEAwEAERYABFYBdBEEAAQBEBEGAAQBAQELVwQCBAECAS5XBAIEAQMBJ1cEAgQBAQFbAVBXAwMEAQIBWwFaVwMDBFYBAQE8EAAAAQU2FAkABQAwAUYQAAABBTYBAEBR7wABKFDxAAEAMAEBVwAEBBAAAAECNgEAQFEfAQECAUgQAAABAjQBBzYUDgAHADABPAEBVwAEBBAVABAAAFcHAlE1AQEmAVABAVcBAwQQFgAQAABXBwJRSwEBJAFuAQFXAQMEEAAAAQM2AQBAUWsBASoBMhAAAAEHNgEIMjABAVcBAwQQAAABCzYBAEBRkgEBAwEkEAAAAQs0AQU2FAkABQAwAW4BBlcABARWAAAFADcABgCEAAcAiwAIAJMACgCTAAsAmQAMAJ8ADQCnAA4ArwAPALcAEADBABEAzAAUAMwAFQD4ABYAHwEXADUBGABLARkAawEaAA==", 541 },
  { "bytebeat_010", R"SYN(// BYTEBEAT 010 — tjirp · ritme
// formule: (t>>7|t|t>>6)*10+4*(t&t>>13|t>>6)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>6)*10+4*(t&t>>13|t>>6); }

void start() {
  bpm = 136;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 60);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAERAAAAAAABAAEBJwAAAFEAAANWEgABBzkSADsSAAEGOTsBCjIBBBIAEgABDTk6EgABBjk7MjAgVVYCiAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwE8VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlGKAAEkAXgBAVcBAwQSAQEgOlGiAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG0AAEqATwBAVcBAwQSAQEPOgEPQFHJAAExAWQBAVcBAwQSAgFAOlHmAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEHAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAJwAGACcABwAwAAgANgAJAD4ACgBGAAsAUQAOAFEADwBdABAAZgARAHUAEgCKABMAogAUALQAFQDJABYA5gAXAA==", 370 },
  { "bytebeat_011", R"SYN(// BYTEBEAT 011 — melodietabel · drone
// formule: ((t>>4)*(13&(0x8898a989>>(t>>11&30))))&255

uint8_t bb(uint32_t t) { return ((t>>4)*(13&(0x8898a989>>(t>>11&30))))&255; }

int vorige = -1;

void start() {
  bpm = 143;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 71);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA/wATAAAAAAAIAAEBKAAAAFIAAAQBAT0RCQAEVhIAAQQ5AQ0CiamYiBIAAQs5AR46OToyAv8AAAA6IFVWAo8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBR1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSkQASAxAJAEEkUJMAAQFRsQABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRywABWlDNAAEoAQFXAAQEEAEAAQQ1AQBAUekAASMBZAEBVwEDBBIBAR86ARBAUf4AATYBWgEBVwEDBFYAAAYACAAEACgACAAoAAkAMQAKADcACwA/AAwARwANAFIAEABSABEAXgASAGcAEwB2ABQAfgAVAJYAFgCrABcAsQAZANMAGgDpABsA", 369 },
  { "bytebeat_012", R"SYN(// BYTEBEAT 012 — drie lagen · melodie
// formule: (t*9&t>>4|t*5&t>>7|t*3&t/1024)-1

uint8_t bb(uint32_t t) { return (t*9&t>>4|t*5&t>>7|t*3&t/1024)-1; }

void start() {
  bpm = 150;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 82);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9wAQAAAAAAABAAEBLQAAAFcAAANWEgABCTISAAEEOToSAAEFMhIAAQc5OjsSAAEDMhIAAgAEAAA0OjsBATEgVVYClgAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFSVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtwABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHMAAEkAXgBAVcBAwQSAgEHOgEDQFHhAAEmAV8BAVcBAwQSARICPAEBOlH2AAEqAUYBAVcBAwRWAQAEAC0ABgAtAAcANgAIADwACQBEAAoATAALAFcADgBXAA8AYwAQAGwAEQB7ABIAlgATALcAFADMABUA4QAWAA==", 349 },
  { "complex_03_fase", R"SYN(// COMPLEX 3 — FASEVERSCHUIVING
// In de geest van Steve Reichs phasing: twee stemmen spelen hetzelfde
// patroon van 12 noten. De tweede schuift elke 2 maten één stap op, zodat
// er steeds nieuwe melodieën ontstaan tot ze weer samenvallen.

const uint8_t PATROON[12] = { 62, 65, 69, 72, 74, 65, 62, 72, 69, 65, 74, 72 };

void start() {
  bpm = 132;
  maten = 24;
  instrument(1, 12);                          // marimba links
  instrument(2, 12);                          // marimba rechts
  cc(1, 10, 20);                              // pan links
  cc(2, 10, 108);                             // pan rechts
  cc(1, 91, 50);
  cc(2, 91, 50);
}

void stap() {
  int verschuiving = (m / 2) % 12;
  noot(1, PATROON[t % 12], 90);
  noot(2, PATROON[(t + verschuiving) % 12] + (m >= 12 ? 12 : 0), 80);
  if (PATROON[t % 12] == PATROON[(t + verschuiving) % 12]) drum(81, 60);   // samenval: triangel
  if (s == 0) drum(35, 70);
}
)SYN", "U0JDMQEAFQADAAAAAQACAAAAUgEQAAAAAACFAAAAzQAAAQEAAT4gFQkADAAEAQEBQSAVCQAMAAQBAgFFIBUJAAwABAEDAUggFQkADAAEAQQBSiAVCQAMAAQBBQFBIBUJAAwABAEGAT4gFQkADAAEAQcBSCAVCQAMAAQBCAFFIBUJAAwABAEJAUEgFQkADAAEAQoBSiAVCQAMAAQBCwFIIBUJAAwABFYChAAAABEEAAQBGBEGAAQBAQEMVwQCBAECAQxXBAIEAQEBCgEUVwMDBAECAQoBbFcDAwQBAQFbATJXAwMEAQIBWwEyVwMDBFYQAgABAjMBDDUTAAQBARAAAAEMNhQJAAwAAVoBAVcABAQBAhAAABIAMAEMNhQJAAwAEAIAAQxIUQwBAQxQDgEBADABUAEBVwAEBBAAAAEMNhQJAAwAEAAAEgAwAQw2FAkADABAUT4BAVEBPAEBVwEDBBABAAEAQFFRAQEjAUYBAVcBAwRWAAAGAIUACACFAAkAjgAKAJQACwCcAAwApAANAK4ADgC4AA8AwgAQAM0AEwDNABQA2QAVAO4AFgAXARcAPgEYAA==", 436 },
  { "bytebeat_013", R"SYN(// BYTEBEAT 013 — CA98 · akkoorden
// formule: t*(0xCA98>>(t>>9&14)&15)|t>>8

uint8_t bb(uint32_t t) { return t*(0xCA98>>(t>>9&14)&15)|t>>8; }

void start() {
  bpm = 157;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 93);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAADgEQAAAAAAABAAEBHgAAAEgAAANWEgACmMoAABIAAQk5AQ46OAEPOjISAAEIOTsgVVYCnQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFdVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRlQABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLIABIBAUE6AUFAJFDKAAEBUdcAASQBcwEBVwEDBBIBAQM4AQM6AQJAUe8AAScBWgEBVwEDBBABAAECNVH9AAEqUP8AASwBKBICAT86MAEBVwEDBFYBAAQAHgAGAB4ABwAnAAgALQAJADUACgA9AAsASAAOAEgADwBUABAAXQARAGwAEgCVABMAsAAUANcAFQDvABYA", 372 },
  { "bytebeat_014", R"SYN(// BYTEBEAT 014 — kruisvermenigvuldiging · ritme
// formule: (t|(t>>9|t>>7))*t&(t>>11|t>>9)

uint8_t bb(uint32_t t) { return (t|(t>>9|t>>7))*t&(t>>11|t>>9); }

void start() {
  bpm = 164;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 104);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAAgERAAAAAAABAAEBIQAAAEsAAANWEgASAAEJORIAAQc5OzsSADISAAELORIAAQk5OzogVVYCpAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGEAAEkAXgBAVcBAwQSAQEgOlGcAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGuAAEqATwBAVcBAwQSAQEPOgEPQFHDAAExAWQBAVcBAwQSAgFAOlHgAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEBAQECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAIQAGACEABwAqAAgAMAAJADgACgBAAAsASwAOAEsADwBXABAAYAARAG8AEgCEABMAnAAUAK4AFQDDABYA4AAXAA==", 364 },
  { "bytebeat_015", R"SYN(// BYTEBEAT 015 — tweeklank · drone
// formule: t*5&(t>>7)|t*3&(t*4>>10)

uint8_t bb(uint32_t t) { return t*5&(t>>7)|t*3&(t*4>>10); }

int vorige = -1;

void start() {
  bpm = 119;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 35);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBJQAAAEwAAAQBAT0RCQAEVhIAAQUyEgABBzk6EgABAzISAAEEMgEKOTo7IFVWAXcRBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBI1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACUACAAlAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "complex_04_cellulair", R"SYN(// COMPLEX 4 — CELLULAIRE AUTOMAAT
// Een rij van 16 cellen; elke maat ontstaat een nieuwe generatie volgens
// een regel van Wolfram (30 = chaos, 90 = Sierpinski, 110 = Turing-volledig).
// Elke stap speelt één cel: levend = noot, buren bepalen de drums.

constexpr int N = 16;
uint8_t cel[N];
uint8_t nieuw[N];
const int REGELS[3] = { 30, 90, 110 };

int regel() { return REGELS[m / 8 % 3]; }

void volgende() {
  for (int i = 0; i < N; i++) {
    int l = cel[(i + N - 1) % N], c = cel[i], r = cel[(i + 1) % N];
    nieuw[i] = (regel() >> (l * 4 + c * 2 + r)) & 1;
  }
  for (int i = 0; i < N; i++) cel[i] = nieuw[i];
}

void start() {
  bpm = 128;
  maten = 24;
  cel[N / 2] = 1;
  instrument(1, 8);                           // celesta
  instrument(2, 88);                          // pad
  cc(1, 91, 70);
  cc(2, 91, 110);
}

void stap() {
  if (s == 0 && t > 0) volgende();
  int buren = cel[(s + N - 1) % N] + cel[(s + 1) % N];
  if (cel[s]) noot(1, 60 + schaal(s + buren), 70 + buren * 25);
  if (buren == 2) drum(42, 70);
  if (cel[s] && buren == 0) drum(36, 110);
  if (!cel[s] && buren == 1 && s % 2 == 0) drum(75, 60);
  if (s == 0) {
    int levend = 0;
    for (int i = 0; i < N; i++) levend += cel[i];
    noot(2, 48 + schaal(levend % 10), 60, 16);
  }
}
)SYN", "U0JDMQEALQAFAAAAAwAEAAAANAIcAAAAAAAlAAAANQAABc4AAAASAQADARARCQAEAQABHhUqAAMABAEBAVoVKgADAAQBAgFuFSoAAwAEVhACAAEIMwEDNRQqAAMAVVYBABMABBIAEAkAQlGgABIAEAkAMAEBMRAJADUUCgAQABMBBBIAFAoAEAATAgQSAAEBMBAJADUUCgAQABMDBFQBABIBAQQyEgIBAjIwEgMwOAEBOiASAAcVGgAQAAQSAAEBMBMAAQExBFA6AAEAEwQEEgQQCQBCUc0AEgQUGgAQACASBAcVCgAQAAQSBAEBMBMEAQExBFClAFYCgAAAABEEAAQBGBEGAAQBASAQCQABAjMHFQoAEAAEAQEBCFcEAgQBAgFYVwQCBAEBAVsBRlcDAwQBAgFbAW5XAwMEVhABAAEAQFElARAAAAEARyRQJwEBAFEuAVQCAAQQAQAQCQAwAQExEAkANRQKABAAEAEAAQEwEAkANRQKABAAMBMABBABABQKABAAUXsBAQEBPBABABIAMFcJATABRhIAARkyMAEBVwAEBBIAAQJAUY0BASoBRgEBVwEDBBABABQKABAAUaEBEgABAEAkUKMBAQBRsAEBJAFuAQFXAQMEEAEAFAoAEAA/UcUBEgABAUAkUMcBAQBR1wEQAQABAjUBAEAkUNkBAQBR5gEBSwE8AQFXAQMEEAEAAQBAUTMCAQATAQQBABMCBBICEAkAQlEeAhICFAoAEAASAQcwEwEEEgIBATATAgEBMQRQ+QEBAgEwEgEBCjVXCQEwATwBEFcABARWAAAGAAYACQAlAAsANQANADUADgBDAA8AcwAQAJIADgCgABIAzgAVAM4AFgDXABcA3QAYAO0AGQD1ABoA/QAbAAcBHAASAR8AEgEgAC4BIQBUASIAewEjAI0BJACwASUA5gEmAO8BJwD0ASgAHgIpAA==", 718 },
  { "bytebeat_016", R"SYN(// BYTEBEAT 016 — priemmodulo · melodie
// formule: (t>>13|t%24)&(t>>7|t%19)

uint8_t bb(uint32_t t) { return (t>>13|t%24)&(t>>7|t%19); }

void start() {
  bpm = 126;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 46);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgABDTkSAAEYNjsSAAEHORIAARM2OzogVVYBfhEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwEuVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_017", R"SYN(// BYTEBEAT 017 — sirene · akkoorden
// formule: t*(t^t+(t>>15|1)^(t-1280^t)>>10)

uint8_t bb(uint32_t t) { return t*(t^t+(t>>15|1)^(t-1280^t)>>10); }

void start() {
  bpm = 133;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 57);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgASABIAEgABDzkBATswPBIAAgAFAAAxEgA8AQo5PDIgVVYChQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwE5VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRmwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_018", R"SYN(// BYTEBEAT 018 — wissel · ritme
// formule: t>>6&1?t>>5:-t>>4

uint8_t bb(uint32_t t) { return t>>6&1?t>>5:-t>>4; }

void start() {
  bpm = 140;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 68);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/gARAAAAAAABAAEBHQAAAEcAAANWEgABBjkBATpRFAASAAEFOVAaABIAPQEEOSBVVgKMAAAAEQQABAEEEQYABAEBAWZXBAIEAQIBI1cEAgQBAQFbAURXAwMEVhAAAAIAAgAAMhMABBIAVAEAIBMBBBIAAgABAAAwVAEAIBMCBBIBAoAAAAA6UYAAASQBeAEBVwEDBBIBASA6UZgAASYBRhICAR86MAEBVwEDBBICAQQ6UaoAASoBPAEBVwEDBBIBAQ86AQ9AUb8AATEBZAEBVwEDBBICAUA6UdwAAQEBPxIBAQc1VwkBMAFaAQFXAAQEEAEAAQQ1AQBAUf0AAQIBJxICAQU1VwkBMAFuAQNXAAQEVgEABAAdAAYAHQAHACYACAAsAAkANAAKADwACwBHAA4ARwAPAFMAEABcABEAawASAIAAEwCYABQAqgAVAL8AFgDcABcA", 360 },
  { "complex_05_levensspel", R"SYN(// COMPLEX 5 — CONWAYS LEVENSSPEL
// Een veld van 16 x 8 cellen (de randen lopen rond). Elke maat een nieuwe
// generatie; elke stap speelt een kolom: levende cellen worden noten,
// hoe hoger in het veld hoe hoger de toon.

constexpr int B = 16, H = 8;
uint8_t veld[B * H];
uint8_t volgend[B * H];

int cel(int x, int y) { return veld[((y + H) % H) * B + (x + B) % B]; }

void zet(int x, int y) { veld[y * B + x] = 1; }

void generatie() {
  for (int y = 0; y < H; y++)
    for (int x = 0; x < B; x++) {
      int n = cel(x - 1, y - 1) + cel(x, y - 1) + cel(x + 1, y - 1)
            + cel(x - 1, y) + cel(x + 1, y)
            + cel(x - 1, y + 1) + cel(x, y + 1) + cel(x + 1, y + 1);
      volgend[y * B + x] = n == 3 || (n == 2 && cel(x, y));
    }
  int levend = 0;
  for (int i = 0; i < B * H; i++) { veld[i] = volgend[i]; levend += veld[i]; }
  if (levend < 4) { zet(1, 0); zet(2, 1); zet(0, 2); zet(1, 2); zet(2, 2); zet(10, 4); zet(11, 4); zet(12, 4); }
}

void start() {
  bpm = 120;
  maten = 24;
  zet(1, 0); zet(2, 1); zet(0, 2); zet(1, 2); zet(2, 2);       // zweefvliegtuig
  zet(9, 4); zet(10, 3); zet(10, 4); zet(10, 5); zet(11, 3);   // r-pentomino
  instrument(1, 11);                          // vibrafoon
  instrument(2, 45);                          // pizzicato
  cc(1, 91, 80);
}

void stap() {
  if (s == 0 && t > 0) generatie();
  int aantal = 0;
  for (int y = 0; y < H; y++) {
    if (veld[y * B + s]) {
      aantal++;
      if (aantal <= 3) noot(y < 4 ? 1 : 2, 50 + mineur(H - y + 4), 60 + y * 6);
    }
  }
  if (aantal >= 3) drum(38, 70 + aantal * 5);
  if (aantal == 0 && s % 4 == 0) drum(36, 100);
  if (aantal == 1) drum(42, 60);
}
)SYN", "U0JDMQEACwEGAAAABAAFAAAA9AIlAAAAAAANAAICLQACAkEAAAWgAQAAFwIAAgEQEQkABAEIEQoABFYSARAKADAQCgA1EAkAMhIAEAkAMBAJADUwFAsAgABVVgEBIBIBEAkAMhIAMAcVCwCAAARWAQATAAQSABAKAEJREwEBABMBBBIBEAkAQlEFARIBAQExEgABATFUAQASARIAAQExVAEAMBIBAQEwEgABATFUAQAwEgEBATESAFQBADASAQEBMBIAVAEAMBIBAQExEgABATBUAQAwEgESAAEBMFQBADASAQEBMBIAAQEwVAEAMBMCBBICAQNAUuQAEgIBAkBR3gASARIAVAEAJFDgAAEAJFDmAAEBIBIAEAkAMhIBMAcViwCAAAQSAQEBMBMBAQExBFBUABIAAQEwEwABATEEUEYAAQATAwQBABMEBBIEEAkAEAoAMkJRVwESBBSLAIAAIBIEBxULAIAABBIEFAsAgAASAwcwEwMEEgQBATATBAEBMQRQHQESAwEEQlGfAQEBAQBUAgAEAQIBAVQCAAQBAAECVAIABAEBAQJUAgAEAQIBAlQCAAQBCgEEVAIABAELAQRUAgAEAQwBBFQCAARWAXgRBAAEARgRBgAEAQEBAFQCAAQBAgEBVAIABAEAAQJUAgAEAQEBAlQCAAQBAgECVAIABAEJAQRUAgAEAQoBA1QCAAQBCgEEVAIABAEKAQVUAgAEAQsBA1QCAAQBAQELVwQCBAECAS1XBAIEAQEBWwFQVwMDBFYQAQABAEBRKgIQAAABAEckUCwCAQBRMwJUAwAEAQATAAQBABMBBBIBEAoAQlGlAhIBEAkAMhABADAUCwCAAFGXAhIAAQEwEwABATEEEgABA0RRlwISAQEEQlF4AgEBUHoCAQIBMhAKABIBMQEEMFcKATABPBIBAQYyMAEBVwAEBBIBAQEwEwEBATEEUD0CEgABA0hRvQIBJgFGEgABBTIwAQFXAQMEEgABAEBR0gIQAQABBDUBAEAkUNQCAQBR4QIBJAFkAQFXAQMEEgABAUBR8wIBKgE8AQFXAQMEVgAABgANAAoALQAMAEEADgBBAA8ATwAQAF0AEQBdABMAXQASAF0AEQCDABIAmQATAMMAFAD3ABAABQEPABMBFgAYARcAVwEYAKABGwCgARwApgEdAKwBHgDUAR8A/AEgAAQCIQAMAiIAFwIlABcCJgAzAicAOAIoAEYCKQBYAioAYwIrAJcCKAClAi4AvQIvAOECMAA=", 950 },
  { "bytebeat_019", R"SYN(// BYTEBEAT 019 — tekstmelodie · drone
// formule: ((t*("36364689"[t>>13&7]&15))/12&128)+(((((t>>12)^(t>>12)-2)%11*t)/4|t>>13)&127)

uint8_t bb(uint32_t t) { return ((t*("36364689"[t>>13&7]&15))/12&128)+(((((t>>12)^(t>>12)-2)%11*t)/4|t>>13)&127); }

int vorige = -1;

void start() {
  bpm = 147;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 79);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAEAHgETAAAAAAAIAAEBRwAAAHEAAAQIADM2MzY0Njg5AQE9EQkABFYSAAMAABIAAQ05AQc6GAEPOjIBDDQCgAAAADoSAAEMORIAAQw5AQIxPAELNhIAMgEENBIAAQ05OwF/OjAgVVYCkwAAABEEAAQBBBEGAAQBAQE0VwQCBAECASRXBAIEAQEBWwFPVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQEGOBMDBBABAAEAQFKwABIDEAkAQSRQsgABAVHQAAECASwSAwECMlcKATABUAEIVwAEBBIDEQkABAEBAUQSAgEONVcKATASAgEBOlHqAAFaUOwAASgBAVcABAQQAQABBDUBAEBRCAEBIwFkAQFXAQMEEgEBHzoBEEBRHQEBNgFaAQFXAQMEVgAABgAIAAQARwAIAEcACQBQAAoAVgALAF4ADABmAA0AcQAQAHEAEQB9ABIAhgATAJUAFACdABUAtQAWAMoAFwDQABkA8gAaAAgBGwA=", 410 },
  { "bytebeat_020", R"SYN(// BYTEBEAT 020 — sierpinski-arp · melodie
// formule: (t*t/256)&(t>>((t/1024)%16))^t%64*(0x0C694A00>>(t>>9&31)&1)

uint8_t bb(uint32_t t) { return (t*t/256)&(t>>((t/1024)%16))^t%64*(0x0C694A00>>(t>>9&31)&1); }

void start() {
  bpm = 154;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 90);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAAAEQAAAAAAABAAEBNgAAAGAAAANWEgASADICAAEAADQSABIAAgAEAAA0ARA2OToSAAFANgIASmkMEgABCTkBHzo4AQE6MjwgVVYCmgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwFaVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRwAABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHVAAEkAXgBAVcBAwQSAgEHOgEDQFHqAAEmAV8BAVcBAwQSARICPAEBOlH/AAEqAUYBAVcBAwRWAQAEADYABgA2AAcAPwAIAEUACQBNAAoAVQALAGAADgBgAA8AbAAQAHUAEQCEABIAnwATAMAAFADVABUA6gAWAA==", 358 },
  { "bytebeat_021", R"SYN(// BYTEBEAT 021 — ritmische stapel · akkoorden
// formule: (t>>10^t>>11)%5*((t>>14&3^t>>15&1)+1)*t%99+((3+(t>>14&3)-(t>>16&1))/3*t%99&64)

uint8_t bb(uint32_t t) { return (t>>10^t>>11)%5*((t>>14&3^t>>15&1)+1)*t%99+((3+(t>>14&3)-(t>>16&1))/3*t%99&64); }

void start() {
  bpm = 161;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 101);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAPgEQAAAAAAABAAEBTgAAAHgAAANWEgABCjkSAAELOTwBBTYSAAEOOQEDOhIAAQ85AQE6PAEBMDISADIBYzYBAxIAAQ45AQM6MBIAARA5AQE6MQEDNBIAMgFjNgFAOjAgVVYCoQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwFlVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRxQABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFL4ABIBAUE6AUFAJFD6AAEBUQcBASQBcwEBVwEDBBIBAQM4AQM6AQJAUR8BAScBWgEBVwEDBBABAAECNVEtAQEqUC8BASwBKBICAT86MAEBVwEDBFYBAAQATgAGAE4ABwBXAAgAXQAJAGUACgBtAAsAeAAOAHgADwCEABAAjQARAJwAEgDFABMA4AAUAAcBFQAfARYA", 420 },
  { "complex_06_lsysteem", R"SYN(// COMPLEX 6 — L-SYSTEEM
// Lindenmayers herschrijfregels A -> AB, B -> A geven het Fibonacci-woord:
// ABAABABAABAAB... Een patroon dat nooit herhaalt maar wel overal op
// zichzelf lijkt. A en B worden ritme, de plek in het woord wordt melodie.

constexpr int MAX = 377;
uint8_t woord[MAX];
uint8_t tmp[MAX];
int lengte = 1;

void groei() {
  int n = 0;
  for (int i = 0; i < lengte && n < MAX; i++) {
    if (woord[i] == 0) {                      // A -> AB
      tmp[n++] = 0;
      if (n < MAX) tmp[n++] = 1;
    } else {                                  // B -> A
      tmp[n++] = 0;
    }
  }
  for (int i = 0; i < n; i++) woord[i] = tmp[i];
  lengte = n;
}

void start() {
  bpm = 124;
  maten = 16;
  for (int i = 0; i < 12; i++) groei();
  instrument(1, 13);                          // xylofoon
  instrument(2, 32);                          // acoustic bass
  cc(1, 91, 60);
}

void stap() {
  int a = woord[t % lengte];
  int b = woord[(t / 2) % lengte];
  int c = woord[(t / 3) % lengte];
  if (a == 0) drum(36, 105); else drum(38, 85);
  if (b) drum(42, 70);
  int hoogte = 0;
  for (int i = 0; i < 6; i++) hoogte += woord[(t + i * 5) % lengte];
  noot(1, 60 + schaal(hoogte + c * 3), 60 + a * 30);
  if (t % 3 == 0) noot(2, 36 + schaal(b + c * 2), 100, 3);
}
)SYN", "U0JDMQEA/QIEAAAAAgADAAAA6wEeAAAAAAAQAAADyAAAAQ4BAAUCeQEAABEJAAQBARH8AgRWAQATAAQBABMBBBIBEPwCQlEtABIAEAkAQiRQLwABAFGVABIBFAoAeQEBAEBRcwABACASAAEBMBMAAQExBxWDAXkBBBIAEAkAQlFwAAEBIBIAAQEwEwABATEHFYMBeQEEUIcAAQAgEgABATATAAEBMQcVgwF5AQQSAQEBMBMBAQExBFAaAAEAEwIEEgISAEJRwQASAhSDAXkBIBICBxUKAHkBBBICAQEwEwIBATEEUJoAEgAR/AIEVgF8EQQABAEQEQYABAEAEwAEEgABDEJR8wBUAQAEEgABATATAAEBMQRQ2QABAQENVwQCBAECASBXBAIEAQEBWwE8VwMDBFYQAAAQ/AI2FAoAeQETAAQQAAABAjQQ/AI2FAoAeQETAQQQAAABAzQQ/AI2FAoAeQETAgQSAAEAQFFWAQEkAWkBAVcBAwRQYAEBJgFVAQFXAQMEEgFRbwEBKgFGAQFXAQMEAQATAwQBABMEBBIEAQZCUagBEAAAEgQBBTIwEPwCNhQKAHkBEgMHMBMDBBIEAQEwEwQBATEEUHkBAQEBPBIDEgIBAzIwVwkBMAE8EgABHjIwAQFXAAQEEAAAAQM2AQBAUeoBAQIBJBIBEgIBAjIwVwkBMAFkAQNXAAQEVgAABgAJAAkAEAALABAADAAVAA0AMgAOAD8ADwBTABAAcwARAHMAEgCHAA0AlQAVAMEAFgDIABkAyAAaAM4AGwDUABwA8wAdAPsAHgADAR8ADgEiAA4BIwAdASQALwElAEEBJgBgAScAbwEoAHQBKQCoASoAxgErAA==", 649 },
  { "bytebeat_022", R"SYN(// BYTEBEAT 022 — acht-bit-mars · ritme
// formule: ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t))

uint8_t bb(uint32_t t) { return ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t)); }

void start() {
  bpm = 168;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 32);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAJQERAAAAAAABAAEBRAAAAG4AAANWEgACABAAADpRJgASABIAEgAC/wAAADY8MhIAAQQ5OwEBOVBBABIAAQM5EgACACAAADpRPgASAAECN1BAABIAOyBVVgKoAAAAEQQABAEEEQYABAEBAWZXBAIEAQIBV1cEAgQBAQFbASBXAwMEVhAAAAIABAAAMhMABBIAVAEAIBMBBBIAAgACAAAwVAEAIBMCBBIBAoAAAAA6UacAASQBeAEBVwEDBBIBASA6Ub8AASYBRhICAR86MAEBVwEDBBICAQQ6UdEAASoBPAEBVwEDBBIBAQ86AQ9AUeYAATEBZAEBVwEDBBICAUA6UQMBAQEBOxIBAQc1VwkBMAFaAQFXAAQEEAEAAQQ1AQBAUSQBAQIBIxICAQU1VwkBMAFuAQNXAAQEVgEABABEAAYARAAHAE0ACABTAAkAWwAKAGMACwBuAA4AbgAPAHoAEACDABEAkgASAKcAEwC/ABQA0QAVAOYAFgADARcA", 399 },
  { "bytebeat_023", R"SYN(// BYTEBEAT 023 — gefilterde zaag · drone
// formule: t*(((t>>11)&(t>>8))&(123&(t>>3)))

uint8_t bb(uint32_t t) { return t*(((t>>11)&(t>>8))&(123&(t>>3))); }

int vorige = -1;

void start() {
  bpm = 123;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 43);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABCzkSAAEIOToBexIAAQM5OjoyIFVWAXsRBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBK1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_024", R"SYN(// BYTEBEAT 024 — glitch-orgel · melodie
// formule: (t>>5)|(t<<4)|((t&1023)^1981)|((t-67)>>4)

uint8_t bb(uint32_t t) { return (t>>5)|(t<<4)|((t&1023)^1981)|((t-67)>>4); }

void start() {
  bpm = 130;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 54);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA8QAQAAAAAAABAAEBJwAAAFEAAANWEgABBTkSAAEENzsSAAL/AwAAOgK9BwAAPDsSAAFDMQEEOTsgVVYCggAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwE2VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRsQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHGAAEkAXgBAVcBAwQSAgEHOgEDQFHbAAEmAV8BAVcBAwQSARICPAEBOlHwAAEqAUYBAVcBAwRWAQAEACcABgAnAAcAMAAIADYACQA+AAoARgALAFEADgBRAA8AXQAQAGYAEQB1ABIAkAATALEAFADGABUA2wAWAA==", 343 },
  { "complex_07_markov", R"SYN(// COMPLEX 7 — MARKOVKETEN
// Een melodie zonder vaste noten: na elke toon kiest de keten de volgende
// met kansen uit een tabel van 7 x 7. Zo klinkt het steeds anders maar
// toch als dezelfde stijl. Elke 8 maten verschuiven de kansen.

constexpr int N = 7;
const uint8_t KANS[N * N] = {
//  naar: 0   1   2   3   4   5   6
         10, 30, 20, 15, 15,  5,  5,     // van 0 (grondtoon)
         35, 10, 30, 10,  5,  5,  5,     // van 1
         20, 25, 10, 25, 10,  5,  5,     // van 2
         10, 10, 30, 10, 30,  5,  5,     // van 3
         25,  5, 10, 25, 10, 20,  5,     // van 4 (kwint)
         10,  5,  5, 15, 35, 10, 20,     // van 5
         40,  5,  5,  5, 10, 25, 10,     // van 6
};
int toonNu = 0;
int vorige = 0;

int kies(int van) {
  int r = rnd(100);
  for (int naar = 0; naar < N; naar++) {
    int k = KANS[van * N + (naar + m / 8) % N];
    if (r < k) return naar;
    r -= k;
  }
  return 0;
}

void start() {
  bpm = 112;
  maten = 16;
  instrument(1, 73);                          // fluit
  instrument(2, 0);                           // piano
  instrument(3, 33);                          // bas
  cc(1, 91, 90);
  cc(2, 91, 60);
}

void stap() {
  if (s % 2 == 0) {
    vorige = toonNu;
    toonNu = kies(toonNu);
    noot(1, 72 + mineur(toonNu), 70 + toonNu * 6, 2);
  }
  if (s % 4 == 0) akkoord(2, 57 + mineur(vorige) - 12, 1, 50, 4);
  if (s % 8 == 0) noot(3, 33 + mineur(toonNu), 100, 6);
  if (pat("x.....x...x.....", s)) drum(36, 100);
  if (pat("....x.......x..x", s)) drum(38, 80);
  if (toonNu == vorige) drum(81, 50);
}
)SYN", "U0JDMQEAPQAEAAAAAgADAAIAegMkAAAAAAAuAgEEhgIAAL8CAAAQAHguLi4uLnguLi54Li4uLi4QAC4uLi54Li4uLi4uLnguLngBBxEJAAQBAAEKIBUKADEABAEBAR4gFQoAMQAEAQIBFCAVCgAxAAQBAwEPIBUKADEABAEEAQ8gFQoAMQAEAQUBBSAVCgAxAAQBBgEFIBUKADEABAEHASMgFQoAMQAEAQgBCiAVCgAxAAQBCQEeIBUKADEABAEKAQogFQoAMQAEAQsBBSAVCgAxAAQBDAEFIBUKADEABAENAQUgFQoAMQAEAQ4BFCAVCgAxAAQBDwEZIBUKADEABAEQAQogFQoAMQAEAREBGSAVCgAxAAQBEgEKIBUKADEABAETAQUgFQoAMQAEARQBBSAVCgAxAAQBFQEKIBUKADEABAEWAQogFQoAMQAEARcBHiAVCgAxAAQBGAEKIBUKADEABAEZAR4gFQoAMQAEARoBBSAVCgAxAAQBGwEFIBUKADEABAEcARkgFQoAMQAEAR0BBSAVCgAxAAQBHgEKIBUKADEABAEfARkgFQoAMQAEASABCiAVCgAxAAQBIQEUIBUKADEABAEiAQUgFQoAMQAEASMBCiAVCgAxAAQBJAEFIBUKADEABAElAQUgFQoAMQAEASYBDyAVCgAxAAQBJwEjIBUKADEABAEoAQogFQoAMQAEASkBFCAVCgAxAAQBKgEoIBUKADEABAErAQUgFQoAMQAEASwBBSAVCgAxAAQBLQEFIBUKADEABAEuAQogFQoAMQAEAS8BGSAVCgAxAAQBMAEKIBUKADEABAEAETsABAEAETwABFYBZFcNARMBBAEAEwIEEgIQCQBCUYICEgAQCQAyEgIQAgABCDMwEAkANTAUCgAxABMDBBIBEgNCUWsCEgJVEgMSAQcxEwEEEgIBATATAgEBMQRQOwIBAFVWAXARBAAEARARBgAEAQEBSVcEAgQBAgEAVwQCBAEDASFXBAIEAQEBWwFaVwMDBAECAVsBPFcDAwRWEAEAAQI1AQBAUfYCEDsAETwABBA7AFQBABE7AAQBAQFIEDsAVwoBMAFGEDsAAQYyMAECVwAEBBABAAEENQEAQFEaAwECATkQPABXCgEwAQwxAQEBMgEEVwIFBBABAAEINQEAQFE5AwEDASEQOwBXCgEwAWQBBlcABAQDAAAQAQBXBwJRTwMBJAFkAQFXAQMEAwEAEAEAVwcCUWUDASYBUAEBVwEDBBA7ABA8AEBReQMBUQEyAQFXAQMEVgAABgAGAAkAUwAKAKAACwDtAAwAOgENAIcBDgDUAQ8AIQIRACcCEgAuAhQALgIVADYCFgBEAhcAYAIYAGsCGQB0AhYAggIbAIYCHgCGAh8AjAIgAJICIQCaAiIAogIjAKoCJAC0AiUAvwIoAL8CKQDLAioA0gIrANwCLAD2Ai4AGgMvADkDMABPAzEAZQMyAA==", 1108 },
  { "bytebeat_025", R"SYN(// BYTEBEAT 025 — schuifregister · akkoorden
// formule: t*(t>>((t>>9|t>>8)&31)&63&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>((t>>9|t>>8)&31)&63&t>>4); }

void start() {
  bpm = 137;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 65);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAEQEQAAAAAAABAAEBIQAAAEsAAANWEgASABIAAQk5EgABCDk7AR86OQE/OhIAAQQ5OjIgVVYCiQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFBVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRmAABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLLABIBAUE6AUFAJFDNAAEBUdoAASQBcwEBVwEDBBIBAQM4AQM6AQJAUfIAAScBWgEBVwEDBBABAAECNVEAAQEqUAIBASwBKBICAT86MAEBVwEDBFYBAAQAIQAGACEABwAqAAgAMAAJADgACgBAAAsASwAOAEsADwBXABAAYAARAG8AEgCYABMAswAUANoAFQDyABYA", 375 },
  { "bytebeat_026", R"SYN(// BYTEBEAT 026 — golfslag · ritme
// formule: (t*(t>>3|t>>4))>>((t>>12)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>4))>>((t>>12)&7); }

void start() {
  bpm = 144;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 76);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEDORIAAQQ5OzISAAEMOQEHOjkgVVYCkAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFMVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_027", R"SYN(// BYTEBEAT 027 — arpeggiator · drone
// formule: t*(0x7531>>(t>>10&12)&15)&t>>4

uint8_t bb(uint32_t t) { return t*(0x7531>>(t>>10&12)&15)&t>>4; }

int vorige = -1;

void start() {
  bpm = 151;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 87);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA/AATAAAAAAAIAAEBJQAAAE8AAAQBAT0RCQAEVhIAAjF1AAASAAEKOQEMOjgBDzoyEgABBDk6IFVWApcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBV1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSjgASAxAJAEEkUJAAAQFRrgABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRyAABWlDKAAEoAQFXAAQEEAEAAQQ1AQBAUeYAASMBZAEBVwEDBBIBAR86ARBAUfsAATYBWgEBVwEDBFYAAAYACAAEACUACAAlAAkALgAKADQACwA8AAwARAANAE8AEABPABEAWwASAGQAEwBzABQAewAVAJMAFgCoABcArgAZANAAGgDmABsA", 366 },
  { "complex_08_twaalftoon", R"SYN(// COMPLEX 8 — TWAALFTOONSREEKS
// Schönbergs methode: een reeks met alle 12 tonen, die alleen in vier
// vormen mag klinken: origineel, omkering, kreeft en kreeft-omkering.
// Elke 4 maten een andere vorm en transpositie; de reeks bepaalt ook
// ritme en sterkte.

const uint8_t REEKS[12] = { 0, 11, 7, 8, 3, 1, 2, 10, 6, 5, 4, 9 };
int vorm = 0;
int transpositie = 0;

int reeksToon(int i) {
  int k = vorm >= 2 ? 11 - i : i;                      // kreeft: achterstevoren
  int v = REEKS[k];
  if (vorm == 1 || vorm == 3) v = (12 - v) % 12;       // omkering
  return (v + transpositie) % 12;
}

void start() {
  bpm = 100;
  maten = 16;
  instrument(1, 11);                          // vibrafoon
  instrument(2, 46);                          // harp
  instrument(3, 45);                          // pizzicato
  cc(1, 91, 100);
  cc(2, 91, 100);
}

int positie = 0;

void stap() {
  if (s == 0 && m % 4 == 0) {
    vorm = m / 4 % 4;
    transpositie = REEKS[m / 4 % 12];
  }
  int duur = REEKS[positie] % 3 + 1;
  if (t % duur == 0) {
    int tn = reeksToon(positie);
    int octaaf = 48 + (REEKS[(positie + 5) % 12] % 4) * 12;
    noot(1 + positie % 3, octaaf + tn, 50 + REEKS[(positie + 3) % 12] * 6, duur);
    positie = (positie + 1) % 12;
    if (positie == 0) drum(81, 40);
  }
}
)SYN", "U0JDMQEAGAAEAAAAAgADAAAA4QEcAAAAAACXAAED5QAAAB4BAAMBAAEAIBUJAAwABAEBAQsgFQkADAAEAQIBByAVCQAMAAQBAwEIIBUJAAwABAEEAQMgFQkADAAEAQUBASAVCQAMAAQBBgECIBUJAAwABAEHAQogFQkADAAEAQgBBiAVCQAMAAQBCQEFIBUJAAwABAEKAQQgFQkADAAEAQsBCSAVCQAMAAQBABEVAAQBABEWAAQBABEXAARWEBUAAQJIUagAAQsSADFQqgASABMBBBIBFAkADAATAgQQFQABAUBSygAQFQABA0AkUMwAAQFR2gABDBICMQEMNRMCBBICEBYAMAEMNVVWAWQRBAAEARARBgAEAQEBC1cEAgQBAgEuVwQCBAEDAS1XBAIEAQEBWwFkVwMDBAECAVsBZFcDAwRWEAEAAQBAUTQBEAIAAQQ1AQBAJFA2AQEAUVgBEAIAAQQzAQQ1ERUABBACAAEEMwEMNRQJAAwAERYABBAXABQJAAwAAQM1AQEwEwAEEAAAEgA2AQBAUeABEBcAVAEAEwEEATAQFwABBTABDDUUCQAMAAEENQEMMjATAgQBARAXAAEDNTASAhIBMAEyEBcAAQMwAQw1FAkADAABBjIwEgBXAAQEEBcAAQEwAQw1ERcABBAXAAEAQFHgAQFRASgBAVcBAwRWAAAHAIQACACKAAkAkAAcAJcACwCXAAwArQANALcADgDaAA8A5QASAOUAEwDrABQA8QAVAPkAFgABARcACQEYABMBGQAeAR4AHgEfADkBIABGASEAWAEjAGkBJAB1ASUAfgEmAJgBJwDAASgAzQEpAA==", 631 },
  { "bytebeat_028", R"SYN(// BYTEBEAT 028 — morse · melodie
// formule: (t>>8&t>>4)*(t>>12&7)|t>>3&t>>9

uint8_t bb(uint32_t t) { return (t>>8&t>>4)*(t>>12&7)|t>>3&t>>9; }

void start() {
  bpm = 158;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 98);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA7gAQAAAAAAABAAEBJAAAAE4AAANWEgABCDkSAAEEOToSAAEMOQEHOjISAAEDORIAAQk5OjsgVVYCngAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwFiVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRrgABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHDAAEkAXgBAVcBAwQSAgEHOgEDQFHYAAEmAV8BAVcBAwQSARICPAEBOlHtAAEqAUYBAVcBAwRWAQAEACQABgAkAAcALQAIADMACQA7AAoAQwALAE4ADgBOAA8AWgAQAGMAEQByABIAjQATAK4AFADDABUA2AAWAA==", 340 },
  { "bytebeat_029", R"SYN(// BYTEBEAT 029 — en-schuif · akkoorden
// formule: t*(69&t>>9)

uint8_t bb(uint32_t t) { return t*(69&t>>9); }

void start() {
  bpm = 165;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 109);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABRRIAAQk5OjIgVVYCpQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFtVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRhgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_030", R"SYN(// BYTEBEAT 030 — viznut-familie · ritme
// formule: t*((t>>9|t>>8)&31&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>8)&31&t>>6); }

void start() {
  bpm = 120;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 40);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgASAAEJORIAAQg5OwEfOhIAAQY5OjIgVVYBeBEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwEoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "complex_09_collatz", R"SYN(// COMPLEX 9 — COLLATZ
// Neem een getal; even: delen door 2, oneven: 3n + 1. Het vermoeden van
// Collatz zegt dat je altijd bij 1 uitkomt, maar niemand heeft het bewezen.
// De reeks wordt een melodie die stijgt en valt; bij 1 begint het volgende getal.

uint32_t getal = 27;
uint32_t start_getal = 27;
int stappen = 0;

uint32_t volgende(uint32_t n) { return n % 2 == 0 ? n / 2 : 3 * n + 1; }

int lengteVan(uint32_t n) {
  int k = 0;
  while (n != 1 && k < 1000) { n = volgende(n); k++; }
  return k;
}

void start() {
  bpm = 136;
  maten = 16;
  instrument(1, 81);                          // sawtooth lead
  instrument(2, 38);                          // synth bass
  cc(1, 91, 60);
}

void stap() {
  int hoogte = 0;
  for (uint32_t x = getal; x > 1; x /= 2) hoogte++;      // log2: hoe groot is het getal?
  noot(1, 48 + schaal(hoogte), 60 + (getal % 2) * 50);
  if (getal % 2 == 1) drum(38, 90); else if (s % 2 == 0) drum(42, 70);
  if (s % 4 == 0) drum(36, 110);
  if (s % 8 == 0) noot(2, 36 + schaal(lengteVan(getal) % 10), 100, 4);
  getal = volgende(getal);
  stappen++;
  if (getal == 1) {
    drum(49, 120);
    start_getal += 2;
    getal = start_getal;
    stappen = 0;
  }
}
)SYN", "U0JDMQEADAAFAAAAAwAEAAAAhQEcAAAAAAATAAEBMAABAmgAAACSAAACARsRCQAEARsRCgAEAQARCwAEVhIAAQI2AQBAUSYAEgABAjRQLgABAxIAMgEBMFVWAQATAQQSAAEBQVFJABIBAugDAABCJFBLAAEAUWQAEgBUAQATAAQSAQEBMBMBAQExBFA1ABIBVVYCiAAAABEEAAQBEBEGAAQBAQFRVwQCBAECASZXBAIEAQEBWwE8VwMDBFYBABMABBAJABMBBBIBAQFHUbwAEgABATATAAEBMQQBAhIBBzQTAQRQnQABAQEwEgBXCQEwATwQCQABAjYBMjIwAQFXAAQEEAkAAQI2AQFAUfEAASYBWgEBVwEDBFAHARABAAECNQEAQFEHAQEqAUYBAVcBAwQQAQABBDUBAEBRHQEBJAFuAQFXAQMEEAEAAQg1AQBAUUIBAQIBJBAJAFQCAAEKNVcJATABZAEEVwAEBBAJAFQBABEJAAQQCwABATARCwABATEEEAkAAQFAUYQBATEBeAEBVwEDBAECEAoABzARCgAEEAoAEQkABAEAEQsABFYAAAYABgAHAAwACAATAAoAMAAMADAADQA1AA4AZAAPAGgAEgBoABMAcQAUAHcAFQB/ABYAhwAXAJIAGgCSABsAlwAcALwAHQDYAB4ABwEfAB0BIABCASEATAEiAFkBIwBiASQAbAElAHcBJgB+AScA", 543 },
  { "bytebeat_031", R"SYN(// BYTEBEAT 031 — dubbele zaag · drone
// formule: (t*5&t>>7)|(t*5&t>>9)

uint8_t bb(uint32_t t) { return (t*5&t>>7)|(t*5&t>>9); }

int vorige = -1;

void start() {
  bpm = 127;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 51);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAAQUyEgABBzk6EgABBTISAAEJOTo7IFVWAX8RBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBM1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_032", R"SYN(// BYTEBEAT 032 — en-poorten · melodie
// formule: t*(t>>12&t>>9&123&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>9&123&t>>4); }

void start() {
  bpm = 134;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 62);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEMORIAAQk5OgF7OhIAAQQ5OjIgVVYChgAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwE+VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_033", R"SYN(// BYTEBEAT 033 — trappen · akkoorden
// formule: (t>>4|t|t>>((t>>15)&15))*5+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>4|t|t>>((t>>15)&15))*5+((t>>11)&7); }

void start() {
  bpm = 141;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 73);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBDkSADsSABIAAQ85AQ86OTsBBTISAAELOQEHOjAgVVYCjQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFJVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRmwABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "complex_10_priemen", R"SYN(// COMPLEX 10 — PRIEMGETALLEN
// De zeef van Eratosthenes in start() vindt alle priemgetallen onder 512.
// Elke stap is een getal: priem = slag. De afstand tot het vorige priemgetal
// wordt het interval; priemtweelingen (zoals 41 en 43) klinken als akkoord.

constexpr int MAX = 512;
bool priem[MAX];
int laatste = 2;

void start() {
  bpm = 128;
  maten = 16;
  for (int i = 2; i < MAX; i++) priem[i] = true;
  for (int i = 2; i * i < MAX; i++)
    if (priem[i])
      for (int j = i * i; j < MAX; j += i) priem[j] = false;
  instrument(1, 10);                          // speeldoos
  instrument(2, 48);                          // strijkers
  cc(1, 91, 70);
  cc(2, 91, 110);
}

void stap() {
  int n = t % MAX;
  if (n < 2) return;
  if (priem[n]) {
    int afstand = n - laatste;
    laatste = n;
    drum(36, 100);
    noot(1, 60 + schaal(afstand + n % 7), 90);
    if (n + 2 < MAX && priem[n + 2]) akkoord(2, 48 + schaal(n % 10), 1, 70, 4);
  } else {
    int deler = 2;
    while (n % deler != 0) deler++;
    if (deler == 2) drum(42, 50);
    else drum(76, 40 + deler * 4);
  }
}
)SYN", "U0JDMQEACwIDAAAAAQACAAAAiQEcAAAAAAAQAAADvgAAAwIAAgAAEQkABAECEQoCBFYCgAAAABEEAAQBEBEGAAQBAhMABBIAEAkAQlFHAAEBJBIABxUKAAACBBIAAQEwEwABATEEUCQAAQITAQQSARIBMhAJAEJRmQASARQKAAACUYsAEgESATITAgQSAhAJAEJRiwABACQSAgcVCgAAAgQSARICBzATAgRQagASAQEBMBMBAQExBFBMAAEBAQpXBAIEAQIBMFcEAgQBAQFbAUZXAwMEAQIBWwFuVwMDBFYQAAAQCQA2EwAEEgABAkJR0QBWEgAUCgAAAlFFARIAEAoCMRMBBBIAEQoCBAEkAWQBAVcBAwQBAQE8EgESAAEHNTBXCQEwAVoBAVcABAQSAAECMBAJAEJRJgESAAECMBQKAAACJFAoAQEAUUIBAQIBMBIAAQo1VwkBMAEBAUYBBFcCBQRQiAEBAhMCBBIAEgI1AQBBUWMBEgIBATATAgEBMQRQSgESAgECQFF4AQEqATIBAVcBAwRQiAEBTAEoEgIBBDIwAQFXAQMEVgAABgAJAAgAEAAKABAACwAZAAwAHwANAEcADgBYAA8AYgAQAIsADgCZABEAoQASAKkAEwCzABQAvgAXAL4AGADIABkA0QAaANsAGwDkABwA6gAdAPQAHgAMAR8ARQEgAEUBIQBKASIAYwEjAHgBJAA=", 539 },
  { "bytebeat_034", R"SYN(// BYTEBEAT 034 — melodietabel · ritme
// formule: t*(0x7531>>(t>>9&14)&15)|t>>8

uint8_t bb(uint32_t t) { return t*(0x7531>>(t>>9&14)&15)|t>>8; }

void start() {
  bpm = 148;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 84);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wARAAAAAAABAAEBHgAAAEgAAANWEgACMXUAABIAAQk5AQ46OAEPOjISAAEIOTsgVVYClAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFUVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlGBAAEkAXgBAVcBAwQSAQEgOlGZAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGrAAEqATwBAVcBAwQSAQEPOgEPQFHAAAExAWQBAVcBAwQSAgFAOlHdAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH+AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAHgAGAB4ABwAnAAgALQAJADUACgA9AAsASAAOAEgADwBUABAAXQARAGwAEgCBABMAmQAUAKsAFQDAABYA3QAXAA==", 361 },
  { "bytebeat_035", R"SYN(// BYTEBEAT 035 — knars · drone
// formule: (t*(t>>4|t>>7))>>((t>>14)&7)

uint8_t bb(uint32_t t) { return (t*(t>>4|t>>7))>>((t>>14)&7); }

int vorige = -1;

void start() {
  bpm = 155;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 95);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABBDkSAAEHOTsyEgABDjkBBzo5IFVWApsAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBX1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_036", R"SYN(// BYTEBEAT 036 — xor-familie · melodie
// formule: ((t*(t>>9|t>>6)&31&t>>9))^(t&t>>12|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>6)&31&t>>9))^(t&t>>12|t>>4); }

void start() {
  bpm = 162;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 106);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQY5OzIBHzoSAAEJOToSABIAAQw5OhIAAQQ5OzwgVVYCogAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFqVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "complex_11_oneindig", R"SYN(// COMPLEX 11 — ONEINDIGHEIDSREEKS
// Per Nørgårds uendelighedsrække: a(0) = 0, a(2n) = -a(n), a(2n+1) = a(n) + 1.
// Een recursieve reeks die zichzelf op elke schaal bevat: de stem op halve
// snelheid speelt dezelfde melodie, en die op een kwart ook.

int reeks(int n) {
  if (n == 0) return 0;
  if (n % 2 == 0) return -reeks(n / 2);
  return reeks(n / 2) + 1;
}

void start() {
  bpm = 120;
  maten = 24;
  instrument(1, 12);                          // marimba
  instrument(2, 46);                          // harp
  instrument(3, 42);                          // cello
  cc(1, 91, 70);
  cc(2, 91, 90);
  cc(3, 91, 90);
}

void stap() {
  noot(1, 67 + reeks(t), 85);
  if (t % 2 == 0) noot(2, 55 + reeks(t / 2), 75, 2);
  if (t % 4 == 0) noot(3, 43 + reeks(t / 4), 90, 4);
  if (reeks(t) > 2) drum(37, 60);
  if (reeks(t) < -2) drum(54, 60);
  if (s % 4 == 0) drum(35, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAADAEUAAAAAAABAAEBLgAAAHEAAABWEgABAEBRDAABAFUSAAECNQEAQFEhABIAAQIzVAEAPVUSAAECM1QBAAEBMFVWAXgRBAAEARgRBgAEAQEBDFcEAgQBAgEuVwQCBAEDASpXBAIEAQEBWwFGVwMDBAECAVsBWlcDAwQBAwFbAVpXAwMEVgEBAUMQAABUAQAwAVUBAVcABAQQAAABAjYBAEBRpgABAgE3EAAAAQI0VAEAMAFLAQJXAAQEEAAAAQQ2AQBAUcgAAQMBKxAAAAEENFQBADABWgEEVwAEBBAAAFQBAAECRlHeAAElATwBAVcBAwQQAABUAQABAj1CUfUAATYBPAEBVwEDBBABAAEENQEAQFELAQEjAUYBAVcBAwRWAQAGAAEABwAMAAgAIQAJAC4ADAAuAA0ANAAOADoADwBCABAASgARAFIAEgBcABMAZgAUAHEAFwBxABgAhAAZAKYAGgDIABsA3gAcAPUAHQA=", 386 },
  { "bytebeat_037", R"SYN(// BYTEBEAT 037 — modulo-ritme · akkoorden
// formule: (t>>13|t%18)&(t>>6|t%23)

uint8_t bb(uint32_t t) { return (t>>13|t%18)&(t>>6|t%23); }

void start() {
  bpm = 169;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 37);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABDTkSAAESNjsSAAEGORIAARc2OzogVVYCqQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwElVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_038", R"SYN(// BYTEBEAT 038 — vermenigvuldigers · ritme
// formule: t*7&(t>>5)|t*(t>>10&7)

uint8_t bb(uint32_t t) { return t*7&(t>>5)|t*(t>>10&7); }

void start() {
  bpm = 124;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 48);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgABBzISAAEFOToSABIAAQo5AQc6MjsgVVYBfBEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwEwVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_039", R"SYN(// BYTEBEAT 039 — en-schuif · drone
// formule: t*(45&t>>10)

uint8_t bb(uint32_t t) { return t*(45&t>>10); }

int vorige = -1;

void start() {
  bpm = 131;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 59);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAAS0SAAEKOToyIFVWAoMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBO1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "complex_12_patronen", R"SYN(// COMPLEX 12 — PATROONTRANSFORMATIES
// In de stijl van live-codeertalen als TidalCycles en Strudel: één patroon
// wordt telkens anders bewerkt: omgekeerd, versneld, gedraaid, uitgedund.
// De bewerking wisselt per maat, als een live-coder die regels aanpast.

uint8_t basis[16] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
const uint8_t TOON[16] = { 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 7, 0, 10, 0, 0, 0 };

int omgekeerd(int i) { return 15 - i; }
int versneld(int i) { return i * 2 % 16; }
int gedraaid(int i, int k) { return (i + k) % 16; }

int bewerk(int i) {
  int soort = m % 6;
  if (soort == 1) return omgekeerd(i);
  if (soort == 2) return versneld(i);
  if (soort == 3) return gedraaid(i, m % 16);
  if (soort == 4) return versneld(omgekeerd(i));
  return i;
}

bool uitdunnen(int kans) { return rnd(100) < kans; }

void start() {
  bpm = 130;
  maten = 24;
  instrument(1, 81);                          // saw lead
  instrument(2, 38);                          // synth bass
  instrument(3, 90);                          // polysynth pad
  cc(1, 91, 60);
  cc(3, 91, 110);
}

void stap() {
  int i = bewerk(s);
  bool dun = m % 6 == 5 && uitdunnen(50);
  if (basis[i] && !dun) {
    noot(1, 60 + TOON[i] + (m % 4 == 3 ? 12 : 0), 100);
    drum(36, 110);
  }
  if (!basis[i] && s % 2 == 1) drum(42, 60);
  if (basis[(i + 4) % 16]) noot(2, 36 + TOON[(i + 4) % 16], 100);
  if (s == 0) akkoord(3, 48 + schaal(m % 5), 1, 60, 16);
  if (s == 0 && m % 8 == 7) {
    int k = rnd(16);
    basis[k] = !basis[k];                     // het patroon zelf evolueert ook
  }
}
)SYN", "U0JDMQEAKQAIAAAABgAHAAAAJQMhAAAAAABhAQEBaAEBAXIBAgJ8AQECygEBAdUBAAARAgADAQABASAVCQAQAAQBAQEAIBUJABAABAECAQAgFQkAEAAEAQMBASAVCQAQAAQBBAEAIBUJABAABAEFAQAgFQkAEAAEAQYBASAVCQAQAAQBBwEAIBUJABAABAEIAQAgFQkAEAAEAQkBACAVCQAQAAQBCgEBIBUJABAABAELAQAgFQkAEAAEAQwBASAVCQAQAAQBDQEAIBUJABAABAEOAQAgFQkAEAAEAQ8BACAVCQAQAAQBAAEAIBUZABAABAEBAQAgFRkAEAAEAQIBACAVGQAQAAQBAwEDIBUZABAABAEEAQAgFRkAEAAEAQUBACAVGQAQAAQBBgEFIBUZABAABAEHAQAgFRkAEAAEAQgBACAVGQAQAAQBCQEAIBUZABAABAEKAQcgFRkAEAAEAQsBACAVGQAQAAQBDAEKIBUZABAABAENAQAgFRkAEAAEAQ4BACAVGQAQAAQBDwEAIBUZABAABFYBDxIAMVVWEgABAjIBEDVVVhIAEgEwARA1VVYQAgABBjUTAQQSAQEBQFGTARIAVAEAVRIBAQJAUaEBEgBUAgBVEgEBA0BRtQESABACAAEQNVQDAFUSAQEEQFHGARIAVAEAVAIAVRIAVVYBZFcNARIAQiRVVgKCAAAAEQQABAEYEQYABAEBAVFXBAIEAQIBJlcEAgQBAwFaVwQCBAEBAVsBPFcDAwQBAwFbAW5XAwMEVhABAFQEABMABBACAAEGNQEFQFEvAgEyVAUAJFAxAgEAJBMBBBIAFAkAEABRRgISAT8kUEgCAQBRfQIBAQE8EgAUGQAQADAQAgABBDUBA0BRaAIBDFBqAgEAMAFkAQFXAAQEASQBbgEBVwEDBBIAFAkAEAA/UZUCEAEAAQI1AQFAJFCXAgEAUaQCASoBPAEBVwEDBBIAAQQwARA1FAkAEABRzgIBAgEkEgABBDABEDUUGQAQADABZAEBVwAEBBABAAEAQFHvAgEDATAQAgABBTVXCQEwAQEBPAEQVwIFBBABAAEAQFEFAxACAAEINQEHQCRQBwMBAFEkAwEQVw0BEwIEEgIUCQAQAD8gEgIHFQkAEAAEVgAABgCwAAcAYQEJAGgBCgByAQsAfAENAHwBDgCFAQ8AkwEQAKEBEQC1ARIAxgETAMoBFgDVARgA1QEZAN4BGgDkARsA7AEcAPQBHQD8AR4ABgIfABECIgARAiMAGgIkADUCJQBLAiYAcwInAH0CKQCkAioAzgIrAO8CLAAKAy0AEgMuAA==", 991 },
  { "bytebeat_040", R"SYN(// BYTEBEAT 040 — viznut-familie · melodie
// formule: t*((t>>11|t>>10)&25&t>>5)

uint8_t bb(uint32_t t) { return t*((t>>11|t>>10)&25&t>>5); }

void start() {
  bpm = 138;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 70);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQo5OwEZOhIAAQU5OjIgVVYCigAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwFGVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_041", R"SYN(// BYTEBEAT 041 — dubbele zaag · akkoorden
// formule: (t*3&t>>6)|(t*2&t>>11)

uint8_t bb(uint32_t t) { return (t*3&t>>6)|(t*2&t>>11); }

void start() {
  bpm = 145;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 81);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEGOToSAAECMhIAAQs5OjsgVVYCkQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwFRVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_042", R"SYN(// BYTEBEAT 042 — en-poorten · ritme
// formule: t*(t>>10&t>>7&63&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>10&t>>7&63&t>>2); }

void start() {
  bpm = 152;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 92);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEKORIAAQc5OgE/OhIAAQI5OjIgVVYCmAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwFcVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_043", R"SYN(// BYTEBEAT 043 — trappen · drone
// formule: (t>>7|t|t>>((t>>16)&15))*5+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>((t>>16)&15))*5+((t>>10)&7); }

int vorige = -1;

void start() {
  bpm = 159;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 103);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQc5EgA7EgASAAEQOQEPOjk7AQUyEgABCjkBBzowIFVWAp8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBZ1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_044", R"SYN(// BYTEBEAT 044 — melodietabel · melodie
// formule: t*(0xC864>>(t>>10&14)&15)|t>>8

uint8_t bb(uint32_t t) { return t*(0xC864>>(t>>10&14)&15)|t>>8; }

void start() {
  bpm = 166;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 34);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA6AAQAAAAAAABAAEBHgAAAEgAAANWEgACZMgAABIAAQo5AQ46OAEPOjISAAEIOTsgVVYCpgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwEiVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRqAABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG9AAEkAXgBAVcBAwQSAgEHOgEDQFHSAAEmAV8BAVcBAwQSARICPAEBOlHnAAEqAUYBAVcBAwRWAQAEAB4ABgAeAAcAJwAIAC0ACQA1AAoAPQALAEgADgBIAA8AVAAQAF0AEQBsABIAhwATAKgAFAC9ABUA0gAWAA==", 334 },
  { "bytebeat_045", R"SYN(// BYTEBEAT 045 — knars · akkoorden
// formule: (t*(t>>5|t>>8))>>((t>>14)&7)

uint8_t bb(uint32_t t) { return (t*(t>>5|t>>8))>>((t>>14)&7); }

void start() {
  bpm = 121;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 45);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAEQAAAAAAABAAEBGwAAAEIAAANWEgASAAEFORIAAQg5OzISAAEOOQEHOjkgVVYBeREEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwEtVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRjwABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLCABIBAUE6AUFAJFDEAAEBUdEAASQBcwEBVwEDBBIBAQM4AQM6AQJAUekAAScBWgEBVwEDBBABAAECNVH3AAEqUPkAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgCPABMAqgAUANEAFQDpABYA", 366 },
  { "bytebeat_046", R"SYN(// BYTEBEAT 046 — xor-familie · ritme
// formule: ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>11|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>11|t>>6); }

void start() {
  bpm = 128;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 56);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEIORIAAQk5OzIBLjoSAAEIOToSABIAAQs5OhIAAQY5OzwgVVYCgAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwE4VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_047", R"SYN(// BYTEBEAT 047 — modulo-ritme · drone
// formule: (t>>12|t%40)&(t>>8|t%15)

uint8_t bb(uint32_t t) { return (t>>12|t%40)&(t>>8|t%15); }

int vorige = -1;

void start() {
  bpm = 135;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 67);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQw5EgABKDY7EgABCDkSAAEPNjs6IFVWAocAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBQ1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_048", R"SYN(// BYTEBEAT 048 — vermenigvuldigers · melodie
// formule: t*11&(t>>4)|t*(t>>10&7)

uint8_t bb(uint32_t t) { return t*11&(t>>4)|t*(t>>10&7); }

void start() {
  bpm = 142;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 78);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCzISAAEEOToSABIAAQo5AQc6MjsgVVYCjgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwFOVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_049", R"SYN(// BYTEBEAT 049 — en-schuif · akkoorden
// formule: t*(37&t>>10)

uint8_t bb(uint32_t t) { return t*(37&t>>10); }

void start() {
  bpm = 149;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 89);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABJRIAAQo5OjIgVVYClQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFZVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRhgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_050", R"SYN(// BYTEBEAT 050 — viznut-familie · ritme
// formule: t*((t>>12|t>>7)&47&t>>5)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>7)&47&t>>5); }

void start() {
  bpm = 156;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 100);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEMORIAAQc5OwEvOhIAAQU5OjIgVVYCnAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwFkVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_051", R"SYN(// BYTEBEAT 051 — dubbele zaag · drone
// formule: (t*9&t>>7)|(t*2&t>>10)

uint8_t bb(uint32_t t) { return (t*9&t>>7)|(t*2&t>>10); }

int vorige = -1;

void start() {
  bpm = 163;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 31);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQkyEgABBzk6EgABAjISAAEKOTo7IFVWAqMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBH1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_052", R"SYN(// BYTEBEAT 052 — en-poorten · melodie
// formule: t*(t>>11&t>>8&77&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>8&77&t>>3); }

void start() {
  bpm = 118;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 42);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgASAAELORIAAQg5OgFNOhIAAQM5OjIgVVYBdhEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwEqVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_053", R"SYN(// BYTEBEAT 053 — trappen · akkoorden
// formule: (t>>5|t|t>>((t>>14)&15))*12+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>5|t|t>>((t>>14)&15))*12+((t>>12)&7); }

void start() {
  bpm = 125;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 53);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAEQEQAAAAAAABAAEBJAAAAEsAAANWEgABBTkSADsSABIAAQ45AQ86OTsBDDISAAEMOQEHOjAgVVYBfREEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwE1VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRmAABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLLABIBAUE6AUFAJFDNAAEBUdoAASQBcwEBVwEDBBIBAQM4AQM6AQJAUfIAAScBWgEBVwEDBBABAAECNVEAAQEqUAIBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAqAAgAMAAJADgACgBAAAsASwAOAEsADwBXABAAYAARAG8AEgCYABMAswAUANoAFQDyABYA", 375 },
  { "bytebeat_054", R"SYN(// BYTEBEAT 054 — melodietabel · ritme
// formule: t*(0x8642>>(t>>9&14)&15)|t>>7

uint8_t bb(uint32_t t) { return t*(0x8642>>(t>>9&14)&15)|t>>7; }

void start() {
  bpm = 132;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 64);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wARAAAAAAABAAEBHgAAAEgAAANWEgACQoYAABIAAQk5AQ46OAEPOjISAAEHOTsgVVYChAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFAVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGBAAEkAXgBAVcBAwQSAQEgOlGZAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGrAAEqATwBAVcBAwQSAQEPOgEPQFHAAAExAWQBAVcBAwQSAgFAOlHdAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH+AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAHgAGAB4ABwAnAAgALQAJADUACgA9AAsASAAOAEgADwBUABAAXQARAGwAEgCBABMAmQAUAKsAFQDAABYA3QAXAA==", 361 },
  { "bytebeat_055", R"SYN(// BYTEBEAT 055 — knars · drone
// formule: (t*(t>>3|t>>7))>>((t>>15)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>7))>>((t>>15)&7); }

int vorige = -1;

void start() {
  bpm = 139;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 75);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABAzkSAAEHOTsyEgABDzkBBzo5IFVWAosAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBS1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_056", R"SYN(// BYTEBEAT 056 — xor-familie · melodie
// formule: ((t*(t>>7|t>>9)&31&t>>7))^(t&t>>13|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>9)&31&t>>7))^(t&t>>13|t>>6); }

void start() {
  bpm = 146;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 86);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQk5OzIBHzoSAAEHOToSABIAAQ05OhIAAQY5OzwgVVYCkgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFWVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "bytebeat_057", R"SYN(// BYTEBEAT 057 — modulo-ritme · akkoorden
// formule: (t>>13|t%32)&(t>>7|t%15)

uint8_t bb(uint32_t t) { return (t>>13|t%32)&(t>>7|t%15); }

void start() {
  bpm = 153;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 97);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABDTkSAAEgNjsSAAEHORIAAQ82OzogVVYCmQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwFhVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_058", R"SYN(// BYTEBEAT 058 — vermenigvuldigers · ritme
// formule: t*5&(t>>5)|t*(t>>12&7)

uint8_t bb(uint32_t t) { return t*5&(t>>5)|t*(t>>12&7); }

void start() {
  bpm = 160;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 108);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABBTISAAEFOToSABIAAQw5AQc6MjsgVVYCoAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFsVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_059", R"SYN(// BYTEBEAT 059 — en-schuif · drone
// formule: t*(63&t>>10)

uint8_t bb(uint32_t t) { return t*(63&t>>10); }

int vorige = -1;

void start() {
  bpm = 167;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 39);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAAT8SAAEKOToyIFVWAqcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBJ1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_060", R"SYN(// BYTEBEAT 060 — viznut-familie · melodie
// formule: t*((t>>13|t>>10)&123&t>>3)

uint8_t bb(uint32_t t) { return t*((t>>13|t>>10)&123&t>>3); }

void start() {
  bpm = 122;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 50);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgASAAENORIAAQo5OwF7OhIAAQM5OjIgVVYBehEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwEyVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_061", R"SYN(// BYTEBEAT 061 — dubbele zaag · akkoorden
// formule: (t*7&t>>8)|(t*3&t>>9)

uint8_t bb(uint32_t t) { return (t*7&t>>8)|(t*3&t>>9); }

void start() {
  bpm = 129;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 61);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEIOToSAAEDMhIAAQk5OjsgVVYCgQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwE9VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_062", R"SYN(// BYTEBEAT 062 — en-poorten · ritme
// formule: t*(t>>13&t>>7&123&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>13&t>>7&123&t>>3); }

void start() {
  bpm = 136;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 72);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQc5OgF7OhIAAQM5OjIgVVYCiAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwFIVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_063", R"SYN(// BYTEBEAT 063 — trappen · drone
// formule: (t>>6|t|t>>((t>>15)&15))*12+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>6|t|t>>((t>>15)&15))*12+((t>>11)&7); }

int vorige = -1;

void start() {
  bpm = 143;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 83);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQY5EgA7EgASAAEPOQEPOjk7AQwyEgABCzkBBzowIFVWAo8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBU1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_064", R"SYN(// BYTEBEAT 064 — melodietabel · melodie
// formule: t*(0x6B8D>>(t>>11&14)&15)|t>>7

uint8_t bb(uint32_t t) { return t*(0x6B8D>>(t>>11&14)&15)|t>>7; }

void start() {
  bpm = 150;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 94);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA6AAQAAAAAAABAAEBHgAAAEgAAANWEgACjWsAABIAAQs5AQ46OAEPOjISAAEHOTsgVVYClgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFeVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRqAABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG9AAEkAXgBAVcBAwQSAgEHOgEDQFHSAAEmAV8BAVcBAwQSARICPAEBOlHnAAEqAUYBAVcBAwRWAQAEAB4ABgAeAAcAJwAIAC0ACQA1AAoAPQALAEgADgBIAA8AVAAQAF0AEQBsABIAhwATAKgAFAC9ABUA0gAWAA==", 334 },
  { "bytebeat_065", R"SYN(// BYTEBEAT 065 — knars · akkoorden
// formule: (t*(t>>6|t>>8))>>((t>>15)&7)

uint8_t bb(uint32_t t) { return (t*(t>>6|t>>8))>>((t>>15)&7); }

void start() {
  bpm = 157;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 105);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEGORIAAQg5OzISAAEPOQEHOjkgVVYCnQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_066", R"SYN(// BYTEBEAT 066 — xor-familie · ritme
// formule: ((t*(t>>9|t>>10)&46&t>>9))^(t&t>>12|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>10)&46&t>>9))^(t&t>>12|t>>5); }

void start() {
  bpm = 164;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 36);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQo5OzIBLjoSAAEJOToSABIAAQw5OhIAAQU5OzwgVVYCpAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwEkVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_067", R"SYN(// BYTEBEAT 067 — modulo-ritme · drone
// formule: (t>>11|t%27)&(t>>6|t%19)

uint8_t bb(uint32_t t) { return (t>>11|t%27)&(t>>6|t%19); }

int vorige = -1;

void start() {
  bpm = 119;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 47);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAAQs5EgABGzY7EgABBjkSAAETNjs6IFVWAXcRBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBL1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_068", R"SYN(// BYTEBEAT 068 — vermenigvuldigers · melodie
// formule: t*9&(t>>4)|t*(t>>12&7)

uint8_t bb(uint32_t t) { return t*9&(t>>4)|t*(t>>12&7); }

void start() {
  bpm = 126;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 58);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgABCTISAAEEOToSABIAAQw5AQc6MjsgVVYBfhEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwE6VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_069", R"SYN(// BYTEBEAT 069 — en-schuif · akkoorden
// formule: t*(99&t>>11)

uint8_t bb(uint32_t t) { return t*(99&t>>11); }

void start() {
  bpm = 133;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 69);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABYxIAAQs5OjIgVVYChQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFFVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRhgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_070", R"SYN(// BYTEBEAT 070 — viznut-familie · ritme
// formule: t*((t>>9|t>>7)&63&t>>3)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>7)&63&t>>3); }

void start() {
  bpm = 140;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 80);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEJORIAAQc5OwE/OhIAAQM5OjIgVVYCjAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwFQVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_071", R"SYN(// BYTEBEAT 071 — dubbele zaag · drone
// formule: (t*5&t>>6)|(t*3&t>>11)

uint8_t bb(uint32_t t) { return (t*5&t>>6)|(t*3&t>>11); }

int vorige = -1;

void start() {
  bpm = 147;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 91);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQUyEgABBjk6EgABAzISAAELOTo7IFVWApMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBW1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_072", R"SYN(// BYTEBEAT 072 — en-poorten · melodie
// formule: t*(t>>12&t>>8&45&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>8&45&t>>4); }

void start() {
  bpm = 154;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 102);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEMORIAAQg5OgEtOhIAAQQ5OjIgVVYCmgAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_073", R"SYN(// BYTEBEAT 073 — trappen · akkoorden
// formule: (t>>4|t|t>>((t>>14)&15))*7+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>4|t|t>>((t>>14)&15))*7+((t>>10)&7); }

void start() {
  bpm = 161;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 33);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBDkSADsSABIAAQ45AQ86OTsBBzISAAEKOQEHOjAgVVYCoQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwEhVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRmwABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_074", R"SYN(// BYTEBEAT 074 — melodietabel · ritme
// formule: t*(0xBA98>>(t>>10&14)&15)|t>>6

uint8_t bb(uint32_t t) { return t*(0xBA98>>(t>>10&14)&15)|t>>6; }

void start() {
  bpm = 168;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 44);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wARAAAAAAABAAEBHgAAAEgAAANWEgACmLoAABIAAQo5AQ46OAEPOjISAAEGOTsgVVYCqAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwEsVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlGBAAEkAXgBAVcBAwQSAQEgOlGZAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGrAAEqATwBAVcBAwQSAQEPOgEPQFHAAAExAWQBAVcBAwQSAgFAOlHdAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH+AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAHgAGAB4ABwAnAAgALQAJADUACgA9AAsASAAOAEgADwBUABAAXQARAGwAEgCBABMAmQAUAKsAFQDAABYA3QAXAA==", 361 },
  { "bytebeat_075", R"SYN(// BYTEBEAT 075 — knars · drone
// formule: (t*(t>>4|t>>9))>>((t>>16)&7)

uint8_t bb(uint32_t t) { return (t*(t>>4|t>>9))>>((t>>16)&7); }

int vorige = -1;

void start() {
  bpm = 123;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 55);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABBDkSAAEJOTsyEgABEDkBBzo5IFVWAXsRBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBN1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_076", R"SYN(// BYTEBEAT 076 — xor-familie · melodie
// formule: ((t*(t>>8|t>>10)&63&t>>8))^(t&t>>12|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>10)&63&t>>8))^(t&t>>12|t>>5); }

void start() {
  bpm = 130;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 66);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEIORIAAQo5OzIBPzoSAAEIOToSABIAAQw5OhIAAQU5OzwgVVYCggAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFCVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "bytebeat_077", R"SYN(// BYTEBEAT 077 — modulo-ritme · akkoorden
// formule: (t>>12|t%24)&(t>>8|t%19)

uint8_t bb(uint32_t t) { return (t>>12|t%24)&(t>>8|t%19); }

void start() {
  bpm = 137;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 77);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABDDkSAAEYNjsSAAEIORIAARM2OzogVVYCiQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwFNVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_078", R"SYN(// BYTEBEAT 078 — vermenigvuldigers · ritme
// formule: t*3&(t>>3)|t*(t>>11&7)

uint8_t bb(uint32_t t) { return t*3&(t>>3)|t*(t>>11&7); }

void start() {
  bpm = 144;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 88);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEDOToSABIAAQs5AQc6MjsgVVYCkAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFYVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_079", R"SYN(// BYTEBEAT 079 — en-schuif · drone
// formule: t*(29&t>>11)

uint8_t bb(uint32_t t) { return t*(29&t>>11); }

int vorige = -1;

void start() {
  bpm = 151;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 99);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAAR0SAAELOToyIFVWApcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBY1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_080", R"SYN(// BYTEBEAT 080 — viznut-familie · melodie
// formule: t*((t>>11|t>>8)&31&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>11|t>>8)&31&t>>4); }

void start() {
  bpm = 158;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 30);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQg5OwEfOhIAAQQ5OjIgVVYCngAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwEeVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_081", R"SYN(// BYTEBEAT 081 — dubbele zaag · akkoorden
// formule: (t*3&t>>8)|(t*11&t>>11)

uint8_t bb(uint32_t t) { return (t*3&t>>8)|(t*11&t>>11); }

void start() {
  bpm = 165;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 41);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEIOToSAAELMhIAAQs5OjsgVVYCpQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwEpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_082", R"SYN(// BYTEBEAT 082 — en-poorten · ritme
// formule: t*(t>>10&t>>9&77&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>10&t>>9&77&t>>2); }

void start() {
  bpm = 120;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 52);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgASAAEKORIAAQk5OgFNOhIAAQI5OjIgVVYBeBEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwE0VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_083", R"SYN(// BYTEBEAT 083 — trappen · drone
// formule: (t>>7|t|t>>((t>>15)&15))*7+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>((t>>15)&15))*7+((t>>12)&7); }

int vorige = -1;

void start() {
  bpm = 127;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 63);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA/wATAAAAAAAIAAEBKwAAAFIAAAQBAT0RCQAEVhIAAQc5EgA7EgASAAEPOQEPOjk7AQcyEgABDDkBBzowIFVWAX8RBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBP1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSkQASAxAJAEEkUJMAAQFRsQABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRywABWlDNAAEoAQFXAAQEEAEAAQQ1AQBAUekAASMBZAEBVwEDBBIBAR86ARBAUf4AATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkAMQAKADcACwA/AAwARwANAFIAEABSABEAXgASAGcAEwB2ABQAfgAVAJYAFgCrABcAsQAZANMAGgDpABsA", 369 },
  { "bytebeat_084", R"SYN(// BYTEBEAT 084 — melodietabel · melodie
// formule: t*(0x4735>>(t>>11&14)&15)|t>>6

uint8_t bb(uint32_t t) { return t*(0x4735>>(t>>11&14)&15)|t>>6; }

void start() {
  bpm = 134;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 74);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA6AAQAAAAAAABAAEBHgAAAEgAAANWEgACNUcAABIAAQs5AQ46OAEPOjISAAEGOTsgVVYChgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFKVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRqAABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG9AAEkAXgBAVcBAwQSAgEHOgEDQFHSAAEmAV8BAVcBAwQSARICPAEBOlHnAAEqAUYBAVcBAwRWAQAEAB4ABgAeAAcAJwAIAC0ACQA1AAoAPQALAEgADgBIAA8AVAAQAF0AEQBsABIAhwATAKgAFAC9ABUA0gAWAA==", 334 },
  { "bytebeat_085", R"SYN(// BYTEBEAT 085 — knars · akkoorden
// formule: (t*(t>>5|t>>7))>>((t>>16)&7)

uint8_t bb(uint32_t t) { return (t*(t>>5|t>>7))>>((t>>16)&7); }

void start() {
  bpm = 141;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 85);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEFORIAAQc5OzISAAEQOQEHOjkgVVYCjQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFVVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_086", R"SYN(// BYTEBEAT 086 — xor-familie · ritme
// formule: ((t*(t>>7|t>>6)&27&t>>7))^(t&t>>11|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>6)&27&t>>7))^(t&t>>11|t>>4); }

void start() {
  bpm = 148;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 96);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQY5OzIBGzoSAAEHOToSABIAAQs5OhIAAQQ5OzwgVVYClAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFgVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_087", R"SYN(// BYTEBEAT 087 — modulo-ritme · drone
// formule: (t>>11|t%18)&(t>>8|t%21)

uint8_t bb(uint32_t t) { return (t>>11|t%18)&(t>>8|t%21); }

int vorige = -1;

void start() {
  bpm = 155;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 107);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQs5EgABEjY7EgABCDkSAAEVNjs6IFVWApsAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBa1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_088", R"SYN(// BYTEBEAT 088 — vermenigvuldigers · melodie
// formule: t*7&(t>>5)|t*(t>>11&7)

uint8_t bb(uint32_t t) { return t*7&(t>>5)|t*(t>>11&7); }

void start() {
  bpm = 162;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 38);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEFOToSABIAAQs5AQc6MjsgVVYCogAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwEmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_089", R"SYN(// BYTEBEAT 089 — en-schuif · akkoorden
// formule: t*(57&t>>12)

uint8_t bb(uint32_t t) { return t*(57&t>>12); }

void start() {
  bpm = 169;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 49);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABORIAAQw5OjIgVVYCqQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwExVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRhgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_090", R"SYN(// BYTEBEAT 090 — viznut-familie · ritme
// formule: t*((t>>12|t>>10)&25&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>10)&25&t>>4); }

void start() {
  bpm = 124;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 60);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgASAAEMORIAAQo5OwEZOhIAAQQ5OjIgVVYBfBEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwE8VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_091", R"SYN(// BYTEBEAT 091 — dubbele zaag · drone
// formule: (t*9&t>>6)|(t*11&t>>10)

uint8_t bb(uint32_t t) { return (t*9&t>>6)|(t*11&t>>10); }

int vorige = -1;

void start() {
  bpm = 131;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 71);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQkyEgABBjk6EgABCzISAAEKOTo7IFVWAoMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBR1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_092", R"SYN(// BYTEBEAT 092 — en-poorten · melodie
// formule: t*(t>>11&t>>7&99&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>7&99&t>>3); }

void start() {
  bpm = 138;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 82);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQc5OgFjOhIAAQM5OjIgVVYCigAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFSVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_093", R"SYN(// BYTEBEAT 093 — trappen · akkoorden
// formule: (t>>5|t|t>>((t>>16)&15))*10+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>5|t|t>>((t>>16)&15))*10+((t>>11)&7); }

void start() {
  bpm = 145;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 93);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBTkSADsSABIAARA5AQ86OTsBCjISAAELOQEHOjAgVVYCkQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFdVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRmwABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_094", R"SYN(// BYTEBEAT 094 — melodietabel · ritme
// formule: t*(0xA876>>(t>>10&14)&15)|t>>8

uint8_t bb(uint32_t t) { return t*(0xA876>>(t>>10&14)&15)|t>>8; }

void start() {
  bpm = 152;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 104);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wARAAAAAAABAAEBHgAAAEgAAANWEgACdqgAABIAAQo5AQ46OAEPOjISAAEIOTsgVVYCmAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGBAAEkAXgBAVcBAwQSAQEgOlGZAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGrAAEqATwBAVcBAwQSAQEPOgEPQFHAAAExAWQBAVcBAwQSAgFAOlHdAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH+AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAHgAGAB4ABwAnAAgALQAJADUACgA9AAsASAAOAEgADwBUABAAXQARAGwAEgCBABMAmQAUAKsAFQDAABYA3QAXAA==", 361 },
  { "bytebeat_095", R"SYN(// BYTEBEAT 095 — knars · drone
// formule: (t*(t>>3|t>>9))>>((t>>13)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>9))>>((t>>13)&7); }

int vorige = -1;

void start() {
  bpm = 159;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 35);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABAzkSAAEJOTsyEgABDTkBBzo5IFVWAp8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBI1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_096", R"SYN(// BYTEBEAT 096 — xor-familie · melodie
// formule: ((t*(t>>9|t>>6)&63&t>>9))^(t&t>>13|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>6)&63&t>>9))^(t&t>>13|t>>4); }

void start() {
  bpm = 166;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 46);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQY5OzIBPzoSAAEJOToSABIAAQ05OhIAAQQ5OzwgVVYCpgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwEuVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "bytebeat_097", R"SYN(// BYTEBEAT 097 — modulo-ritme · akkoorden
// formule: (t>>12|t%40)&(t>>7|t%21)

uint8_t bb(uint32_t t) { return (t>>12|t%40)&(t>>7|t%21); }

void start() {
  bpm = 121;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 57);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAEQAAAAAAABAAEBGwAAAEIAAANWEgABDDkSAAEoNjsSAAEHORIAARU2OzogVVYBeREEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwE5VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRjwABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLCABIBAUE6AUFAJFDEAAEBUdEAASQBcwEBVwEDBBIBAQM4AQM6AQJAUekAAScBWgEBVwEDBBABAAECNVH3AAEqUPkAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgCPABMAqgAUANEAFQDpABYA", 366 },
  { "bytebeat_098", R"SYN(// BYTEBEAT 098 — vermenigvuldigers · ritme
// formule: t*11&(t>>3)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*11&(t>>3)|t*(t>>9&7); }

void start() {
  bpm = 128;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 68);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABCzISAAEDOToSABIAAQk5AQc6MjsgVVYCgAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFEVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_099", R"SYN(// BYTEBEAT 099 — en-schuif · drone
// formule: t*(77&t>>12)

uint8_t bb(uint32_t t) { return t*(77&t>>12); }

int vorige = -1;

void start() {
  bpm = 135;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 79);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAAU0SAAEMOToyIFVWAocAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBT1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_100", R"SYN(// BYTEBEAT 100 — viznut-familie · melodie
// formule: t*((t>>13|t>>8)&25&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>13|t>>8)&25&t>>6); }

void start() {
  bpm = 142;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 90);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQg5OwEZOhIAAQY5OjIgVVYCjgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwFaVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_101", R"SYN(// BYTEBEAT 101 — dubbele zaag · akkoorden
// formule: (t*7&t>>7)|(t*5&t>>9)

uint8_t bb(uint32_t t) { return (t*7&t>>7)|(t*5&t>>9); }

void start() {
  bpm = 149;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 101);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEHOToSAAEFMhIAAQk5OjsgVVYClQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwFlVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_102", R"SYN(// BYTEBEAT 102 — en-poorten · ritme
// formule: t*(t>>13&t>>9&45&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>13&t>>9&45&t>>4); }

void start() {
  bpm = 156;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 32);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQk5OgEtOhIAAQQ5OjIgVVYCnAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwEgVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_103", R"SYN(// BYTEBEAT 103 — trappen · drone
// formule: (t>>6|t|t>>((t>>14)&15))*10+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>6|t|t>>((t>>14)&15))*10+((t>>10)&7); }

int vorige = -1;

void start() {
  bpm = 163;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 43);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQY5EgA7EgASAAEOOQEPOjk7AQoyEgABCjkBBzowIFVWAqMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBK1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_104", R"SYN(// BYTEBEAT 104 — melodietabel · melodie
// formule: t*(0x9753>>(t>>9&14)&15)|t>>7

uint8_t bb(uint32_t t) { return t*(0x9753>>(t>>9&14)&15)|t>>7; }

void start() {
  bpm = 118;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 54);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBHgAAAEUAAANWEgACU5cAABIAAQk5AQ46OAEPOjISAAEHOTsgVVYBdhEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwE2VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEAB4ABgAeAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_105", R"SYN(// BYTEBEAT 105 — knars · akkoorden
// formule: (t*(t>>6|t>>7))>>((t>>13)&7)

uint8_t bb(uint32_t t) { return (t*(t>>6|t>>7))>>((t>>13)&7); }

void start() {
  bpm = 125;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 65);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAEQAAAAAAABAAEBGwAAAEIAAANWEgASAAEGORIAAQc5OzISAAENOQEHOjkgVVYBfREEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFBVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRjwABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLCABIBAUE6AUFAJFDEAAEBUdEAASQBcwEBVwEDBBIBAQM4AQM6AQJAUekAAScBWgEBVwEDBBABAAECNVH3AAEqUPkAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgCPABMAqgAUANEAFQDpABYA", 366 },
  { "bytebeat_106", R"SYN(// BYTEBEAT 106 — xor-familie · ritme
// formule: ((t*(t>>8|t>>9)&27&t>>8))^(t&t>>12|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>9)&27&t>>8))^(t&t>>12|t>>6); }

void start() {
  bpm = 132;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 76);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEIORIAAQk5OzIBGzoSAAEIOToSABIAAQw5OhIAAQY5OzwgVVYChAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFMVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_107", R"SYN(// BYTEBEAT 107 — modulo-ritme · drone
// formule: (t>>13|t%32)&(t>>6|t%23)

uint8_t bb(uint32_t t) { return (t>>13|t%32)&(t>>6|t%23); }

int vorige = -1;

void start() {
  bpm = 139;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 87);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQ05EgABIDY7EgABBjkSAAEXNjs6IFVWAosAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBV1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_108", R"SYN(// BYTEBEAT 108 — vermenigvuldigers · melodie
// formule: t*5&(t>>5)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*5&(t>>5)|t*(t>>9&7); }

void start() {
  bpm = 146;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 98);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABBTISAAEFOToSABIAAQk5AQc6MjsgVVYCkgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwFiVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_109", R"SYN(// BYTEBEAT 109 — en-schuif · akkoorden
// formule: t*(21&t>>9)

uint8_t bb(uint32_t t) { return t*(21&t>>9); }

void start() {
  bpm = 153;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 109);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABFRIAAQk5OjIgVVYCmQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFtVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRhgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_110", R"SYN(// BYTEBEAT 110 — viznut-familie · ritme
// formule: t*((t>>9|t>>10)&47&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>10)&47&t>>6); }

void start() {
  bpm = 160;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 40);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEJORIAAQo5OwEvOhIAAQY5OjIgVVYCoAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwEoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_111", R"SYN(// BYTEBEAT 111 — dubbele zaag · drone
// formule: (t*5&t>>8)|(t*5&t>>11)

uint8_t bb(uint32_t t) { return (t*5&t>>8)|(t*5&t>>11); }

int vorige = -1;

void start() {
  bpm = 167;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 51);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQUyEgABCDk6EgABBTISAAELOTo7IFVWAqcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBM1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_112", R"SYN(// BYTEBEAT 112 — en-poorten · melodie
// formule: t*(t>>12&t>>7&63&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>7&63&t>>2); }

void start() {
  bpm = 122;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 62);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgASAAEMORIAAQc5OgE/OhIAAQI5OjIgVVYBehEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwE+VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_113", R"SYN(// BYTEBEAT 113 — trappen · akkoorden
// formule: (t>>4|t|t>>((t>>16)&15))*5+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>4|t|t>>((t>>16)&15))*5+((t>>10)&7); }

void start() {
  bpm = 129;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 73);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBDkSADsSABIAARA5AQ86OTsBBTISAAEKOQEHOjAgVVYCgQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFJVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRmwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_114", R"SYN(// BYTEBEAT 114 — melodietabel · ritme
// formule: t*(0x7A59>>(t>>11&14)&15)|t>>7

uint8_t bb(uint32_t t) { return t*(0x7A59>>(t>>11&14)&15)|t>>7; }

void start() {
  bpm = 136;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 84);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wARAAAAAAABAAEBHgAAAEgAAANWEgACWXoAABIAAQs5AQ46OAEPOjISAAEHOTsgVVYCiAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFUVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlGBAAEkAXgBAVcBAwQSAQEgOlGZAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGrAAEqATwBAVcBAwQSAQEPOgEPQFHAAAExAWQBAVcBAwQSAgFAOlHdAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH+AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAHgAGAB4ABwAnAAgALQAJADUACgA9AAsASAAOAEgADwBUABAAXQARAGwAEgCBABMAmQAUAKsAFQDAABYA3QAXAA==", 361 },
  { "bytebeat_115", R"SYN(// BYTEBEAT 115 — knars · drone
// formule: (t*(t>>4|t>>8))>>((t>>14)&7)

uint8_t bb(uint32_t t) { return (t*(t>>4|t>>8))>>((t>>14)&7); }

int vorige = -1;

void start() {
  bpm = 143;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 95);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABBDkSAAEIOTsyEgABDjkBBzo5IFVWAo8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBX1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_116", R"SYN(// BYTEBEAT 116 — xor-familie · melodie
// formule: ((t*(t>>7|t>>9)&46&t>>7))^(t&t>>11|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>9)&46&t>>7))^(t&t>>11|t>>6); }

void start() {
  bpm = 150;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 106);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQk5OzIBLjoSAAEHOToSABIAAQs5OhIAAQY5OzwgVVYClgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFqVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "bytebeat_117", R"SYN(// BYTEBEAT 117 — modulo-ritme · akkoorden
// formule: (t>>11|t%27)&(t>>8|t%23)

uint8_t bb(uint32_t t) { return (t>>11|t%27)&(t>>8|t%23); }

void start() {
  bpm = 157;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 37);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABCzkSAAEbNjsSAAEIORIAARc2OzogVVYCnQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwElVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_118", R"SYN(// BYTEBEAT 118 — vermenigvuldigers · ritme
// formule: t*9&(t>>4)|t*(t>>10&7)

uint8_t bb(uint32_t t) { return t*9&(t>>4)|t*(t>>10&7); }

void start() {
  bpm = 164;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 48);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEEOToSABIAAQo5AQc6MjsgVVYCpAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwEwVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_119", R"SYN(// BYTEBEAT 119 — en-schuif · drone
// formule: t*(51&t>>9)

uint8_t bb(uint32_t t) { return t*(51&t>>9); }

int vorige = -1;

void start() {
  bpm = 119;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 59);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA6gATAAAAAAAIAAEBFgAAAD0AAAQBAT0RCQAEVhIAATMSAAEJOToyIFVWAXcRBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBO1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfAASAxAJAEEkUH4AAQFRnAABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRtgABWlC4AAEoAQFXAAQEEAEAAQQ1AQBAUdQAASMBZAEBVwEDBBIBAR86ARBAUekAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHAAKACIACwAqAAwAMgANAD0AEAA9ABEASQASAFIAEwBhABQAaQAVAIEAFgCWABcAnAAZAL4AGgDUABsA", 348 },
  { "bytebeat_120", R"SYN(// BYTEBEAT 120 — viznut-familie · melodie
// formule: t*((t>>11|t>>7)&123&t>>5)

uint8_t bb(uint32_t t) { return t*((t>>11|t>>7)&123&t>>5); }

void start() {
  bpm = 126;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 70);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgASAAELORIAAQc5OwF7OhIAAQU5OjIgVVYBfhEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwFGVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_121", R"SYN(// BYTEBEAT 121 — dubbele zaag · akkoorden
// formule: (t*3&t>>7)|(t*2&t>>10)

uint8_t bb(uint32_t t) { return (t*3&t>>7)|(t*2&t>>10); }

void start() {
  bpm = 133;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 81);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEHOToSAAECMhIAAQo5OjsgVVYChQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwFRVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_122", R"SYN(// BYTEBEAT 122 — en-poorten · ritme
// formule: t*(t>>10&t>>8&99&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>10&t>>8&99&t>>3); }

void start() {
  bpm = 140;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 92);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEKORIAAQg5OgFjOhIAAQM5OjIgVVYCjAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwFcVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_123", R"SYN(// BYTEBEAT 123 — trappen · drone
// formule: (t>>7|t|t>>((t>>14)&15))*5+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>((t>>14)&15))*5+((t>>12)&7); }

int vorige = -1;

void start() {
  bpm = 147;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 103);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQc5EgA7EgASAAEOOQEPOjk7AQUyEgABDDkBBzowIFVWApMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBZ1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_124", R"SYN(// BYTEBEAT 124 — melodietabel · melodie
// formule: t*(0x5432>>(t>>10&14)&15)|t>>6

uint8_t bb(uint32_t t) { return t*(0x5432>>(t>>10&14)&15)|t>>6; }

void start() {
  bpm = 154;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 34);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA6AAQAAAAAAABAAEBHgAAAEgAAANWEgACMlQAABIAAQo5AQ46OAEPOjISAAEGOTsgVVYCmgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwEiVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRqAABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG9AAEkAXgBAVcBAwQSAgEHOgEDQFHSAAEmAV8BAVcBAwQSARICPAEBOlHnAAEqAUYBAVcBAwRWAQAEAB4ABgAeAAcAJwAIAC0ACQA1AAoAPQALAEgADgBIAA8AVAAQAF0AEQBsABIAhwATAKgAFAC9ABUA0gAWAA==", 334 },
  { "bytebeat_125", R"SYN(// BYTEBEAT 125 — knars · akkoorden
// formule: (t*(t>>5|t>>9))>>((t>>14)&7)

uint8_t bb(uint32_t t) { return (t*(t>>5|t>>9))>>((t>>14)&7); }

void start() {
  bpm = 161;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 45);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEFORIAAQk5OzISAAEOOQEHOjkgVVYCoQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwEtVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_126", R"SYN(// BYTEBEAT 126 — xor-familie · ritme
// formule: ((t*(t>>9|t>>10)&31&t>>9))^(t&t>>13|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>10)&31&t>>9))^(t&t>>13|t>>5); }

void start() {
  bpm = 168;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 56);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQo5OzIBHzoSAAEJOToSABIAAQ05OhIAAQU5OzwgVVYCqAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwE4VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_127", R"SYN(// BYTEBEAT 127 — modulo-ritme · drone
// formule: (t>>13|t%24)&(t>>7|t%15)

uint8_t bb(uint32_t t) { return (t>>13|t%24)&(t>>7|t%15); }

int vorige = -1;

void start() {
  bpm = 123;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 67);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAAQ05EgABGDY7EgABBzkSAAEPNjs6IFVWAXsRBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBQ1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_128", R"SYN(// BYTEBEAT 128 — vermenigvuldigers · melodie
// formule: t*3&(t>>3)|t*(t>>10&7)

uint8_t bb(uint32_t t) { return t*3&(t>>3)|t*(t>>10&7); }

void start() {
  bpm = 130;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 78);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEDOToSABIAAQo5AQc6MjsgVVYCggAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwFOVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_129", R"SYN(// BYTEBEAT 129 — en-schuif · akkoorden
// formule: t*(117&t>>9)

uint8_t bb(uint32_t t) { return t*(117&t>>9); }

void start() {
  bpm = 137;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 89);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABdRIAAQk5OjIgVVYCiQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFZVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRhgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_130", R"SYN(// BYTEBEAT 130 — viznut-familie · ritme
// formule: t*((t>>12|t>>8)&63&t>>5)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>8)&63&t>>5); }

void start() {
  bpm = 144;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 100);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEMORIAAQg5OwE/OhIAAQU5OjIgVVYCkAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwFkVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_131", R"SYN(// BYTEBEAT 131 — dubbele zaag · drone
// formule: (t*9&t>>8)|(t*2&t>>9)

uint8_t bb(uint32_t t) { return (t*9&t>>8)|(t*2&t>>9); }

int vorige = -1;

void start() {
  bpm = 151;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 31);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQkyEgABCDk6EgABAjISAAEJOTo7IFVWApcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBH1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_132", R"SYN(// BYTEBEAT 132 — en-poorten · melodie
// formule: t*(t>>11&t>>9&123&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>9&123&t>>4); }

void start() {
  bpm = 158;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 42);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQk5OgF7OhIAAQQ5OjIgVVYCngAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwEqVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_133", R"SYN(// BYTEBEAT 133 — trappen · akkoorden
// formule: (t>>5|t|t>>((t>>15)&15))*12+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>5|t|t>>((t>>15)&15))*12+((t>>11)&7); }

void start() {
  bpm = 165;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 53);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBTkSADsSABIAAQ85AQ86OTsBDDISAAELOQEHOjAgVVYCpQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwE1VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRmwABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_134", R"SYN(// BYTEBEAT 134 — melodietabel · ritme
// formule: t*(0x8A9C>>(t>>11&14)&15)|t>>6

uint8_t bb(uint32_t t) { return t*(0x8A9C>>(t>>11&14)&15)|t>>6; }

void start() {
  bpm = 120;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 64);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBHgAAAEUAAANWEgACnIoAABIAAQs5AQ46OAEPOjISAAEGOTsgVVYBeBEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFAVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAHgAGAB4ABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_135", R"SYN(// BYTEBEAT 135 — knars · drone
// formule: (t*(t>>3|t>>8))>>((t>>15)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>8))>>((t>>15)&7); }

int vorige = -1;

void start() {
  bpm = 127;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 75);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABAzkSAAEIOTsyEgABDzkBBzo5IFVWAX8RBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBS1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_136", R"SYN(// BYTEBEAT 136 — xor-familie · melodie
// formule: ((t*(t>>8|t>>10)&46&t>>8))^(t&t>>12|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>10)&46&t>>8))^(t&t>>12|t>>5); }

void start() {
  bpm = 134;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 86);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEIORIAAQo5OzIBLjoSAAEIOToSABIAAQw5OhIAAQU5OzwgVVYChgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFWVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "bytebeat_137", R"SYN(// BYTEBEAT 137 — modulo-ritme · akkoorden
// formule: (t>>11|t%18)&(t>>6|t%15)

uint8_t bb(uint32_t t) { return (t>>11|t%18)&(t>>6|t%15); }

void start() {
  bpm = 141;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 97);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABCzkSAAESNjsSAAEGORIAAQ82OzogVVYCjQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwFhVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_138", R"SYN(// BYTEBEAT 138 — vermenigvuldigers · ritme
// formule: t*7&(t>>4)|t*(t>>12&7)

uint8_t bb(uint32_t t) { return t*7&(t>>4)|t*(t>>12&7); }

void start() {
  bpm = 148;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 108);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEEOToSABIAAQw5AQc6MjsgVVYClAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFsVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_139", R"SYN(// BYTEBEAT 139 — en-schuif · drone
// formule: t*(23&t>>10)

uint8_t bb(uint32_t t) { return t*(23&t>>10); }

int vorige = -1;

void start() {
  bpm = 155;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 39);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAARcSAAEKOToyIFVWApsAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBJ1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_140", R"SYN(// BYTEBEAT 140 — viznut-familie · melodie
// formule: t*((t>>13|t>>7)&31&t>>3)

uint8_t bb(uint32_t t) { return t*((t>>13|t>>7)&31&t>>3); }

void start() {
  bpm = 162;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 50);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQc5OwEfOhIAAQM5OjIgVVYCogAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwEyVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_141", R"SYN(// BYTEBEAT 141 — dubbele zaag · akkoorden
// formule: (t*7&t>>6)|(t*3&t>>11)

uint8_t bb(uint32_t t) { return (t*7&t>>6)|(t*3&t>>11); }

void start() {
  bpm = 169;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 61);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEGOToSAAEDMhIAAQs5OjsgVVYCqQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwE9VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_142", R"SYN(// BYTEBEAT 142 — en-poorten · ritme
// formule: t*(t>>13&t>>8&63&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>13&t>>8&63&t>>4); }

void start() {
  bpm = 124;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 72);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgASAAENORIAAQg5OgE/OhIAAQQ5OjIgVVYBfBEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwFIVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_143", R"SYN(// BYTEBEAT 143 — trappen · drone
// formule: (t>>6|t|t>>((t>>16)&15))*12+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>6|t|t>>((t>>16)&15))*12+((t>>10)&7); }

int vorige = -1;

void start() {
  bpm = 131;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 83);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQY5EgA7EgASAAEQOQEPOjk7AQwyEgABCjkBBzowIFVWAoMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBU1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_144", R"SYN(// BYTEBEAT 144 — knars · melodie
// formule: (t*(t>>6|t>>9))>>((t>>15)&7)

uint8_t bb(uint32_t t) { return (t*(t>>6|t>>9))>>((t>>15)&7); }

void start() {
  bpm = 138;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 94);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEGORIAAQk5OzISAAEPOQEHOjkgVVYCigAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFeVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_145", R"SYN(// BYTEBEAT 145 — xor-familie · akkoorden
// formule: ((t*(t>>7|t>>6)&31&t>>7))^(t&t>>11|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>6)&31&t>>7))^(t&t>>11|t>>4); }

void start() {
  bpm = 145;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 105);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAGgEQAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQY5OzIBHzoSAAEHOToSABIAAQs5OhIAAQQ5OzwgVVYCkQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRoQABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLUABIBAUE6AUFAJFDWAAEBUeMAASQBcwEBVwEDBBIBAQM4AQM6AQJAUfsAAScBWgEBVwEDBBABAAECNVEJAQEqUAsBASwBKBICAT86MAEBVwEDBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgChABMAvAAUAOMAFQD7ABYA", 384 },
  { "bytebeat_146", R"SYN(// BYTEBEAT 146 — modulo-ritme · ritme
// formule: (t>>12|t%40)&(t>>8|t%19)

uint8_t bb(uint32_t t) { return (t>>12|t%40)&(t>>8|t%19); }

void start() {
  bpm = 152;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 36);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABDDkSAAEoNjsSAAEIORIAARM2OzogVVYCmAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwEkVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_147", R"SYN(// BYTEBEAT 147 — vermenigvuldigers · drone
// formule: t*11&(t>>3)|t*(t>>12&7)

uint8_t bb(uint32_t t) { return t*11&(t>>3)|t*(t>>12&7); }

int vorige = -1;

void start() {
  bpm = 159;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 47);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQsyEgABAzk6EgASAAEMOQEHOjI7IFVWAp8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBL1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_148", R"SYN(// BYTEBEAT 148 — en-schuif · melodie
// formule: t*(77&t>>11)

uint8_t bb(uint32_t t) { return t*(77&t>>11); }

void start() {
  bpm = 166;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 58);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA2QAQAAAAAAABAAEBDwAAADkAAANWEgABTRIAAQs5OjIgVVYCpgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwE6VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRmQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlGuAAEkAXgBAVcBAwQSAgEHOgEDQFHDAAEmAV8BAVcBAwQSARICPAEBOlHYAAEqAUYBAVcBAwRWAQAEAA8ABgAPAAcAGAAIAB4ACQAmAAoALgALADkADgA5AA8ARQAQAE4AEQBdABIAeAATAJkAFACuABUAwwAWAA==", 319 },
  { "bytebeat_149", R"SYN(// BYTEBEAT 149 — viznut-familie · akkoorden
// formule: t*((t>>9|t>>8)&25&t>>3)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>8)&25&t>>3); }

void start() {
  bpm = 121;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 69);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAEQAAAAAAABAAEBGwAAAEIAAANWEgASAAEJORIAAQg5OwEZOhIAAQM5OjIgVVYBeREEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFFVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRjwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLCABIBAUE6AUFAJFDEAAEBUdEAASQBcwEBVwEDBBIBAQM4AQM6AQJAUekAAScBWgEBVwEDBBABAAECNVH3AAEqUPkAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgCPABMAqgAUANEAFQDpABYA", 366 },
  { "bytebeat_150", R"SYN(// BYTEBEAT 150 — dubbele zaag · ritme
// formule: (t*3&t>>7)|(t*11&t>>9)

uint8_t bb(uint32_t t) { return (t*3&t>>7)|(t*11&t>>9); }

void start() {
  bpm = 128;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 80);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEHOToSAAELMhIAAQk5OjsgVVYCgAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwFQVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_151", R"SYN(// BYTEBEAT 151 — en-poorten · drone
// formule: t*(t>>12&t>>9&77&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>9&77&t>>2); }

int vorige = -1;

void start() {
  bpm = 135;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 91);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABDDkSAAEJOToBTToSAAECOToyIFVWAocAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBW1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_152", R"SYN(// BYTEBEAT 152 — trappen · melodie
// formule: (t>>4|t|t>>((t>>15)&15))*7+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>4|t|t>>((t>>15)&15))*7+((t>>12)&7); }

void start() {
  bpm = 142;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 102);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA7gAQAAAAAAABAAEBJAAAAE4AAANWEgABBDkSADsSABIAAQ85AQ86OTsBBzISAAEMOQEHOjAgVVYCjgAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRrgABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHDAAEkAXgBAVcBAwQSAgEHOgEDQFHYAAEmAV8BAVcBAwQSARICPAEBOlHtAAEqAUYBAVcBAwRWAQAEACQABgAkAAcALQAIADMACQA7AAoAQwALAE4ADgBOAA8AWgAQAGMAEQByABIAjQATAK4AFADDABUA2AAWAA==", 340 },
  { "bytebeat_153", R"SYN(// BYTEBEAT 153 — knars · akkoorden
// formule: (t*(t>>4|t>>7))>>((t>>16)&7)

uint8_t bb(uint32_t t) { return (t*(t>>4|t>>7))>>((t>>16)&7); }

void start() {
  bpm = 149;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 33);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEEORIAAQc5OzISAAEQOQEHOjkgVVYClQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwEhVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_154", R"SYN(// BYTEBEAT 154 — xor-familie · ritme
// formule: ((t*(t>>9|t>>6)&27&t>>9))^(t&t>>11|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>6)&27&t>>9))^(t&t>>11|t>>4); }

void start() {
  bpm = 156;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 44);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQY5OzIBGzoSAAEJOToSABIAAQs5OhIAAQQ5OzwgVVYCnAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwEsVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_155", R"SYN(// BYTEBEAT 155 — modulo-ritme · drone
// formule: (t>>13|t%32)&(t>>7|t%19)

uint8_t bb(uint32_t t) { return (t>>13|t%32)&(t>>7|t%19); }

int vorige = -1;

void start() {
  bpm = 163;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 55);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQ05EgABIDY7EgABBzkSAAETNjs6IFVWAqMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBN1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_156", R"SYN(// BYTEBEAT 156 — vermenigvuldigers · melodie
// formule: t*5&(t>>5)|t*(t>>11&7)

uint8_t bb(uint32_t t) { return t*5&(t>>5)|t*(t>>11&7); }

void start() {
  bpm = 118;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 66);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgABBTISAAEFOToSABIAAQs5AQc6MjsgVVYBdhEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFCVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_157", R"SYN(// BYTEBEAT 157 — en-schuif · akkoorden
// formule: t*(85&t>>11)

uint8_t bb(uint32_t t) { return t*(85&t>>11); }

void start() {
  bpm = 125;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 77);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AAQAAAAAAABAAEBDwAAADYAAANWEgABVRIAAQs5OjIgVVYBfREEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwFNVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRgwABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK2ABIBAUE6AUFAJFC4AAEBUcUAASQBcwEBVwEDBBIBAQM4AQM6AQJAUd0AAScBWgEBVwEDBBABAAECNVHrAAEqUO0AASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAVAAgAGwAJACMACgArAAsANgAOADYADwBCABAASwARAFoAEgCDABMAngAUAMUAFQDdABYA", 354 },
  { "bytebeat_158", R"SYN(// BYTEBEAT 158 — viznut-familie · ritme
// formule: t*((t>>11|t>>10)&47&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>11|t>>10)&47&t>>4); }

void start() {
  bpm = 132;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 88);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQo5OwEvOhIAAQQ5OjIgVVYChAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFYVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_159", R"SYN(// BYTEBEAT 159 — dubbele zaag · drone
// formule: (t*3&t>>6)|(t*11&t>>10)

uint8_t bb(uint32_t t) { return (t*3&t>>6)|(t*11&t>>10); }

int vorige = -1;

void start() {
  bpm = 139;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 99);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQMyEgABBjk6EgABCzISAAEKOTo7IFVWAosAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBY1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_160", R"SYN(// BYTEBEAT 160 — en-poorten · melodie
// formule: t*(t>>10&t>>7&123&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>10&t>>7&123&t>>3); }

void start() {
  bpm = 146;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 30);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEKORIAAQc5OgF7OhIAAQM5OjIgVVYCkgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwEeVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_161", R"SYN(// BYTEBEAT 161 — trappen · akkoorden
// formule: (t>>7|t|t>>((t>>16)&15))*7+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>((t>>16)&15))*7+((t>>11)&7); }

void start() {
  bpm = 153;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 41);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBzkSADsSABIAARA5AQ86OTsBBzISAAELOQEHOjAgVVYCmQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwEpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRmwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_162", R"SYN(// BYTEBEAT 162 — knars · ritme
// formule: (t*(t>>3|t>>8))>>((t>>13)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>8))>>((t>>13)&7); }

void start() {
  bpm = 160;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 52);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEDORIAAQg5OzISAAENOQEHOjkgVVYCoAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwE0VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_163", R"SYN(// BYTEBEAT 163 — xor-familie · drone
// formule: ((t*(t>>8|t>>9)&63&t>>8))^(t&t>>13|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>9)&63&t>>8))^(t&t>>13|t>>6); }

int vorige = -1;

void start() {
  bpm = 167;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 63);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAACAETAAAAAAAIAAEBMQAAAFsAAAQBAT0RCQAEVhIAEgABCDkSAAEJOTsyAT86EgABCDk6EgASAAENOToSAAEGOTs8IFVWAqcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBP1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSmgASAxAJAEEkUJwAAQFRugABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpR1AABWlDWAAEoAQFXAAQEEAEAAQQ1AQBAUfIAASMBZAEBVwEDBBIBAR86ARBAUQcBATYBWgEBVwEDBFYAAAYACAAEADEACAAxAAkAOgAKAEAACwBIAAwAUAANAFsAEABbABEAZwASAHAAEwB/ABQAhwAVAJ8AFgC0ABcAugAZANwAGgDyABsA", 378 },
  { "bytebeat_164", R"SYN(// BYTEBEAT 164 — modulo-ritme · melodie
// formule: (t>>12|t%27)&(t>>7|t%21)

uint8_t bb(uint32_t t) { return (t>>12|t%27)&(t>>7|t%21); }

void start() {
  bpm = 122;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 74);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgABDDkSAAEbNjsSAAEHORIAARU2OzogVVYBehEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFKVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_165", R"SYN(// BYTEBEAT 165 — vermenigvuldigers · akkoorden
// formule: t*9&(t>>4)|t*(t>>11&7)

uint8_t bb(uint32_t t) { return t*9&(t>>4)|t*(t>>11&7); }

void start() {
  bpm = 129;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 85);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEEOToSABIAAQs5AQc6MjsgVVYCgQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFVVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_166", R"SYN(// BYTEBEAT 166 — en-schuif · ritme
// formule: t*(91&t>>11)

uint8_t bb(uint32_t t) { return t*(91&t>>11); }

void start() {
  bpm = 136;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 96);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA8AARAAAAAAABAAEBDwAAADkAAANWEgABWxIAAQs5OjIgVVYCiAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFgVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlFyAAEkAXgBAVcBAwQSAQEgOlGKAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGcAAEqATwBAVcBAwQSAQEPOgEPQFGxAAExAWQBAVcBAwQSAgFAOlHOAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFHvAAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgByABMAigAUAJwAFQCxABYAzgAXAA==", 346 },
  { "bytebeat_167", R"SYN(// BYTEBEAT 167 — viznut-familie · drone
// formule: t*((t>>12|t>>7)&123&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>7)&123&t>>4); }

int vorige = -1;

void start() {
  bpm = 143;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 107);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABDDkSAAEHOTsBezoSAAEEOToyIFVWAo8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBa1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_168", R"SYN(// BYTEBEAT 168 — dubbele zaag · melodie
// formule: (t*9&t>>7)|(t*11&t>>9)

uint8_t bb(uint32_t t) { return (t*9&t>>7)|(t*11&t>>9); }

void start() {
  bpm = 150;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 38);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEHOToSAAELMhIAAQk5OjsgVVYClgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwEmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_169", R"SYN(// BYTEBEAT 169 — en-poorten · akkoorden
// formule: t*(t>>11&t>>8&45&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>8&45&t>>4); }

void start() {
  bpm = 157;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 49);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQg5OgEtOhIAAQQ5OjIgVVYCnQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwExVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_170", R"SYN(// BYTEBEAT 170 — trappen · ritme
// formule: (t>>5|t|t>>((t>>14)&15))*10+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>5|t|t>>((t>>14)&15))*10+((t>>10)&7); }

void start() {
  bpm = 164;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 60);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAABQERAAAAAAABAAEBJAAAAE4AAANWEgABBTkSADsSABIAAQ45AQ86OTsBCjISAAEKOQEHOjAgVVYCpAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwE8VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlGHAAEkAXgBAVcBAwQSAQEgOlGfAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGxAAEqATwBAVcBAwQSAQEPOgEPQFHGAAExAWQBAVcBAwQSAgFAOlHjAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEEAQECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCHABMAnwAUALEAFQDGABYA4wAXAA==", 367 },
  { "bytebeat_171", R"SYN(// BYTEBEAT 171 — knars · drone
// formule: (t*(t>>3|t>>7))>>((t>>13)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>7))>>((t>>13)&7); }

int vorige = -1;

void start() {
  bpm = 119;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 71);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABAzkSAAEHOTsyEgABDTkBBzo5IFVWAXcRBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBR1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_172", R"SYN(// BYTEBEAT 172 — xor-familie · melodie
// formule: ((t*(t>>7|t>>9)&27&t>>7))^(t&t>>12|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>9)&27&t>>7))^(t&t>>12|t>>6); }

void start() {
  bpm = 126;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 82);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA8QAQAAAAAAABAAEBKgAAAFEAAANWEgASAAEHORIAAQk5OzIBGzoSAAEHOToSABIAAQw5OhIAAQY5OzwgVVYBfhEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFSVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRsQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHGAAEkAXgBAVcBAwQSAgEHOgEDQFHbAAEmAV8BAVcBAwQSARICPAEBOlHwAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMAAIADYACQA+AAoARgALAFEADgBRAA8AXQAQAGYAEQB1ABIAkAATALEAFADGABUA2wAWAA==", 343 },
  { "bytebeat_173", R"SYN(// BYTEBEAT 173 — modulo-ritme · akkoorden
// formule: (t>>13|t%24)&(t>>6|t%21)

uint8_t bb(uint32_t t) { return (t>>13|t%24)&(t>>6|t%21); }

void start() {
  bpm = 133;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 93);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABDTkSAAEYNjsSAAEGORIAARU2OzogVVYChQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFdVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_174", R"SYN(// BYTEBEAT 174 — vermenigvuldigers · ritme
// formule: t*3&(t>>5)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*3&(t>>5)|t*(t>>9&7); }

void start() {
  bpm = 140;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 104);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABAzISAAEFOToSABIAAQk5AQc6MjsgVVYCjAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_175", R"SYN(// BYTEBEAT 175 — en-schuif · drone
// formule: t*(13&t>>12)

uint8_t bb(uint32_t t) { return t*(13&t>>12); }

int vorige = -1;

void start() {
  bpm = 147;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 35);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAAQ0SAAEMOToyIFVWApMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBI1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_176", R"SYN(// BYTEBEAT 176 — viznut-familie · melodie
// formule: t*((t>>13|t>>10)&123&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>13|t>>10)&123&t>>6); }

void start() {
  bpm = 154;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 46);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQo5OwF7OhIAAQY5OjIgVVYCmgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwEuVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_177", R"SYN(// BYTEBEAT 177 — dubbele zaag · akkoorden
// formule: (t*7&t>>8)|(t*5&t>>11)

uint8_t bb(uint32_t t) { return (t*7&t>>8)|(t*5&t>>11); }

void start() {
  bpm = 161;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 57);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEIOToSAAEFMhIAAQs5OjsgVVYCoQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwE5VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_178", R"SYN(// BYTEBEAT 178 — en-poorten · ritme
// formule: t*(t>>13&t>>7&77&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>13&t>>7&77&t>>2); }

void start() {
  bpm = 168;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 68);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQc5OgFNOhIAAQI5OjIgVVYCqAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFEVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_179", R"SYN(// BYTEBEAT 179 — trappen · drone
// formule: (t>>6|t|t>>((t>>15)&15))*10+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>6|t|t>>((t>>15)&15))*10+((t>>12)&7); }

int vorige = -1;

void start() {
  bpm = 123;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 79);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA/wATAAAAAAAIAAEBKwAAAFIAAAQBAT0RCQAEVhIAAQY5EgA7EgASAAEPOQEPOjk7AQoyEgABDDkBBzowIFVWAXsRBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBT1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSkQASAxAJAEEkUJMAAQFRsQABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRywABWlDNAAEoAQFXAAQEEAEAAQQ1AQBAUekAASMBZAEBVwEDBBIBAR86ARBAUf4AATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkAMQAKADcACwA/AAwARwANAFIAEABSABEAXgASAGcAEwB2ABQAfgAVAJYAFgCrABcAsQAZANMAGgDpABsA", 369 },
  { "bytebeat_180", R"SYN(// BYTEBEAT 180 — knars · melodie
// formule: (t*(t>>6|t>>8))>>((t>>13)&7)

uint8_t bb(uint32_t t) { return (t*(t>>6|t>>8))>>((t>>13)&7); }

void start() {
  bpm = 130;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 90);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEGORIAAQg5OzISAAENOQEHOjkgVVYCggAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwFaVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_181", R"SYN(// BYTEBEAT 181 — xor-familie · akkoorden
// formule: ((t*(t>>9|t>>10)&63&t>>9))^(t&t>>11|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>10)&63&t>>9))^(t&t>>11|t>>5); }

void start() {
  bpm = 137;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 101);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAGgEQAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQo5OzIBPzoSAAEJOToSABIAAQs5OhIAAQU5OzwgVVYCiQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwFlVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRoQABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLUABIBAUE6AUFAJFDWAAEBUeMAASQBcwEBVwEDBBIBAQM4AQM6AQJAUfsAAScBWgEBVwEDBBABAAECNVEJAQEqUAsBASwBKBICAT86MAEBVwEDBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgChABMAvAAUAOMAFQD7ABYA", 384 },
  { "bytebeat_182", R"SYN(// BYTEBEAT 182 — modulo-ritme · ritme
// formule: (t>>11|t%18)&(t>>8|t%23)

uint8_t bb(uint32_t t) { return (t>>11|t%18)&(t>>8|t%23); }

void start() {
  bpm = 144;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 32);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABCzkSAAESNjsSAAEIORIAARc2OzogVVYCkAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwEgVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_183", R"SYN(// BYTEBEAT 183 — vermenigvuldigers · drone
// formule: t*7&(t>>4)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*7&(t>>4)|t*(t>>9&7); }

int vorige = -1;

void start() {
  bpm = 151;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 43);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQcyEgABBDk6EgASAAEJOQEHOjI7IFVWApcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBK1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_184", R"SYN(// BYTEBEAT 184 — en-schuif · melodie
// formule: t*(69&t>>12)

uint8_t bb(uint32_t t) { return t*(69&t>>12); }

void start() {
  bpm = 158;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 54);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA2QAQAAAAAAABAAEBDwAAADkAAANWEgABRRIAAQw5OjIgVVYCngAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwE2VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRmQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlGuAAEkAXgBAVcBAwQSAgEHOgEDQFHDAAEmAV8BAVcBAwQSARICPAEBOlHYAAEqAUYBAVcBAwRWAQAEAA8ABgAPAAcAGAAIAB4ACQAmAAoALgALADkADgA5AA8ARQAQAE4AEQBdABIAeAATAJkAFACuABUAwwAWAA==", 319 },
  { "bytebeat_185", R"SYN(// BYTEBEAT 185 — viznut-familie · akkoorden
// formule: t*((t>>9|t>>7)&63&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>7)&63&t>>6); }

void start() {
  bpm = 165;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 65);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEJORIAAQc5OwE/OhIAAQY5OjIgVVYCpQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFBVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_186", R"SYN(// BYTEBEAT 186 — dubbele zaag · ritme
// formule: (t*5&t>>6)|(t*5&t>>10)

uint8_t bb(uint32_t t) { return (t*5&t>>6)|(t*5&t>>10); }

void start() {
  bpm = 120;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 76);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgABBTISAAEGOToSAAEFMhIAAQo5OjsgVVYBeBEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFMVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_187", R"SYN(// BYTEBEAT 187 — en-poorten · drone
// formule: t*(t>>12&t>>8&99&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>8&99&t>>3); }

int vorige = -1;

void start() {
  bpm = 127;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 87);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABDDkSAAEIOToBYzoSAAEDOToyIFVWAX8RBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBV1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_188", R"SYN(// BYTEBEAT 188 — trappen · melodie
// formule: (t>>4|t|t>>((t>>14)&15))*5+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>4|t|t>>((t>>14)&15))*5+((t>>12)&7); }

void start() {
  bpm = 134;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 98);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA7gAQAAAAAAABAAEBJAAAAE4AAANWEgABBDkSADsSABIAAQ45AQ86OTsBBTISAAEMOQEHOjAgVVYChgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwFiVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRrgABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHDAAEkAXgBAVcBAwQSAgEHOgEDQFHYAAEmAV8BAVcBAwQSARICPAEBOlHtAAEqAUYBAVcBAwRWAQAEACQABgAkAAcALQAIADMACQA7AAoAQwALAE4ADgBOAA8AWgAQAGMAEQByABIAjQATAK4AFADDABUA2AAWAA==", 340 },
  { "bytebeat_189", R"SYN(// BYTEBEAT 189 — knars · akkoorden
// formule: (t*(t>>4|t>>9))>>((t>>14)&7)

uint8_t bb(uint32_t t) { return (t*(t>>4|t>>9))>>((t>>14)&7); }

void start() {
  bpm = 141;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 109);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEEORIAAQk5OzISAAEOOQEHOjkgVVYCjQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFtVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_190", R"SYN(// BYTEBEAT 190 — xor-familie · ritme
// formule: ((t*(t>>8|t>>10)&31&t>>8))^(t&t>>13|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>10)&31&t>>8))^(t&t>>13|t>>5); }

void start() {
  bpm = 148;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 40);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEIORIAAQo5OzIBHzoSAAEIOToSABIAAQ05OhIAAQU5OzwgVVYClAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwEoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_191", R"SYN(// BYTEBEAT 191 — modulo-ritme · drone
// formule: (t>>12|t%40)&(t>>7|t%23)

uint8_t bb(uint32_t t) { return (t>>12|t%40)&(t>>7|t%23); }

int vorige = -1;

void start() {
  bpm = 155;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 51);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQw5EgABKDY7EgABBzkSAAEXNjs6IFVWApsAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBM1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_192", R"SYN(// BYTEBEAT 192 — vermenigvuldigers · melodie
// formule: t*11&(t>>3)|t*(t>>10&7)

uint8_t bb(uint32_t t) { return t*11&(t>>3)|t*(t>>10&7); }

void start() {
  bpm = 162;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 62);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCzISAAEDOToSABIAAQo5AQc6MjsgVVYCogAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwE+VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_193", R"SYN(// BYTEBEAT 193 — en-schuif · akkoorden
// formule: t*(42&t>>9)

uint8_t bb(uint32_t t) { return t*(42&t>>9); }

void start() {
  bpm = 169;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 73);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABKhIAAQk5OjIgVVYCqQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFJVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRhgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_194", R"SYN(// BYTEBEAT 194 — viznut-familie · ritme
// formule: t*((t>>11|t>>8)&31&t>>5)

uint8_t bb(uint32_t t) { return t*((t>>11|t>>8)&31&t>>5); }

void start() {
  bpm = 124;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 84);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgASAAELORIAAQg5OwEfOhIAAQU5OjIgVVYBfBEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFUVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_195", R"SYN(// BYTEBEAT 195 — dubbele zaag · drone
// formule: (t*3&t>>8)|(t*2&t>>9)

uint8_t bb(uint32_t t) { return (t*3&t>>8)|(t*2&t>>9); }

int vorige = -1;

void start() {
  bpm = 131;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 95);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQMyEgABCDk6EgABAjISAAEJOTo7IFVWAoMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBX1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_196", R"SYN(// BYTEBEAT 196 — en-poorten · melodie
// formule: t*(t>>10&t>>9&45&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>10&t>>9&45&t>>4); }

void start() {
  bpm = 138;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 106);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEKORIAAQk5OgEtOhIAAQQ5OjIgVVYCigAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFqVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_197", R"SYN(// BYTEBEAT 197 — trappen · akkoorden
// formule: (t>>7|t|t>>((t>>15)&15))*5+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>((t>>15)&15))*5+((t>>11)&7); }

void start() {
  bpm = 145;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 37);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBzkSADsSABIAAQ85AQ86OTsBBTISAAELOQEHOjAgVVYCkQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwElVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRmwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_198", R"SYN(// BYTEBEAT 198 — knars · ritme
// formule: (t*(t>>5|t>>7))>>((t>>14)&7)

uint8_t bb(uint32_t t) { return (t*(t>>5|t>>7))>>((t>>14)&7); }

void start() {
  bpm = 152;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 48);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEFORIAAQc5OzISAAEOOQEHOjkgVVYCmAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwEwVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_199", R"SYN(// BYTEBEAT 199 — xor-familie · drone
// formule: ((t*(t>>7|t>>6)&46&t>>7))^(t&t>>12|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>6)&46&t>>7))^(t&t>>12|t>>4); }

int vorige = -1;

void start() {
  bpm = 159;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 59);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAACAETAAAAAAAIAAEBMQAAAFsAAAQBAT0RCQAEVhIAEgABBzkSAAEGOTsyAS46EgABBzk6EgASAAEMOToSAAEEOTs8IFVWAp8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBO1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSmgASAxAJAEEkUJwAAQFRugABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpR1AABWlDWAAEoAQFXAAQEEAEAAQQ1AQBAUfIAASMBZAEBVwEDBBIBAR86ARBAUQcBATYBWgEBVwEDBFYAAAYACAAEADEACAAxAAkAOgAKAEAACwBIAAwAUAANAFsAEABbABEAZwASAHAAEwB/ABQAhwAVAJ8AFgC0ABcAugAZANwAGgDyABsA", 378 },
  { "bytebeat_200", R"SYN(// BYTEBEAT 200 — modulo-ritme · melodie
// formule: (t>>11|t%32)&(t>>6|t%15)

uint8_t bb(uint32_t t) { return (t>>11|t%32)&(t>>6|t%15); }

void start() {
  bpm = 166;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 70);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCzkSAAEgNjsSAAEGORIAAQ82OzogVVYCpgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwFGVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_201", R"SYN(// BYTEBEAT 201 — vermenigvuldigers · akkoorden
// formule: t*5&(t>>5)|t*(t>>10&7)

uint8_t bb(uint32_t t) { return t*5&(t>>5)|t*(t>>10&7); }

void start() {
  bpm = 121;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 81);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAEQAAAAAAABAAEBGwAAAEIAAANWEgABBTISAAEFOToSABIAAQo5AQc6MjsgVVYBeREEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwFRVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRjwABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLCABIBAUE6AUFAJFDEAAEBUdEAASQBcwEBVwEDBBIBAQM4AQM6AQJAUekAAScBWgEBVwEDBBABAAECNVH3AAEqUPkAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgCPABMAqgAUANEAFQDpABYA", 366 },
  { "bytebeat_202", R"SYN(// BYTEBEAT 202 — en-schuif · ritme
// formule: t*(37&t>>9)

uint8_t bb(uint32_t t) { return t*(37&t>>9); }

void start() {
  bpm = 128;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 92);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA8AARAAAAAAABAAEBDwAAADkAAANWEgABJRIAAQk5OjIgVVYCgAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwFcVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlFyAAEkAXgBAVcBAwQSAQEgOlGKAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGcAAEqATwBAVcBAwQSAQEPOgEPQFGxAAExAWQBAVcBAwQSAgFAOlHOAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFHvAAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgByABMAigAUAJwAFQCxABYAzgAXAA==", 346 },
  { "bytebeat_203", R"SYN(// BYTEBEAT 203 — viznut-familie · drone
// formule: t*((t>>12|t>>10)&25&t>>5)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>10)&25&t>>5); }

int vorige = -1;

void start() {
  bpm = 135;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 103);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABDDkSAAEKOTsBGToSAAEFOToyIFVWAocAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBZ1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_204", R"SYN(// BYTEBEAT 204 — dubbele zaag · melodie
// formule: (t*9&t>>6)|(t*2&t>>11)

uint8_t bb(uint32_t t) { return (t*9&t>>6)|(t*2&t>>11); }

void start() {
  bpm = 142;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 34);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEGOToSAAECMhIAAQs5OjsgVVYCjgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwEiVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_205", R"SYN(// BYTEBEAT 205 — en-poorten · akkoorden
// formule: t*(t>>11&t>>7&63&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>7&63&t>>2); }

void start() {
  bpm = 149;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 45);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQc5OgE/OhIAAQI5OjIgVVYClQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwEtVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_206", R"SYN(// BYTEBEAT 206 — trappen · ritme
// formule: (t>>5|t|t>>((t>>16)&15))*12+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>5|t|t>>((t>>16)&15))*12+((t>>10)&7); }

void start() {
  bpm = 156;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 56);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAABQERAAAAAAABAAEBJAAAAE4AAANWEgABBTkSADsSABIAARA5AQ86OTsBDDISAAEKOQEHOjAgVVYCnAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwE4VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlGHAAEkAXgBAVcBAwQSAQEgOlGfAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGxAAEqATwBAVcBAwQSAQEPOgEPQFHGAAExAWQBAVcBAwQSAgFAOlHjAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEEAQECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCHABMAnwAUALEAFQDGABYA4wAXAA==", 367 },
  { "bytebeat_207", R"SYN(// BYTEBEAT 207 — knars · drone
// formule: (t*(t>>3|t>>9))>>((t>>15)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>9))>>((t>>15)&7); }

int vorige = -1;

void start() {
  bpm = 163;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 67);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABAzkSAAEJOTsyEgABDzkBBzo5IFVWAqMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBQ1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_208", R"SYN(// BYTEBEAT 208 — xor-familie · melodie
// formule: ((t*(t>>9|t>>6)&31&t>>9))^(t&t>>11|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>6)&31&t>>9))^(t&t>>11|t>>4); }

void start() {
  bpm = 118;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 78);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA8QAQAAAAAAABAAEBKgAAAFEAAANWEgASAAEJORIAAQY5OzIBHzoSAAEJOToSABIAAQs5OhIAAQQ5OzwgVVYBdhEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwFOVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRsQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHGAAEkAXgBAVcBAwQSAgEHOgEDQFHbAAEmAV8BAVcBAwQSARICPAEBOlHwAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMAAIADYACQA+AAoARgALAFEADgBRAA8AXQAQAGYAEQB1ABIAkAATALEAFADGABUA2wAWAA==", 343 },
  { "bytebeat_209", R"SYN(// BYTEBEAT 209 — modulo-ritme · akkoorden
// formule: (t>>12|t%27)&(t>>8|t%15)

uint8_t bb(uint32_t t) { return (t>>12|t%27)&(t>>8|t%15); }

void start() {
  bpm = 125;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 89);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACAEQAAAAAAABAAEBGwAAAEIAAANWEgABDDkSAAEbNjsSAAEIORIAAQ82OzogVVYBfREEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFZVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRjwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLCABIBAUE6AUFAJFDEAAEBUdEAASQBcwEBVwEDBBIBAQM4AQM6AQJAUekAAScBWgEBVwEDBBABAAECNVH3AAEqUPkAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgCPABMAqgAUANEAFQDpABYA", 366 },
  { "bytebeat_210", R"SYN(// BYTEBEAT 210 — vermenigvuldigers · ritme
// formule: t*9&(t>>3)|t*(t>>12&7)

uint8_t bb(uint32_t t) { return t*9&(t>>3)|t*(t>>12&7); }

void start() {
  bpm = 132;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 100);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEDOToSABIAAQw5AQc6MjsgVVYChAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwFkVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_211", R"SYN(// BYTEBEAT 211 — en-schuif · drone
// formule: t*(63&t>>9)

uint8_t bb(uint32_t t) { return t*(63&t>>9); }

int vorige = -1;

void start() {
  bpm = 139;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 31);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAAT8SAAEJOToyIFVWAosAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBH1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_212", R"SYN(// BYTEBEAT 212 — viznut-familie · melodie
// formule: t*((t>>13|t>>8)&47&t>>3)

uint8_t bb(uint32_t t) { return t*((t>>13|t>>8)&47&t>>3); }

void start() {
  bpm = 146;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 42);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQg5OwEvOhIAAQM5OjIgVVYCkgAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwEqVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_213", R"SYN(// BYTEBEAT 213 — dubbele zaag · akkoorden
// formule: (t*7&t>>7)|(t*3&t>>10)

uint8_t bb(uint32_t t) { return (t*7&t>>7)|(t*3&t>>10); }

void start() {
  bpm = 153;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 53);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEHOToSAAEDMhIAAQo5OjsgVVYCmQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwE1VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_214", R"SYN(// BYTEBEAT 214 — en-poorten · ritme
// formule: t*(t>>13&t>>9&99&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>13&t>>9&99&t>>2); }

void start() {
  bpm = 160;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 64);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQk5OgFjOhIAAQI5OjIgVVYCoAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFAVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_215", R"SYN(// BYTEBEAT 215 — trappen · drone
// formule: (t>>6|t|t>>((t>>14)&15))*12+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>6|t|t>>((t>>14)&15))*12+((t>>12)&7); }

int vorige = -1;

void start() {
  bpm = 167;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 75);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAAAgETAAAAAAAIAAEBKwAAAFUAAAQBAT0RCQAEVhIAAQY5EgA7EgASAAEOOQEPOjk7AQwyEgABDDkBBzowIFVWAqcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBS1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSlAASAxAJAEEkUJYAAQFRtAABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRzgABWlDQAAEoAQFXAAQEEAEAAQQ1AQBAUewAASMBZAEBVwEDBBIBAR86ARBAUQEBATYBWgEBVwEDBFYAAAYACAAEACsACAArAAkANAAKADoACwBCAAwASgANAFUAEABVABEAYQASAGoAEwB5ABQAgQAVAJkAFgCuABcAtAAZANYAGgDsABsA", 372 },
  { "bytebeat_216", R"SYN(// BYTEBEAT 216 — knars · melodie
// formule: (t*(t>>6|t>>7))>>((t>>15)&7)

uint8_t bb(uint32_t t) { return (t*(t>>6|t>>7))>>((t>>15)&7); }

void start() {
  bpm = 122;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 86);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA4gAQAAAAAAABAAEBGwAAAEIAAANWEgASAAEGORIAAQc5OzISAAEPOQEHOjkgVVYBehEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFWVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRogABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG3AAEkAXgBAVcBAwQSAgEHOgEDQFHMAAEmAV8BAVcBAwQSARICPAEBOlHhAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAIQAIACcACQAvAAoANwALAEIADgBCAA8ATgAQAFcAEQBmABIAgQATAKIAFAC3ABUAzAAWAA==", 328 },
  { "bytebeat_217", R"SYN(// BYTEBEAT 217 — xor-familie · akkoorden
// formule: ((t*(t>>7|t>>6)&63&t>>7))^(t&t>>13|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>6)&63&t>>7))^(t&t>>13|t>>4); }

void start() {
  bpm = 129;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 97);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAGgEQAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQY5OzIBPzoSAAEHOToSABIAAQ05OhIAAQQ5OzwgVVYCgQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwFhVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRoQABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLUABIBAUE6AUFAJFDWAAEBUeMAASQBcwEBVwEDBBIBAQM4AQM6AQJAUfsAAScBWgEBVwEDBBABAAECNVEJAQEqUAsBASwBKBICAT86MAEBVwEDBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgChABMAvAAUAOMAFQD7ABYA", 384 },
  { "bytebeat_218", R"SYN(// BYTEBEAT 218 — modulo-ritme · ritme
// formule: (t>>13|t%27)&(t>>6|t%21)

uint8_t bb(uint32_t t) { return (t>>13|t%27)&(t>>6|t%21); }

void start() {
  bpm = 136;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 108);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABDTkSAAEbNjsSAAEGORIAARU2OzogVVYCiAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFsVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_219", R"SYN(// BYTEBEAT 219 — vermenigvuldigers · drone
// formule: t*3&(t>>5)|t*(t>>12&7)

uint8_t bb(uint32_t t) { return t*3&(t>>5)|t*(t>>12&7); }

int vorige = -1;

void start() {
  bpm = 143;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 39);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQMyEgABBTk6EgASAAEMOQEHOjI7IFVWAo8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBJ1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_220", R"SYN(// BYTEBEAT 220 — en-schuif · melodie
// formule: t*(99&t>>10)

uint8_t bb(uint32_t t) { return t*(99&t>>10); }

void start() {
  bpm = 150;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 50);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA2QAQAAAAAAABAAEBDwAAADkAAANWEgABYxIAAQo5OjIgVVYClgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwEyVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRmQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlGuAAEkAXgBAVcBAwQSAgEHOgEDQFHDAAEmAV8BAVcBAwQSARICPAEBOlHYAAEqAUYBAVcBAwRWAQAEAA8ABgAPAAcAGAAIAB4ACQAmAAoALgALADkADgA5AA8ARQAQAE4AEQBdABIAeAATAJkAFACuABUAwwAWAA==", 319 },
  { "bytebeat_221", R"SYN(// BYTEBEAT 221 — viznut-familie · akkoorden
// formule: t*((t>>9|t>>10)&123&t>>3)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>10)&123&t>>3); }

void start() {
  bpm = 157;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 61);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEJORIAAQo5OwF7OhIAAQM5OjIgVVYCnQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwE9VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_222", R"SYN(// BYTEBEAT 222 — dubbele zaag · ritme
// formule: (t*5&t>>8)|(t*3&t>>9)

uint8_t bb(uint32_t t) { return (t*5&t>>8)|(t*3&t>>9); }

void start() {
  bpm = 164;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 72);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgABBTISAAEIOToSAAEDMhIAAQk5OjsgVVYCpAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwFIVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_223", R"SYN(// BYTEBEAT 223 — en-poorten · drone
// formule: t*(t>>12&t>>7&123&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>7&123&t>>3); }

int vorige = -1;

void start() {
  bpm = 119;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 83);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABDDkSAAEHOToBezoSAAEDOToyIFVWAXcRBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBU1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_224", R"SYN(// BYTEBEAT 224 — trappen · melodie
// formule: (t>>4|t|t>>((t>>16)&15))*7+((t>>11)&7)

uint8_t bb(uint32_t t) { return (t>>4|t|t>>((t>>16)&15))*7+((t>>11)&7); }

void start() {
  bpm = 126;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 94);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA6wAQAAAAAAABAAEBJAAAAEsAAANWEgABBDkSADsSABIAARA5AQ86OTsBBzISAAELOQEHOjAgVVYBfhEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFeVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRqwABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHAAAEkAXgBAVcBAwQSAgEHOgEDQFHVAAEmAV8BAVcBAwQSARICPAEBOlHqAAEqAUYBAVcBAwRWAQAEACQABgAkAAcAKgAIADAACQA4AAoAQAALAEsADgBLAA8AVwAQAGAAEQBvABIAigATAKsAFADAABUA1QAWAA==", 337 },
  { "bytebeat_225", R"SYN(// BYTEBEAT 225 — knars · akkoorden
// formule: (t*(t>>4|t>>8))>>((t>>16)&7)

uint8_t bb(uint32_t t) { return (t*(t>>4|t>>8))>>((t>>16)&7); }

void start() {
  bpm = 133;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 105);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAEEORIAAQg5OzISAAEQOQEHOjkgVVYChQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_226", R"SYN(// BYTEBEAT 226 — xor-familie · ritme
// formule: ((t*(t>>7|t>>9)&63&t>>7))^(t&t>>13|t>>6)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>9)&63&t>>7))^(t&t>>13|t>>6); }

void start() {
  bpm = 140;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 36);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQk5OzIBPzoSAAEHOToSABIAAQ05OhIAAQY5OzwgVVYCjAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwEkVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_227", R"SYN(// BYTEBEAT 227 — modulo-ritme · drone
// formule: (t>>11|t%18)&(t>>6|t%19)

uint8_t bb(uint32_t t) { return (t>>11|t%18)&(t>>6|t%19); }

int vorige = -1;

void start() {
  bpm = 147;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 47);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQs5EgABEjY7EgABBjkSAAETNjs6IFVWApMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBL1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_228", R"SYN(// BYTEBEAT 228 — vermenigvuldigers · melodie
// formule: t*7&(t>>4)|t*(t>>11&7)

uint8_t bb(uint32_t t) { return t*7&(t>>4)|t*(t>>11&7); }

void start() {
  bpm = 154;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 58);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABBzISAAEEOToSABIAAQs5AQc6MjsgVVYCmgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwE6VwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_229", R"SYN(// BYTEBEAT 229 — en-schuif · akkoorden
// formule: t*(29&t>>10)

uint8_t bb(uint32_t t) { return t*(29&t>>10); }

void start() {
  bpm = 161;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 69);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/wAQAAAAAAABAAEBDwAAADkAAANWEgABHRIAAQo5OjIgVVYCoQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwFFVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRhgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK5ABIBAUE6AUFAJFC7AAEBUcgAASQBcwEBVwEDBBIBAQM4AQM6AQJAUeAAAScBWgEBVwEDBBABAAECNVHuAAEqUPAAASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAYAAgAHgAJACYACgAuAAsAOQAOADkADwBFABAATgARAF0AEgCGABMAoQAUAMgAFQDgABYA", 357 },
  { "bytebeat_230", R"SYN(// BYTEBEAT 230 — viznut-familie · ritme
// formule: t*((t>>11|t>>7)&63&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>11|t>>7)&63&t>>4); }

void start() {
  bpm = 168;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 80);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQc5OwE/OhIAAQQ5OjIgVVYCqAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwFQVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_231", R"SYN(// BYTEBEAT 231 — dubbele zaag · drone
// formule: (t*7&t>>6)|(t*5&t>>10)

uint8_t bb(uint32_t t) { return (t*7&t>>6)|(t*5&t>>10); }

int vorige = -1;

void start() {
  bpm = 123;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 91);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAAQcyEgABBjk6EgABBTISAAEKOTo7IFVWAXsRBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBW1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_232", R"SYN(// BYTEBEAT 232 — en-poorten · melodie
// formule: t*(t>>10&t>>8&63&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>10&t>>8&63&t>>4); }

void start() {
  bpm = 130;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 102);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAEKORIAAQg5OgE/OhIAAQQ5OjIgVVYCggAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_233", R"SYN(// BYTEBEAT 233 — trappen · akkoorden
// formule: (t>>7|t|t>>((t>>14)&15))*7+((t>>10)&7)

uint8_t bb(uint32_t t) { return (t>>7|t|t>>((t>>14)&15))*7+((t>>10)&7); }

void start() {
  bpm = 137;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 33);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAAFAEQAAAAAAABAAEBJAAAAE4AAANWEgABBzkSADsSABIAAQ45AQ86OTsBBzISAAEKOQEHOjAgVVYCiQAAABEEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwEhVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRmwABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLOABIBAUE6AUFAJFDQAAEBUd0AASQBcwEBVwEDBBIBAQM4AQM6AQJAUfUAAScBWgEBVwEDBBABAAECNVEDAQEqUAUBASwBKBICAT86MAEBVwEDBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCbABMAtgAUAN0AFQD1ABYA", 378 },
  { "bytebeat_234", R"SYN(// BYTEBEAT 234 — knars · ritme
// formule: (t*(t>>5|t>>9))>>((t>>16)&7)

uint8_t bb(uint32_t t) { return (t*(t>>5|t>>9))>>((t>>16)&7); }

void start() {
  bpm = 144;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 44);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEFORIAAQk5OzISAAEQOQEHOjkgVVYCkAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwEsVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_235", R"SYN(// BYTEBEAT 235 — xor-familie · drone
// formule: ((t*(t>>9|t>>10)&27&t>>9))^(t&t>>12|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>10)&27&t>>9))^(t&t>>12|t>>5); }

int vorige = -1;

void start() {
  bpm = 151;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 55);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAACAETAAAAAAAIAAEBMQAAAFsAAAQBAT0RCQAEVhIAEgABCTkSAAEKOTsyARs6EgABCTk6EgASAAEMOToSAAEFOTs8IFVWApcAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBN1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSmgASAxAJAEEkUJwAAQFRugABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpR1AABWlDWAAEoAQFXAAQEEAEAAQQ1AQBAUfIAASMBZAEBVwEDBBIBAR86ARBAUQcBATYBWgEBVwEDBFYAAAYACAAEADEACAAxAAkAOgAKAEAACwBIAAwAUAANAFsAEABbABEAZwASAHAAEwB/ABQAhwAVAJ8AFgC0ABcAugAZANwAGgDyABsA", 378 },
  { "bytebeat_236", R"SYN(// BYTEBEAT 236 — modulo-ritme · melodie
// formule: (t>>13|t%40)&(t>>6|t%21)

uint8_t bb(uint32_t t) { return (t>>13|t%40)&(t>>6|t%21); }

void start() {
  bpm = 158;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 66);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABDTkSAAEoNjsSAAEGORIAARU2OzogVVYCngAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwFCVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_237", R"SYN(// BYTEBEAT 237 — vermenigvuldigers · akkoorden
// formule: t*11&(t>>3)|t*(t>>11&7)

uint8_t bb(uint32_t t) { return t*11&(t>>3)|t*(t>>11&7); }

void start() {
  bpm = 165;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 77);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABCzISAAEDOToSABIAAQs5AQc6MjsgVVYCpQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASdXBAIEAQEBWwFNVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_238", R"SYN(// BYTEBEAT 238 — en-schuif · ritme
// formule: t*(57&t>>11)

uint8_t bb(uint32_t t) { return t*(57&t>>11); }

void start() {
  bpm = 120;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 88);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA7QARAAAAAAABAAEBDwAAADYAAANWEgABORIAAQs5OjIgVVYBeBEEAAQBBBEGAAQBAQFmVwQCBAECASNXBAIEAQEBWwFYVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlFvAAEkAXgBAVcBAwQSAQEgOlGHAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGZAAEqATwBAVcBAwQSAQEPOgEPQFGuAAExAWQBAVcBAwQSAgFAOlHLAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFHsAAECASMSAgEFNVcJATABbgEDVwAEBFYBAAQADwAGAA8ABwAVAAgAGwAJACMACgArAAsANgAOADYADwBCABAASwARAFoAEgBvABMAhwAUAJkAFQCuABYAywAXAA==", 343 },
  { "bytebeat_239", R"SYN(// BYTEBEAT 239 — viznut-familie · drone
// formule: t*((t>>12|t>>8)&31&t>>4)

uint8_t bb(uint32_t t) { return t*((t>>12|t>>8)&31&t>>4); }

int vorige = -1;

void start() {
  bpm = 127;
  maten = 4;
  instrument(1, 52);
  instrument(2, 36);
  cc(1, 91, 99);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA9gATAAAAAAAIAAEBIgAAAEkAAAQBAT0RCQAEVhIAEgABDDkSAAEIOTsBHzoSAAEEOToyIFVWAX8RBAAEAQQRBgAEAQEBNFcEAgQBAgEkVwQCBAEBAVsBY1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiAASAxAJAEEkUIoAAQFRqAABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRwgABWlDEAAEoAQFXAAQEEAEAAQQ1AQBAUeAAASMBZAEBVwEDBBIBAR86ARBAUfUAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKAAKAC4ACwA2AAwAPgANAEkAEABJABEAVQASAF4AEwBtABQAdQAVAI0AFgCiABcAqAAZAMoAGgDgABsA", 360 },
  { "bytebeat_240", R"SYN(// BYTEBEAT 240 — dubbele zaag · melodie
// formule: (t*9&t>>8)|(t*11&t>>11)

uint8_t bb(uint32_t t) { return (t*9&t>>8)|(t*11&t>>11); }

void start() {
  bpm = 134;
  maten = 4;
  instrument(1, 80);
  instrument(2, 38);
  cc(1, 91, 30);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEIOToSAAELMhIAAQs5OjsgVVYChgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASZXBAIEAQEBWwEeVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_241", R"SYN(// BYTEBEAT 241 — en-poorten · akkoorden
// formule: t*(t>>11&t>>9&77&t>>2)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>9&77&t>>2); }

void start() {
  bpm = 141;
  maten = 4;
  instrument(1, 12);
  instrument(2, 34);
  cc(1, 91, 41);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAELORIAAQk5OgFNOhIAAQI5OjIgVVYCjQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASJXBAIEAQEBWwEpVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQQAQABBDUBAEBRkgABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_242", R"SYN(// BYTEBEAT 242 — trappen · ritme
// formule: (t>>5|t|t>>((t>>15)&15))*10+((t>>12)&7)

uint8_t bb(uint32_t t) { return (t>>5|t|t>>((t>>15)&15))*10+((t>>12)&7); }

void start() {
  bpm = 148;
  maten = 4;
  instrument(1, 102);
  instrument(2, 87);
  cc(1, 91, 52);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAABQERAAAAAAABAAEBJAAAAE4AAANWEgABBTkSADsSABIAAQ85AQ86OTsBCjISAAEMOQEHOjAgVVYClAAAABEEAAQBBBEGAAQBAQFmVwQCBAECAVdXBAIEAQEBWwE0VwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQSAQKAAAAAOlGHAAEkAXgBAVcBAwQSAQEgOlGfAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGxAAEqATwBAVcBAwQSAQEPOgEPQFHGAAExAWQBAVcBAwQSAgFAOlHjAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEEAQECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAJAAGACQABwAtAAgAMwAJADsACgBDAAsATgAOAE4ADwBaABAAYwARAHIAEgCHABMAnwAUALEAFQDGABYA4wAXAA==", 367 },
  { "bytebeat_243", R"SYN(// BYTEBEAT 243 — knars · drone
// formule: (t*(t>>6|t>>9))>>((t>>13)&7)

uint8_t bb(uint32_t t) { return (t*(t>>6|t>>9))>>((t>>13)&7); }

int vorige = -1;

void start() {
  bpm = 155;
  maten = 4;
  instrument(1, 52);
  instrument(2, 43);
  cc(1, 91, 63);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABBjkSAAEJOTsyEgABDTkBBzo5IFVWApsAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgErVwQCBAEBAVsBP1cDAwRWEAAAAgACAAAyEwAEEgBUAQAgEwEEEgACAAEAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_244", R"SYN(// BYTEBEAT 244 — xor-familie · melodie
// formule: ((t*(t>>8|t>>10)&63&t>>8))^(t&t>>11|t>>5)

uint8_t bb(uint32_t t) { return ((t*(t>>8|t>>10)&63&t>>8))^(t&t>>11|t>>5); }

void start() {
  bpm = 162;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 74);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEIORIAAQo5OzIBPzoSAAEIOToSABIAAQs5OhIAAQU5OzwgVVYCogAAABEEAAQBBBEGAAQBAQFQVwQCBAECASFXBAIEAQEBWwFKVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
  { "bytebeat_245", R"SYN(// BYTEBEAT 245 — modulo-ritme · akkoorden
// formule: (t>>11|t%32)&(t>>8|t%21)

uint8_t bb(uint32_t t) { return (t>>11|t%32)&(t>>8|t%21); }

void start() {
  bpm = 169;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 85);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgABCzkSAAEgNjsSAAEIORIAARU2OzogVVYCqQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASBXBAIEAQEBWwFVVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRkgABAgEuEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAToSAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_246", R"SYN(// BYTEBEAT 246 — vermenigvuldigers · ritme
// formule: t*5&(t>>4)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*5&(t>>4)|t*(t>>9&7); }

void start() {
  bpm = 124;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 96);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 63 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 39 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA+QARAAAAAAABAAEBGwAAAEIAAANWEgABBTISAAEEOToSABIAAQk5AQc6MjsgVVYBfBEEAAQBBBEGAAQBAQFmVwQCBAECASVXBAIEAQEBWwFgVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF7AAEkAXgBAVcBAwQSAQEgOlGTAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGlAAEqATwBAVcBAwQSAQEPOgEPQFG6AAExAWQBAVcBAwQSAgFAOlHXAAEBAT8SAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH4AAECAScSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAhAAgAJwAJAC8ACgA3AAsAQgAOAEIADwBOABAAVwARAGYAEgB7ABMAkwAUAKUAFQC6ABYA1wAXAA==", 355 },
  { "bytebeat_247", R"SYN(// BYTEBEAT 247 — en-schuif · drone
// formule: t*(37&t>>12)

uint8_t bb(uint32_t t) { return t*(37&t>>12); }

int vorige = -1;

void start() {
  bpm = 131;
  maten = 4;
  instrument(1, 52);
  instrument(2, 39);
  cc(1, 91, 107);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 44 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 68 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA7QATAAAAAAAIAAEBFgAAAEAAAAQBAT0RCQAEVhIAASUSAAEMOToyIFVWAoMAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEnVwQCBAEBAVsBa1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSfwASAxAJAEEkUIEAAQFRnwABAgEsEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFEEgIBDjVXCgEwEgIBATpRuQABWlC7AAEoAQFXAAQEEAEAAQQ1AQBAUdcAASMBZAEBVwEDBBIBAR86ARBAUewAATYBWgEBVwEDBFYAAAYACAAEABYACAAWAAkAHwAKACUACwAtAAwANQANAEAAEABAABEATAASAFUAEwBkABQAbAAVAIQAFgCZABcAnwAZAMEAGgDXABsA", 351 },
  { "bytebeat_248", R"SYN(// BYTEBEAT 248 — viznut-familie · melodie
// formule: t*((t>>13|t>>7)&31&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>13|t>>7)&31&t>>6); }

void start() {
  bpm = 138;
  maten = 4;
  instrument(1, 80);
  instrument(2, 35);
  cc(1, 91, 38);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  noot(1, 49 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 37 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQc5OwEfOhIAAQY5OjIgVVYCigAAABEEAAQBBBEGAAQBAQFQVwQCBAECASNXBAIEAQEBWwEmVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQBAQExEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgElEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_249", R"SYN(// BYTEBEAT 249 — en-poorten · akkoorden
// formule: t*(t>>13&t>>8&123&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>13&t>>8&123&t>>3); }

void start() {
  bpm = 145;
  maten = 4;
  instrument(1, 12);
  instrument(2, 36);
  cc(1, 91, 49);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (s % 4 == 0) akkoord(2, 54 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 66 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwEQAAAAAAABAAEBGwAAAEUAAANWEgASAAENORIAAQg5OgF7OhIAAQM5OjIgVVYCkQAAABEEAAQBBBEGAAQBAQEMVwQCBAECASRXBAIEAQEBWwExVwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQQAQABBDUBAEBRkgABAgE2EgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAUISAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFLFABIBAUE6AUFAJFDHAAEBUdQAASQBcwEBVwEDBBIBAQM4AQM6AQJAUewAAScBWgEBVwEDBBABAAECNVH6AAEqUPwAASwBKBICAT86MAEBVwEDBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgCSABMArQAUANQAFQDsABYA", 369 },
  { "bytebeat_250", R"SYN(// BYTEBEAT 250 — xor-familie · ritme
// formule: ((t*(t>>7|t>>6)&27&t>>7))^(t&t>>13|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>7|t>>6)&27&t>>7))^(t&t>>13|t>>4); }

void start() {
  bpm = 152;
  maten = 4;
  instrument(1, 102);
  instrument(2, 38);
  cc(1, 91, 60);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 59 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 35 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAACwERAAAAAAABAAEBKgAAAFQAAANWEgASAAEHORIAAQY5OzIBGzoSAAEHOToSABIAAQ05OhIAAQQ5OzwgVVYCmAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASZXBAIEAQEBWwE8VwMDBFYQAAACAAgAADITAAQSAFQBACATAQQSAAIABAAAMFQBACATAgQSAQKAAAAAOlGNAAEkAXgBAVcBAwQSAQEgOlGlAAEmAUYSAgEfOjABAVcBAwQSAgEEOlG3AAEqATwBAVcBAwQSAQEPOgEPQFHMAAExAWQBAVcBAwQSAgFAOlHpAAEBATsSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFEKAQECASMSAgEFNVcJATABbgEDVwAEBFYBAAQAKgAGACoABwAzAAgAOQAJAEEACgBJAAsAVAAOAFQADwBgABAAaQARAHgAEgCNABMApQAUALcAFQDMABYA6QAXAA==", 373 },
  { "bytebeat_251", R"SYN(// BYTEBEAT 251 — modulo-ritme · drone
// formule: (t>>12|t%27)&(t>>7|t%23)

uint8_t bb(uint32_t t) { return (t>>12|t%27)&(t>>7|t%23); }

int vorige = -1;

void start() {
  bpm = 159;
  maten = 4;
  instrument(1, 52);
  instrument(2, 34);
  cc(1, 91, 71);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 40 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 64 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAAQw5EgABGzY7EgABBzkSAAEXNjs6IFVWAp8AAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEiVwQCBAEBAVsBR1cDAwRWEAAAAgAIAAAyEwAEEgBUAQAgEwEEEgACAAQAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEoEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQFAEgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_252", R"SYN(// BYTEBEAT 252 — vermenigvuldigers · melodie
// formule: t*9&(t>>3)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*9&(t>>3)|t*(t>>9&7); }

void start() {
  bpm = 166;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 82);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA5QAQAAAAAAABAAEBGwAAAEUAAANWEgABCTISAAEDOToSABIAAQk5AQc6MjsgVVYCpgAAABEEAAQBBBEGAAQBAQFQVwQCBAECAVdXBAIEAQEBWwFSVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQBAQEtEgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRpQABAgEhEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlG6AAEkAXgBAVcBAwQSAgEHOgEDQFHPAAEmAV8BAVcBAwQSARICPAEBOlHkAAEqAUYBAVcBAwRWAQAEABsABgAbAAcAJAAIACoACQAyAAoAOgALAEUADgBFAA8AUQAQAFoAEQBpABIAhAATAKUAFAC6ABUAzwAWAA==", 331 },
  { "bytebeat_253", R"SYN(// BYTEBEAT 253 — en-schuif · akkoorden
// formule: t*(21&t>>12)

uint8_t bb(uint32_t t) { return t*(21&t>>12); }

void start() {
  bpm = 121;
  maten = 4;
  instrument(1, 12);
  instrument(2, 43);
  cc(1, 91, 93);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 50 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 62 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AAQAAAAAAABAAEBDwAAADYAAANWEgABFRIAAQw5OjIgVVYBeREEAAQBBBEGAAQBAQEMVwQCBAECAStXBAIEAQEBWwFdVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQQAQABBDUBAEBRgwABAgEyEgEBBThXCgEwEgIBBzgBAToBRgEEVwIFBAEBAT4SAgEKNVcKATABMhIBAT86MAEBVwAEBBABAAEENQEAQFK2ABIBAUE6AUFAJFC4AAEBUcUAASQBcwEBVwEDBBIBAQM4AQM6AQJAUd0AAScBWgEBVwEDBBABAAECNVHrAAEqUO0AASwBKBICAT86MAEBVwEDBFYBAAQADwAGAA8ABwAVAAgAGwAJACMACgArAAsANgAOADYADwBCABAASwARAFoAEgCDABMAngAUAMUAFQDdABYA", 354 },
  { "bytebeat_254", R"SYN(// BYTEBEAT 254 — viznut-familie · ritme
// formule: t*((t>>9|t>>8)&25&t>>6)

uint8_t bb(uint32_t t) { return t*((t>>9|t>>8)&25&t>>6); }

void start() {
  bpm = 128;
  maten = 4;
  instrument(1, 102);
  instrument(2, 33);
  cc(1, 91, 104);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA/AARAAAAAAABAAEBGwAAAEUAAANWEgASAAEJORIAAQg5OwEZOhIAAQY5OjIgVVYCgAAAABEEAAQBBBEGAAQBAQFmVwQCBAECASFXBAIEAQEBWwFoVwMDBFYQAAACAAQAADITAAQSAFQBACATAQQSAAIAAgAAMFQBACATAgQSAQKAAAAAOlF+AAEkAXgBAVcBAwQSAQEgOlGWAAEmAUYSAgEfOjABAVcBAwQSAgEEOlGoAAEqATwBAVcBAwQSAQEPOgEPQFG9AAExAWQBAVcBAwQSAgFAOlHaAAEBAUMSAQEHNVcJATABWgEBVwAEBBABAAEENQEAQFH7AAECASsSAgEFNVcJATABbgEDVwAEBFYBAAQAGwAGABsABwAkAAgAKgAJADIACgA6AAsARQAOAEUADwBRABAAWgARAGkAEgB+ABMAlgAUAKgAFQC9ABYA2gAXAA==", 358 },
  { "bytebeat_255", R"SYN(// BYTEBEAT 255 — en-poorten · drone
// formule: t*(t>>12&t>>9&45&t>>4)

uint8_t bb(uint32_t t) { return t*(t>>12&t>>9&45&t>>4); }

int vorige = -1;

void start() {
  bpm = 135;
  maten = 4;
  instrument(1, 52);
  instrument(2, 32);
  cc(1, 91, 35);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  int g = v >> 6;
  if (s == 0 || g != vorige) {
    noot(2, 36 + mineur(g * 2), 80, 8);
    vorige = g;
  }
  noot(1, 60 + mineur(w % 14), w & 1 ? 90 : 40);
  if (s % 4 == 0) drum(35, 100);
  if ((v & 0x1F) == 0x10) drum(54, 90);
}
)SYN", "U0JDMQEACgAEAAAAAgADAAAA+QATAAAAAAAIAAEBIgAAAEwAAAQBAT0RCQAEVhIAEgABDDkSAAEJOToBLToSAAEEOToyIFVWAocAAAARBAAEAQQRBgAEAQEBNFcEAgQBAgEgVwQCBAEBAVsBI1cDAwRWEAAAAgAEAAAyEwAEEgBUAQAgEwEEEgACAAIAADBUAQAgEwIEEgEBBjgTAwQQAQABAEBSiwASAxAJAEEkUI0AAQFRqwABAgEkEgMBAjJXCgEwAVABCFcABAQSAxEJAAQBAQE8EgIBDjVXCgEwEgIBATpRxQABWlDHAAEoAQFXAAQEEAEAAQQ1AQBAUeMAASMBZAEBVwEDBBIBAR86ARBAUfgAATYBWgEBVwEDBFYAAAYACAAEACIACAAiAAkAKwAKADEACwA5AAwAQQANAEwAEABMABEAWAASAGEAEwBwABQAeAAVAJAAFgClABcAqwAZAM0AGgDjABsA", 363 },
  { "bytebeat_256", R"SYN(// BYTEBEAT 256 — xor-familie · melodie
// formule: ((t*(t>>9|t>>6)&46&t>>9))^(t&t>>12|t>>4)

uint8_t bb(uint32_t t) { return ((t*(t>>9|t>>6)&46&t>>9))^(t&t>>12|t>>4); }

void start() {
  bpm = 142;
  maten = 4;
  instrument(1, 80);
  instrument(2, 37);
  cc(1, 91, 46);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  noot(1, 53 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 41 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
)SYN", "U0JDMQEACQAEAAAAAgADAAAA9AAQAAAAAAABAAEBKgAAAFQAAANWEgASAAEJORIAAQY5OzIBLjoSAAEJOToSABIAAQw5OhIAAQQ5OzwgVVYCjgAAABEEAAQBBBEGAAQBAQFQVwQCBAECASVXBAIEAQEBWwEuVwMDBFYQAAACAAIAADITAAQSAFQBACATAQQSAAIAAQAAMFQBACATAgQBAQE1EgEBDDVXCQEwATwSAQE8NTABAVcABAQQAQABAjUBAEBRtAABAgEpEgIBBThXCQEwAWkBAlcABAQSAQKAAAAAOlHJAAEkAXgBAVcBAwQSAgEHOgEDQFHeAAEmAV8BAVcBAwQSARICPAEBOlHzAAEqAUYBAVcBAwRWAQAEACoABgAqAAcAMwAIADkACQBBAAoASQALAFQADgBUAA8AYAAQAGkAEQB4ABIAkwATALQAFADJABUA3gAWAA==", 346 },
};

static const int N_INGEBOUWD = sizeof(INGEBOUWD) / sizeof(INGEBOUWD[0]);
