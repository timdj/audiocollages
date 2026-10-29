// BYTEBEAT 012 — drie lagen · melodie
// formule: (t*9&t>>4|t*5&t>>7|t*3&t/1024)-1

uint8_t bb(uint32_t t) { return (t*9&t>>4|t*5&t>>7|t*3&t/1024)-1; }

void start() {
  bpm = 150;
  maten = 4;
  instrument(1, 80);
  instrument(2, 87);
  cc(1, 91, 82);
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
