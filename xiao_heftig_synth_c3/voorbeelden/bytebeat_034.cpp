// BYTEBEAT 034 — melodietabel · ritme
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
