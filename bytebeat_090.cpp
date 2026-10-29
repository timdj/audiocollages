// BYTEBEAT 090 — viznut-familie · ritme
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
