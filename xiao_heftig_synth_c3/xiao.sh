#!/bin/bash
# =============================================================================
#  xiao.sh  —  XIAO Heftig Synth voor de Seeed XIAO MIDI Synthesizer (ESP32-C3)
#              bouwen en flitsen vanaf een Raspberry Pi (of elke Linux-machine)
#
#  ./xiao.sh flits        kant-en-klare firmware uit firmware/ flitsen (snel)
#  ./xiao.sh bouw         sketch compileren -> build/*.bin
#  ./xiao.sh alles        bouwen en flitsen
#  ./xiao.sh web          XIAO Flitser openen in Chromium (flitsen + /synth bewerken)
#  ./xiao.sh monitor      meldingen van de synth bekijken (Ctrl+C = stoppen)
#
#  Optie:  POORT=/dev/ttyACM1 ./xiao.sh flits
#
#  'bouw' installeert de eerste keer arduino-cli en de ESP32-core 3.2.0
#  (~1,5 GB in ~/.arduino15, vraagt sudo alleen voor python3-pip als dat ontbreekt).
#  Flitsen gebruikt esptool (pip). Bestanden in /synth blijven bewaard.
# =============================================================================
set -euo pipefail

HIER="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ACTIE="${1:-flits}"
SKETCH="$HIER"
FW="$HIER/firmware"
BUILD="$HIER/build"
CORE_VERSIE=3.2.0
FQBN=esp32:esp32:XIAO_ESP32C3
ESP_INDEX=https://espressif.github.io/arduino-esp32/package_esp32_index.json
ACLI="${ACLI:-$HOME/.local/bin/arduino-cli}"

say() { printf '\033[1m%s\033[0m\n' "$*"; }

poort() {
  if [ -n "${POORT:-}" ]; then echo "$POORT"; return; fi
  for t in /dev/ttyACM*; do
    [ -e "$t" ] || continue
    v=$(cat "/sys/class/tty/$(basename "$t")/device/../idVendor" 2>/dev/null || true)
    [ "$v" = "303a" ] && { echo "$t"; return; }
  done
  echo "Geen XIAO ESP32-C3 gevonden (USB 303a:1001). Datakabel? Of: POORT=/dev/ttyACMx $0 $ACTIE" >&2
  exit 1
}

esptool() {
  if ! python3 -c "import esptool" 2>/dev/null; then
    say "esptool installeren (pip)"
    command -v pip3 >/dev/null || { sudo apt-get update && sudo apt-get install -y python3-pip; }
    pip3 install --user --break-system-packages esptool 2>/dev/null || pip3 install --user esptool
  fi
  python3 -m esptool "$@"
}

arduino_cli() {
  if [ ! -x "$ACLI" ]; then
    say "arduino-cli installeren"
    local arch
    case "$(uname -m)" in
      aarch64|arm64) arch=Linux_ARM64 ;;
      armv7l|armv6l) arch=Linux_ARMv7 ;;
      x86_64)        arch=Linux_64bit ;;
      *) echo "onbekende processor $(uname -m)"; exit 1 ;;
    esac
    mkdir -p "$(dirname "$ACLI")"
    curl -fsSL "https://github.com/arduino/arduino-cli/releases/download/v1.2.2/arduino-cli_1.2.2_${arch}.tar.gz" \
      | tar xz -C "$(dirname "$ACLI")" arduino-cli
  fi
  if ! "$ACLI" core list 2>/dev/null | grep -q "esp32:esp32 *$CORE_VERSIE"; then
    say "ESP32-core $CORE_VERSIE installeren (eenmalig, groot)"
    "$ACLI" config init --overwrite >/dev/null
    "$ACLI" config add board_manager.additional_urls "$ESP_INDEX"
    "$ACLI" core update-index
    "$ACLI" core install "esp32:esp32@$CORE_VERSIE"
  fi
}

bouw() {
  arduino_cli
  say "compileren"
  "$ACLI" compile --fqbn "$FQBN" --output-dir "$BUILD" "$SKETCH"
  FLITS_DIR="$BUILD"
  BOOT="$BUILD/xiao_heftig_synth_c3.ino.bootloader.bin"
  PART="$BUILD/xiao_heftig_synth_c3.ino.partitions.bin"
  APP="$BUILD/xiao_heftig_synth_c3.ino.bin"
  APP0="$(dirname "$(find "$HOME/.arduino15/packages/esp32/hardware/esp32/$CORE_VERSIE" -name boot_app0.bin | head -1)")/boot_app0.bin"
}

flits() {
  local p; p="$(poort)"
  say "flitsen naar $p"
  esptool --chip esp32c3 --port "$p" --baud 921600 \
    --before default_reset --after hard_reset write_flash \
    0x0 "$BOOT" 0x8000 "$PART" 0xe000 "$APP0" 0x10000 "$APP"
  say "klaar — de synth start opnieuw op"
}

kant_en_klaar() {
  BOOT="$FW/bootloader.bin"; PART="$FW/partitions.bin"
  APP0="$FW/boot_app0.bin"; APP="$FW/xiao_heftig_synth_c3.bin"
}

case "$ACTIE" in
  flits)   kant_en_klaar; flits ;;
  bouw)    bouw; ls -l "$BUILD"/*.bin ;;
  alles)   bouw; flits ;;
  web)     for b in chromium-browser chromium google-chrome; do
             if command -v "$b" >/dev/null; then exec "$b" "file://$HIER/xiao_flitser.html"; fi
           done
           echo "Chromium niet gevonden: sudo apt install chromium-browser"; exit 1 ;;
  monitor) p="$(poort)"; stty -F "$p" 115200 raw -echo -hupcl; echo "INFO" > "$p"; exec cat "$p" ;;
  *)       sed -n '3,19p' "$0"; exit 1 ;;
esac
