// BYTEBEAT 084 — melodietabel · melodie
// formule: t*(0x4735>>(t>>11&14)&15)|t>>6

uint8_t bb(uint32_t t) { return t*(0x4735>>(t>>11&14)&15)|t>>6; }

void start() {
  bpm = 134;
  maten = 4;
  instrument(1, 80);
  instrument(2, 33);
  cc(1, 91, 74);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  noot(1, 45 + schaal(v % 12), 60 + v % 60);
  if (s % 2 == 0) noot(2, 33 + schaal(w >> 5), 105, 2);
  if (v & 0x80) drum(36, 120);
  if ((w & 7) == 3) drum(38, 95);
  if ((v ^ w) & 1) drum(42, 70);
}
