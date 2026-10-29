// BYTEBEAT 040 — viznut-familie · melodie
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
