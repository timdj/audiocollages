// BYTEBEAT 098 — vermenigvuldigers · ritme
// formule: t*11&(t>>3)|t*(t>>9&7)

uint8_t bb(uint32_t t) { return t*11&(t>>3)|t*(t>>9&7); }

void start() {
  bpm = 128;
  maten = 4;
  instrument(1, 102);
  instrument(2, 35);
  cc(1, 91, 68);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (v & 0x80) drum(36, 120);
  if (v & 0x20) drum(38, 70 + (w & 31));
  if (w & 0x04) drum(42, 60);
  if ((v & 0x0F) == 0x0F) drum(49, 100);
  if (w & 0x40) noot(1, 67 + schaal(v % 7), 90);
  if (s % 4 == 0) noot(2, 43 + schaal(w % 5), 110, 3);
}
