# XIAO Heftig Synth

Firmware voor de Seeed XIAO MIDI Synthesizer (XIAO ESP32-C3 + SAM2695).

De synthstukken zijn gewone C++. De XIAO Flitser compileert ze in de browser
naar bytecode; de firmware voert die uit en stuurt MIDI naar de SAM2695.

- `xiao_heftig_synth_c3.ino` — hoofdprogramma: knoppen, DIN-MIDI, USB-protocol, afspelen
- `vm.h` — de bytecode-machine (met controles op arrays, deling door 0, oneindige lussen)
- `muziek.h` — de muziekfuncties: noot, drum, akkoord, schaal, pat, toon, …
- `voorbeelden.h` — 271 ingebouwde stukken (gegenereerd): 3 techno, 12 complex, 256 bytebeats
- `synth.h` — compileer een stuk met gewone C++ op een computer:
  `g++ -std=c++17 -include synth.h stuk.cpp -o stuk && ./stuk 64`

Elke wijziging aan een C++-bestand wordt automatisch gebouwd door GitHub Actions
(`.github/workflows/bouw.yml`). Het resultaat — firmware of foutmeldingen — komt
op de tak `build`, waar de XIAO Flitser het ophaalt en naar de XIAO flitst.

Bord: `esp32:esp32:XIAO_ESP32C3`, ESP32-core 3.2.0. Geen externe libraries.
