// muziek.h — de muziekfuncties van XIAO Heftig Synth.
// Gedeeld door de bytecode-VM op de XIAO (vm.h) en door synth.h (gewone C++ op
// een computer), zodat beide routes precies dezelfde MIDI maken.
#pragma once
#include <cstdint>

namespace muziek {

static const int8_t SINUS[256] = {
  0, 3, 6, 9, 12, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 51, 54, 57, 60, 63, 65, 68, 71, 73, 76, 78, 81, 83, 85, 88,
  90, 92, 94, 96, 98, 100, 102, 104, 106, 107, 109, 111, 112, 113, 115, 116, 117, 118, 120, 121, 122, 122, 123, 124, 125, 125, 126, 126, 126, 127,
  127, 127, 127, 127, 127, 127, 126, 126, 126, 125, 125, 124, 123, 122, 122, 121, 120, 118, 117, 116, 115, 113, 112, 111, 109, 107, 106, 104, 102, 100,
  98, 96, 94, 92, 90, 88, 85, 83, 81, 78, 76, 73, 71, 68, 65, 63, 60, 57, 54, 51, 49, 46, 43, 40, 37, 34, 31, 28, 25, 22, 19, 16,
  12, 9, 6, 3, 0, -3, -6, -9, -12, -16, -19, -22, -25, -28, -31, -34, -37, -40, -43, -46, -49, -51, -54, -57, -60, -63, -65, -68, -71, -73,
  -76, -78, -81, -83, -85, -88, -90, -92, -94, -96, -98, -100, -102, -104, -106, -107, -109, -111, -112, -113, -115, -116, -117, -118, -120, -121, -122, -122, -123, -124,
  -125, -125, -126, -126, -126, -127, -127, -127, -127, -127, -127, -127, -126, -126, -126, -125, -125, -124, -123, -122, -122, -121, -120, -118, -117, -116, -115, -113, -112, -111,
  -109, -107, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54, -51, -49, -46, -43, -40,
  -37, -34, -31, -28, -25, -22, -19, -16, -12, -9, -6, -3,
};

typedef void (*MidiFn)(const uint8_t *b, int n);

struct Held { uint8_t ch, note; uint32_t offStep; };

struct Muziek {
  MidiFn midi = nullptr;
  uint32_t rng = 0x12345678u;
  Held held[64];
  int nHeld = 0;
  uint32_t stapT = 0;

  void seed(uint32_t s) { rng = s ? s : 0x12345678u; }

  // ---- uitvoer ----
  void out(const uint8_t *b, int n) { if (midi) midi(b, n); }
  static int clamp(int32_t v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : (int)v; }
  static int kanaal(int32_t k) { return (k >= 1 && k <= 16) ? (int)k - 1 : -1; }
  static int wrap(int32_t i, int n) { int r = (int)(i % n); return r < 0 ? r + n : r; }
  void msg3(int st, int32_t d1, int32_t d2) {
    uint8_t b[3] = { (uint8_t)st, (uint8_t)clamp(d1, 0, 127), (uint8_t)clamp(d2, 0, 127) };
    out(b, 3);
  }
  void noteOff(uint8_t ch, uint8_t n) { uint8_t b[3] = { (uint8_t)(0x80 | ch), n, 0 }; out(b, 3); }

  // ---- noten met een lengte in stappen ----
  void speel(int32_t k, int32_t n, int32_t v, int32_t lengte) {
    int ch = kanaal(k);
    if (ch < 0 || n < 0 || n > 127 || v <= 0) return;
    if (v > 127) v = 127;
    if (lengte < 1) lengte = 1;
    for (int i = 0; i < nHeld; i++)
      if (held[i].ch == ch && held[i].note == n) { noteOff((uint8_t)ch, (uint8_t)n); held[i] = held[--nHeld]; break; }
    if (nHeld >= 64) { noteOff(held[0].ch, held[0].note); held[0] = held[--nHeld]; }
    uint8_t b[3] = { (uint8_t)(0x90 | ch), (uint8_t)n, (uint8_t)v };
    out(b, 3);
    held[nHeld++] = { (uint8_t)ch, (uint8_t)n, stapT + (uint32_t)lengte };
  }
  void loslaten(uint32_t t) {
    for (int i = 0; i < nHeld;) {
      if ((int32_t)(t - held[i].offStep) >= 0) { noteOff(held[i].ch, held[i].note); held[i] = held[--nHeld]; }
      else i++;
    }
  }
  void allesUit() {
    for (int i = 0; i < nHeld; i++) noteOff(held[i].ch, held[i].note);
    nHeld = 0;
    for (uint8_t ch = 0; ch < 16; ch++) { uint8_t b[3] = { (uint8_t)(0xB0 | ch), 123, 0 }; out(b, 3); }
  }

  // ---- de ingebouwde functies van de synthtaal ----
  void noot(int32_t k, int32_t n, int32_t v, int32_t l) { speel(k, n, v, l); }
  void drum(int32_t n, int32_t v, int32_t l) { speel(10, n, v, l); }
  void akkoord(int32_t k, int32_t g, int32_t mineur, int32_t v, int32_t l) {
    for (int i = 0; i < 3; i++) speel(k, g + drieklank(i, mineur), v, l);
  }
  void cc(int32_t k, int32_t nr, int32_t w) { int ch = kanaal(k); if (ch >= 0) msg3(0xB0 | ch, nr, w); }
  void instrument(int32_t k, int32_t nr) {
    int ch = kanaal(k);
    if (ch < 0) return;
    uint8_t b[2] = { (uint8_t)(0xC0 | ch), (uint8_t)clamp(nr, 0, 127) };
    out(b, 2);
  }
  void filter(int32_t k, int32_t cutoff, int32_t reso) {
    int ch = kanaal(k);
    if (ch < 0) return;
    msg3(0xB0 | ch, 99, 0x01); msg3(0xB0 | ch, 98, 0x20); msg3(0xB0 | ch, 6, cutoff);
    msg3(0xB0 | ch, 99, 0x01); msg3(0xB0 | ch, 98, 0x21); msg3(0xB0 | ch, 6, reso);
  }
  void bend(int32_t k, int32_t w) {
    int ch = kanaal(k);
    if (ch < 0) return;
    int x = clamp(w, -8192, 8191) + 8192;
    uint8_t b[3] = { (uint8_t)(0xE0 | ch), (uint8_t)(x & 127), (uint8_t)(x >> 7) };
    out(b, 3);
  }
  static int32_t pat(const uint8_t *s, int len, int32_t i) {
    if (len <= 0) return 0;
    uint8_t c = s[wrap(i, len)];
    if (c == '.' || c == ' ' || c == '-' || c == '_') return 0;
    if (c >= '1' && c <= '9') return c - '0';
    return 1;
  }
  static int32_t toon(const uint8_t *s, int len, int32_t i) {
    if (len <= 0) return -1000;
    uint8_t c = s[wrap(i, len)];
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'a') return 10;
    if (c == 'b') return 11;
    if (c >= 'A' && c <= 'L') return 12 + (c - 'A');
    return -1000;
  }
  static int32_t ladder(int32_t i, const int *sc, int n) {
    int32_t oct = i >= 0 ? i / n : -((-i + n - 1) / n);
    return sc[wrap(i, n)] + 12 * oct;
  }
  static int32_t schaal(int32_t i) { static const int P[5] = { 0, 3, 5, 7, 10 }; return ladder(i, P, 5); }
  static int32_t mineur(int32_t i) { static const int M[7] = { 0, 2, 3, 5, 7, 8, 10 }; return ladder(i, M, 7); }
  static int32_t drieklank(int32_t i, int32_t mineurAkk) {
    int st = wrap(i, 3);
    int32_t oct = i >= 0 ? i / 3 : -((-i + 2) / 3);
    int v = st == 0 ? 0 : st == 1 ? (mineurAkk ? 3 : 4) : 7;
    return v + 12 * oct;
  }
  static int32_t sinus(int32_t x) { return SINUS[x & 255]; }
  int32_t rnd(int32_t n) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return n > 0 ? (int32_t)(rng % (uint32_t)n) : 0;
  }
  static int32_t min(int32_t a, int32_t b) { return a < b ? a : b; }
  static int32_t max(int32_t a, int32_t b) { return a > b ? a : b; }
  static int32_t abs(int32_t a) { return a < 0 ? (int32_t)(0u - (uint32_t)a) : a; }
};

}  // namespace muziek
