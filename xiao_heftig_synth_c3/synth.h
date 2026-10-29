// synth.h — draai een synthbestand als gewoon C++-programma op je computer.
//   g++ -std=c++17 -include synth.h mijn_stuk.cpp -o mijn_stuk && ./mijn_stuk 64 > midi.txt
// Het programma voert start() en dan <aantal> keer stap() uit en schrijft de
// MIDI-berichten als hex-regels. Dezelfde code draait op de XIAO via de
// bytecode-compiler in de XIAO Flitser; beide geven precies dezelfde MIDI.
#pragma once
#include <cstdint>
#include <cstring>
#include <cstdio>
#include "muziek.h"

namespace synth_intern {
inline muziek::Muziek &mz() { static muziek::Muziek m; return m; }
}

// vaste variabelen
inline uint32_t t = 0;
inline int s = 0, m = 0, tel = 0, bpm = 120, swing = 0, maten = 8, noot_in = 60, vol = 100;

// ingebouwde functies
inline void noot(int k, int n, int v, int l = 1) { synth_intern::mz().noot(k, n, v, l); }
inline void drum(int n, int v, int l = 1) { synth_intern::mz().drum(n, v, l); }
inline void akkoord(int k, int g, int mineurAkk, int v, int l = 1) { synth_intern::mz().akkoord(k, g, mineurAkk, v, l); }
inline void cc(int k, int nr, int w) { synth_intern::mz().cc(k, nr, w); }
inline void instrument(int k, int nr) { synth_intern::mz().instrument(k, nr); }
inline void filter(int k, int cutoff, int reso) { synth_intern::mz().filter(k, cutoff, reso); }
inline void bend(int k, int w) { synth_intern::mz().bend(k, w); }
inline int pat(const char *p, int i) { return muziek::Muziek::pat((const uint8_t *)p, (int)strlen(p), i); }
inline int toon(const char *p, int i) { return muziek::Muziek::toon((const uint8_t *)p, (int)strlen(p), i); }
inline int schaal(int i) { return muziek::Muziek::schaal(i); }
inline int mineur(int i) { return muziek::Muziek::mineur(i); }
inline int drieklank(int i, int mineurAkk) { return muziek::Muziek::drieklank(i, mineurAkk); }
inline int sinus(int x) { return muziek::Muziek::sinus(x); }
inline int rnd(int n) { return synth_intern::mz().rnd(n); }
inline int min(int a, int b) { return muziek::Muziek::min(a, b); }
inline int max(int a, int b) { return muziek::Muziek::max(a, b); }
inline int abs(int a) { return muziek::Muziek::abs(a); }
inline void print(int x) { fprintf(stderr, "print %d\n", x); }

void start() __attribute__((weak));   // start() mag ontbreken
void stap();

#ifndef SYNTH_GEEN_MAIN
inline void synth_midi_hex(const uint8_t *b, int n) {
  for (int i = 0; i < n; i++) printf("%02X", b[i]);
  printf("\n");
}
int main(int argc, char **argv) {
  int stappen = 64;
  if (argc > 1) { stappen = 0; for (const char *c = argv[1]; *c >= '0' && *c <= '9'; c++) stappen = stappen * 10 + (*c - '0'); }
  muziek::Muziek &z = synth_intern::mz();
  z.midi = synth_midi_hex;
  z.seed(1);
  if (start) start();
  for (uint32_t i = 0; i < (uint32_t)stappen; i++) {
    z.loslaten(i);
    z.stapT = i;
    t = i; s = (int)(i & 15); m = (int)(i >> 4); tel = (int)((i >> 2) & 3);
    stap();
  }
  z.allesUit();
  return 0;
}
#endif
