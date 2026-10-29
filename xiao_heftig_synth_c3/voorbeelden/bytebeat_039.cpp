// BYTEBEAT 039 — en-schuif · drone
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
