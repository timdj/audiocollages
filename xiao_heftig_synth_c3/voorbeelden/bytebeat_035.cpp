// BYTEBEAT 035 — knars · drone
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
