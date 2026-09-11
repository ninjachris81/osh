#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_all.sh <sysroot> [qt-target-root]

Runs the three cross-compile steps in order:
  1) WiringPi
  2) Qt6 + qtmqtt
  3) OSHServices
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "A sysroot is required, and a Qt target root is optional." >&2
    usage >&2
    exit 2
fi

SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "[1/3] Building WiringPi"
"$SCRIPTDIR/cross_compile_wiringpi.sh" "$@"

echo "[2/3] Building Qt6 and qtmqtt"
"$SCRIPTDIR/cross_compile_qt6.sh" "$@"

echo "[3/3] Building OSHServices"
"$SCRIPTDIR/cross_compile_osh_services.sh" "$@"

echo "All cross-builds completed."
