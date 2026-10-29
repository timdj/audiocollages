// BYTEBEAT 011 — melodietabel · drone
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
