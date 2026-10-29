// BYTEBEAT 092 — en-poorten · melodie
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
