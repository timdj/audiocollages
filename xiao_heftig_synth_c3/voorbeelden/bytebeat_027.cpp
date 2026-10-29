// BYTEBEAT 027 — arpeggiator · drone
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
