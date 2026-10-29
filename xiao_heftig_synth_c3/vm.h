// vm.h — de bytecode-machine van XIAO Heftig Synth.
// ----------------------------------------------------------------------------
// De synthbestanden zijn gewone C++ (een deelverzameling). De XIAO Flitser
// compileert ze in de browser naar bytecode (.sbc); deze machine voert die uit.
// Alles wordt gecontroleerd: arraygrenzen, deling door nul, stapelruimte,
// sprongadressen en een rekenbudget per stap. Een fout stopt alleen het stuk,
// nooit de XIAO, en wordt gemeld met het regelnummer in de C++-bron.
//
// Bestandsformaat (little-endian):
//   "SBC1" u8 versie=1 u8 vlaggen
//   u16 nGlobals u16 nFuncs u16 fInit u16 fStart u16 fStap u16 nStr u16 codeLen u16 nLines
//   nFuncs x (u16 adres, u8 nParams, u8 nLocals)
//   nStr   x (u16 lengte, bytes)
//   code   (codeLen bytes)
//   nLines x (u16 pc, u16 regel)
// ----------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include "muziek.h"

namespace vm {

enum Op : uint8_t {
  PUSHB = 0x01, PUSHW = 0x02, PUSHS = 0x03, POP = 0x04, DUP = 0x05, ROT = 0x06, SWAP = 0x07,
  LDG = 0x10, STG = 0x11, LDL = 0x12, STL = 0x13, LDGA = 0x14, STGA = 0x15, LDLA = 0x16, STLA = 0x17, STRAT = 0x18,
  TU8 = 0x20, TS8 = 0x21, TU16 = 0x22, TS16 = 0x23, TBOOL = 0x24,
  ADD = 0x30, SUB, MUL, DIVS, DIVU, MODS, MODU, SHL, SHRS, SHRU, AND, OR, XOR, NEG, BNOT, LNOT,
  EQ = 0x40, NE, LTS, LTU, LES, LEU, GTS, GTU, GES, GEU,
  JMP = 0x50, JZ = 0x51, JNZ = 0x52, CALL = 0x54, RET = 0x55, RETV = 0x56, SYS = 0x57,
};

enum Sys : uint8_t {
  S_NOOT, S_DRUM, S_AKKOORD, S_CC, S_INSTRUMENT, S_FILTER, S_BEND, S_PAT, S_TOON,
  S_SCHAAL, S_MINEUR, S_DRIEKLANK, S_SINUS, S_RND, S_MIN, S_MAX, S_ABS, S_PRINT, S_STRLEN, N_SYS
};
static const uint8_t SYS_ARGC[N_SYS] = { 4, 3, 5, 3, 2, 3, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1 };

// vaste globale variabelen (dezelfde volgorde als in de compiler)
enum { G_T, G_S, G_M, G_TEL, G_BPM, G_SWING, G_MATEN, G_NOOTIN, G_VOL, N_VAST };

static const uint32_t STR_TAG = 0x53000000u;
static const int MAX_STACK = 256, MAX_LOCALS = 2048, MAX_FRAMES = 64, MAX_GLOBALS = 8192;
static const uint32_t BUDGET = 200000;            // instructies per aanroep

typedef void (*PrintFn)(int32_t v);

class Machine {
public:
  muziek::Muziek *mz = nullptr;
  PrintFn print = nullptr;
  std::string fout;
  int foutRegel = 0;

  bool laad(const uint8_t *d, size_t n) {
    reset();
    if (n < 24 || memcmp(d, "SBC1", 4) != 0) return zetFout(0, "geen synth-bytecode (SBC1)");
    if (d[4] != 1) return zetFout(0, "bytecode-versie wordt niet ondersteund");
    size_t p = 6;
    auto u16 = [&](uint16_t &v) { if (p + 2 > n) return false; v = (uint16_t)(d[p] | (d[p + 1] << 8)); p += 2; return true; };
    uint16_t nG, nF, nS, cl, nL;
    if (!u16(nG) || !u16(nF) || !u16(fInit) || !u16(fStart) || !u16(fStap) || !u16(nS) || !u16(cl) || !u16(nL))
      return zetFout(0, "bytecode is afgekapt");
    if (nG < N_VAST || nG > MAX_GLOBALS) return zetFout(0, "ongeldig aantal globale variabelen");
    if (nF == 0 || fInit >= nF || fStap >= nF || (fStart != 0xFFFF && fStart >= nF)) return zetFout(0, "ongeldige functietabel");
    funcs.resize(nF);
    for (auto &f : funcs) {
      if (p + 4 > n) return zetFout(0, "bytecode is afgekapt");
      f.addr = (uint16_t)(d[p] | (d[p + 1] << 8)); f.nParams = d[p + 2]; f.nLocals = d[p + 3]; p += 4;
      if (f.nParams > f.nLocals) return zetFout(0, "ongeldige functie");
    }
    strs.resize(nS);
    for (auto &s : strs) {
      uint16_t len;
      if (!u16(len) || p + len > n) return zetFout(0, "bytecode is afgekapt");
      s.assign(d + p, d + p + len); p += len;
    }
    if (p + cl > n) return zetFout(0, "bytecode is afgekapt");
    code.assign(d + p, d + p + cl); p += cl;
    for (auto &f : funcs) if (f.addr >= cl) return zetFout(0, "functie buiten de code");
    lines.resize(nL);
    for (auto &l : lines) {
      if (p + 4 > n) return zetFout(0, "bytecode is afgekapt");
      l.pc = (uint16_t)(d[p] | (d[p + 1] << 8)); l.line = (uint16_t)(d[p + 2] | (d[p + 3] << 8)); p += 4;
    }
    globals.assign(nG, 0);
    globals[G_BPM] = 120; globals[G_MATEN] = 8; globals[G_NOOTIN] = 60; globals[G_VOL] = 100;
    geladen = true;
    return roep(fInit);
  }

  bool start() { return fStart == 0xFFFF || roep(fStart); }

  // één zestiende noot: noten loslaten, t/s/m/tel zetten, stap() uitvoeren
  bool stap(uint32_t t) {
    if (!geladen) return false;
    mz->loslaten(t);
    mz->stapT = t;
    globals[G_T] = (int32_t)t;
    globals[G_S] = (int32_t)(t & 15);
    globals[G_M] = (int32_t)(t >> 4);
    globals[G_TEL] = (int32_t)((t >> 2) & 3);
    return roep(fStap);
  }

  int32_t &g(int i) { return globals[i]; }
  bool isGeladen() const { return geladen; }

private:
  struct Func { uint16_t addr; uint8_t nParams, nLocals; };
  struct Line { uint16_t pc, line; };
  struct Frame { uint32_t retPc; uint16_t base; uint16_t func; };
  std::vector<uint8_t> code;
  std::vector<std::vector<uint8_t>> strs;
  std::vector<Func> funcs;
  std::vector<Line> lines;
  std::vector<int32_t> globals;
  uint16_t fInit = 0, fStart = 0xFFFF, fStap = 0;
  bool geladen = false;

  int32_t stk[MAX_STACK];
  int32_t loc[MAX_LOCALS];
  Frame frames[MAX_FRAMES];

  void reset() {
    code.clear(); strs.clear(); funcs.clear(); lines.clear(); globals.clear();
    geladen = false; fout.clear(); foutRegel = 0;
  }
  bool zetFout(int regel, const char *t) { fout = t; foutRegel = regel; geladen = false; return false; }
  int regelBij(uint32_t pc) const {
    int r = 0;
    for (auto &l : lines) { if (l.pc <= pc) r = l.line; else break; }
    return r;
  }

  const std::vector<uint8_t> *str(int32_t h) const {
    uint32_t u = (uint32_t)h;
    if ((u & 0xFF000000u) != STR_TAG) return nullptr;
    u &= 0xFFFFFFu;
    return u < strs.size() ? &strs[u] : nullptr;
  }

  // voert functie f uit tot hij terugkeert
  bool roep(uint16_t f) {
    if (f >= funcs.size()) return zetFout(0, "onbekende functie");
    int sp = 0, fp = 0, locTop = 0;
    uint32_t pc = 0, opPc = 0, budget = BUDGET;
    const uint32_t cl = (uint32_t)code.size();
    const uint8_t *c = code.data();

#define FOUT(t) do { fout = (t); foutRegel = regelBij(opPc); return false; } while (0)
#define NEED(k) do { if (pc + (k) > cl) FOUT("bytecode is beschadigd"); } while (0)
#define POPV(x) do { if (sp <= 0) FOUT("stapel leeg"); (x) = stk[--sp]; } while (0)
#define PUSHV(x) do { if (sp >= MAX_STACK) FOUT("stapel vol (te ingewikkelde uitdrukking)"); stk[sp++] = (x); } while (0)
#define U16() ((uint32_t)c[pc] | ((uint32_t)c[pc + 1] << 8))

    // de eerste frame
    {
      const Func &fn = funcs[f];
      if (fn.nLocals > MAX_LOCALS) FOUT("te veel lokale variabelen");
      for (int i = 0; i < fn.nLocals; i++) loc[i] = 0;
      frames[0] = { 0xFFFFFFFFu, 0, f };
      fp = 1; locTop = fn.nLocals; pc = fn.addr;
    }
    int base = 0;

    for (;;) {
      if (--budget == 0) FOUT("te veel rekenwerk in één stap (oneindige lus?)");
      opPc = pc;
      NEED(1);
      uint8_t op = c[pc++];
      int32_t a, b;
      switch (op) {
        case PUSHB: NEED(1); PUSHV((int32_t)(int8_t)c[pc]); pc++; break;
        case PUSHW: NEED(4); PUSHV((int32_t)((uint32_t)c[pc] | ((uint32_t)c[pc + 1] << 8) | ((uint32_t)c[pc + 2] << 16) | ((uint32_t)c[pc + 3] << 24))); pc += 4; break;
        case PUSHS: { NEED(2); uint32_t i = U16(); pc += 2; if (i >= strs.size()) FOUT("onbekende tekst"); PUSHV((int32_t)(STR_TAG | i)); break; }
        case POP: POPV(a); break;
        case DUP: { if (sp <= 0) FOUT("stapel leeg"); int32_t top = stk[sp - 1]; PUSHV(top); break; }
        case SWAP: { if (sp < 2) FOUT("stapel leeg"); int32_t x = stk[sp - 1]; stk[sp - 1] = stk[sp - 2]; stk[sp - 2] = x; break; }
        case ROT: {                                  // x y z -> y z x
          if (sp < 3) FOUT("stapel leeg");
          int32_t x = stk[sp - 3]; stk[sp - 3] = stk[sp - 2]; stk[sp - 2] = stk[sp - 1]; stk[sp - 1] = x; break;
        }

        case LDG: { NEED(2); uint32_t i = U16(); pc += 2; if (i >= globals.size()) FOUT("onbekende variabele"); PUSHV(globals[i]); break; }
        case STG: { NEED(2); uint32_t i = U16(); pc += 2; if (i >= globals.size()) FOUT("onbekende variabele"); if (sp <= 0) FOUT("stapel leeg"); globals[i] = stk[sp - 1]; break; }
        case LDL: { NEED(1); uint32_t i = c[pc++]; if (base + i >= (uint32_t)locTop) FOUT("onbekende lokale variabele"); PUSHV(loc[base + i]); break; }
        case STL: { NEED(1); uint32_t i = c[pc++]; if (base + i >= (uint32_t)locTop) FOUT("onbekende lokale variabele"); if (sp <= 0) FOUT("stapel leeg"); loc[base + i] = stk[sp - 1]; break; }
        case LDGA: case STGA: {
          NEED(4); uint32_t bs = U16(), len = (uint32_t)c[pc + 2] | ((uint32_t)c[pc + 3] << 8); pc += 4;
          int32_t v = 0;
          if (op == STGA) POPV(v);
          POPV(a);
          if (a < 0 || (uint32_t)a >= len) {
            char m[64]; snprintf(m, sizeof m, "index %ld buiten de array (lengte %lu)", (long)a, (unsigned long)len); FOUT(m);
          }
          if (bs + len > globals.size()) FOUT("array buiten het geheugen");
          if (op == LDGA) PUSHV(globals[bs + a]); else { globals[bs + a] = v; PUSHV(v); }
          break;
        }
        case LDLA: case STLA: {
          NEED(3); uint32_t bs = c[pc], len = (uint32_t)c[pc + 1] | ((uint32_t)c[pc + 2] << 8); pc += 3;
          int32_t v = 0;
          if (op == STLA) POPV(v);
          POPV(a);
          if (a < 0 || (uint32_t)a >= len) {
            char m[64]; snprintf(m, sizeof m, "index %ld buiten de array (lengte %lu)", (long)a, (unsigned long)len); FOUT(m);
          }
          if (base + bs + len > (uint32_t)locTop) FOUT("array buiten het geheugen");
          if (op == LDLA) PUSHV(loc[base + bs + a]); else { loc[base + bs + a] = v; PUSHV(v); }
          break;
        }
        case STRAT: {
          POPV(b); POPV(a);
          const std::vector<uint8_t> *s = str(a);
          if (!s) FOUT("geen tekst");
          if (b < 0 || (uint32_t)b > s->size()) FOUT("index buiten de tekst");
          PUSHV((uint32_t)b == s->size() ? 0 : (*s)[b]);
          break;
        }

        case TU8:   if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = (uint8_t)stk[sp - 1]; break;
        case TS8:   if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = (int8_t)(uint8_t)stk[sp - 1]; break;
        case TU16:  if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = (uint16_t)stk[sp - 1]; break;
        case TS16:  if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = (int16_t)(uint16_t)stk[sp - 1]; break;
        case TBOOL: if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = stk[sp - 1] != 0; break;

        case NEG:  if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = (int32_t)(0u - (uint32_t)stk[sp - 1]); break;
        case BNOT: if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = ~stk[sp - 1]; break;
        case LNOT: if (sp <= 0) FOUT("stapel leeg"); stk[sp - 1] = !stk[sp - 1]; break;

        default:
          if (op >= ADD && op <= GEU && op != NEG && op != BNOT && op != LNOT) {
            POPV(b); POPV(a);
            uint32_t ua = (uint32_t)a, ub = (uint32_t)b;
            int32_t r = 0;
            switch (op) {
              case ADD: r = (int32_t)(ua + ub); break;
              case SUB: r = (int32_t)(ua - ub); break;
              case MUL: r = (int32_t)(ua * ub); break;
              case DIVS: if (b == 0) FOUT("deling door 0"); if (a == INT32_MIN && b == -1) FOUT("deling loopt over"); r = a / b; break;
              case DIVU: if (ub == 0) FOUT("deling door 0"); r = (int32_t)(ua / ub); break;
              case MODS: if (b == 0) FOUT("deling door 0 (%)"); if (a == INT32_MIN && b == -1) FOUT("deling loopt over"); r = a % b; break;
              case MODU: if (ub == 0) FOUT("deling door 0 (%)"); r = (int32_t)(ua % ub); break;
              case SHL:  r = (int32_t)(ua << (ub & 31)); break;
              case SHRS: r = a >> (ub & 31); break;
              case SHRU: r = (int32_t)(ua >> (ub & 31)); break;
              case AND: r = a & b; break;
              case OR:  r = a | b; break;
              case XOR: r = a ^ b; break;
              case EQ: r = a == b; break;   case NE: r = a != b; break;
              case LTS: r = a < b; break;   case LTU: r = ua < ub; break;
              case LES: r = a <= b; break;  case LEU: r = ua <= ub; break;
              case GTS: r = a > b; break;   case GTU: r = ua > ub; break;
              case GES: r = a >= b; break;  case GEU: r = ua >= ub; break;
              default: FOUT("onbekende instructie");
            }
            PUSHV(r);
            break;
          }
          switch (op) {
            case JMP: NEED(2); pc = U16(); break;
            case JZ:  { NEED(2); uint32_t to = U16(); pc += 2; POPV(a); if (!a) pc = to; break; }
            case JNZ: { NEED(2); uint32_t to = U16(); pc += 2; POPV(a); if (a) pc = to; break; }
            case CALL: {
              NEED(2); uint32_t fi = U16(); pc += 2;
              if (fi >= funcs.size()) FOUT("onbekende functie");
              const Func &fn = funcs[fi];
              if (fp >= MAX_FRAMES) FOUT("te diepe recursie");
              if (sp < fn.nParams) FOUT("stapel leeg");
              if (locTop + fn.nLocals > MAX_LOCALS) FOUT("te veel lokale variabelen (te diepe recursie?)");
              int nb = locTop;
              for (int i = 0; i < fn.nLocals; i++) loc[nb + i] = 0;
              for (int i = 0; i < fn.nParams; i++) loc[nb + i] = stk[sp - fn.nParams + i];
              sp -= fn.nParams;
              frames[fp++] = { pc, (uint16_t)nb, (uint16_t)fi };
              locTop = nb + fn.nLocals; base = nb; pc = fn.addr;
              break;
            }
            case RET: case RETV: {
              int32_t v = 0;
              if (op == RET) POPV(v);
              Frame fr = frames[--fp];
              locTop = fr.base;
              if (fp == 0) return true;
              base = frames[fp - 1].base;
              pc = fr.retPc;
              PUSHV(v);
              break;
            }
            case SYS: {
              NEED(2); uint8_t id = c[pc], argc = c[pc + 1]; pc += 2;
              if (id >= N_SYS || argc != SYS_ARGC[id]) FOUT("onbekende ingebouwde functie");
              if (sp < argc) FOUT("stapel leeg");
              int32_t *ar = &stk[sp - argc];
              sp -= argc;
              int32_t r = 0;
              const std::vector<uint8_t> *s = nullptr;
              if (id == S_PAT || id == S_TOON || id == S_STRLEN) { s = str(ar[0]); if (!s) FOUT("geen tekst"); }
              switch (id) {
                case S_NOOT: mz->noot(ar[0], ar[1], ar[2], ar[3]); break;
                case S_DRUM: mz->drum(ar[0], ar[1], ar[2]); break;
                case S_AKKOORD: mz->akkoord(ar[0], ar[1], ar[2], ar[3], ar[4]); break;
                case S_CC: mz->cc(ar[0], ar[1], ar[2]); break;
                case S_INSTRUMENT: mz->instrument(ar[0], ar[1]); break;
                case S_FILTER: mz->filter(ar[0], ar[1], ar[2]); break;
                case S_BEND: mz->bend(ar[0], ar[1]); break;
                case S_PAT: r = muziek::Muziek::pat(s->data(), (int)s->size(), ar[1]); break;
                case S_TOON: r = muziek::Muziek::toon(s->data(), (int)s->size(), ar[1]); break;
                case S_SCHAAL: r = muziek::Muziek::schaal(ar[0]); break;
                case S_MINEUR: r = muziek::Muziek::mineur(ar[0]); break;
                case S_DRIEKLANK: r = muziek::Muziek::drieklank(ar[0], ar[1]); break;
                case S_SINUS: r = muziek::Muziek::sinus(ar[0]); break;
                case S_RND: r = mz->rnd(ar[0]); break;
                case S_MIN: r = muziek::Muziek::min(ar[0], ar[1]); break;
                case S_MAX: r = muziek::Muziek::max(ar[0], ar[1]); break;
                case S_ABS: r = muziek::Muziek::abs(ar[0]); break;
                case S_PRINT: if (print) print(ar[0]); break;
                case S_STRLEN: r = (int32_t)s->size(); break;
              }
              PUSHV(r);
              break;
            }
            default: FOUT("onbekende instructie");
          }
      }
    }
#undef FOUT
#undef NEED
#undef POPV
#undef PUSHV
#undef U16
  }
};

}  // namespace vm
