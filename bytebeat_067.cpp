// BYTEBEAT 067 — modulo-ritme · drone
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
