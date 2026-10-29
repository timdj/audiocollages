// BYTEBEAT 026 — golfslag · ritme
// formule: (t*(t>>3|t>>4))>>((t>>12)&7)

uint8_t bb(uint32_t t) { return (t*(t>>3|t>>4))>>((t>>12)&7); }

void start() {
  bpm = 144;
  maten = 4;
  instrument(1, 102);
  instrument(2, 37);
  cc(1, 91, 76);
}

void stap() {
  uint32_t b = t * 2048;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 1024);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
