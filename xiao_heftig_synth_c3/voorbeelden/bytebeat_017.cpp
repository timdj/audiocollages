// BYTEBEAT 017 — sirene · akkoorden
// formule: t*(t^t+(t>>15|1)^(t-1280^t)>>10)

uint8_t bb(uint32_t t) { return t*(t^t+(t>>15|1)^(t-1280^t)>>10); }

void start() {
  bpm = 133;
  maten = 4;
  instrument(1, 12);
  instrument(2, 39);
  cc(1, 91, 57);
}

void stap() {
  uint32_t b = t * 512;
  uint8_t v = bb(b);
  uint8_t w = bb(b + 256);
  if (s % 4 == 0) akkoord(2, 46 + mineur(v >> 5), (w >> 7) & 1, 70, 4);
  noot(1, 58 + mineur(w % 10), 50 + (v & 63));
  if (s % 4 == 0 || (v & 0x41) == 0x41) drum(36, 115);
  if ((v >> 3 & 3) == 2) drum(39, 90);
  drum(s % 2 ? 42 : 44, 40 + (w & 63));
}
