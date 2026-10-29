// BYTEBEAT 005 — en-poort · akkoorden
// formule: t*(t>>11&t>>8&123&t>>3)

uint8_t bb(uint32_t t) { return t*(t>>11&t>>8&123&t>>3); }

void start() {
  bpm = 153;
  maten = 4;
  instrument(1, 12);
  instrument(2, 32);
  cc(1, 91, 85);
}

void stap() {
  uint32_t b = t * 1024;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 512);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
