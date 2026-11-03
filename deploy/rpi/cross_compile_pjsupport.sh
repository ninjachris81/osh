#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_pjsupport.sh <sysroot>

Optional variables:
    RPI_PJSUPPORT_BUILD_DIR  PJSIP build root (default: build-rpi-pjsupport)
    RPI_BUILD_JOBS           Parallel build jobs (default: 4)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -ne 1 ]]; then
    echo "A sysroot is required." >&2
    usage >&2
    exit 2
fi

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
RPI_SYSROOT="$1"
RPI_CROSS_PREFIX="aarch64-linux-gnu-"
RPI_PJSUPPORT_BUILD_DIR="${RPI_PJSUPPORT_BUILD_DIR:-$ROOT_DIR/build-rpi-pjsupport}"
RPI_BUILD_JOBS="${RPI_BUILD_JOBS:-4}"

if [[ ! -d "$RPI_SYSROOT" ]]; then
    echo "Required sysroot directory does not exist: $RPI_SYSROOT" >&2
    exit 3
fi

if [[ ! "$RPI_BUILD_JOBS" =~ ^[1-9][0-9]*$ ]]; then
    echo "RPI_BUILD_JOBS must be a positive integer: $RPI_BUILD_JOBS" >&2
    exit 2
fi

CROSS_C_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}gcc"
CROSS_CXX_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}g++"

for compiler in "$CROSS_C_COMPILER" "$CROSS_CXX_COMPILER"; do
    if [[ ! -x "$compiler" ]]; then
        echo "Required host compiler is not executable: $compiler" >&2
        exit 3
    fi
done

PJPROJECT_REV="$(git -C "$ROOT_DIR/pjproject" rev-parse --verify HEAD)"
PJPROJECT_BUILD_DIR="$RPI_PJSUPPORT_BUILD_DIR/pjproject-$PJPROJECT_REV"

mkdir -p "$RPI_PJSUPPORT_BUILD_DIR"
rm -rf "$PJPROJECT_BUILD_DIR"
mkdir -p "$PJPROJECT_BUILD_DIR"
git -C "$ROOT_DIR/pjproject" archive HEAD | tar -x -C "$PJPROJECT_BUILD_DIR"

echo "Configuring PJProject for AArch64 in $PJPROJECT_BUILD_DIR"
(
    cd "$PJPROJECT_BUILD_DIR"
    CC="$CROSS_C_COMPILER" \
    CXX="$CROSS_CXX_COMPILER" \
    CFLAGS="--sysroot=$RPI_SYSROOT" \
    LDFLAGS="--sysroot=$RPI_SYSROOT" \
        ./configure --host="${RPI_CROSS_PREFIX%-}" --disable-libwebrtc --enable-shared
)
make -C "$PJPROJECT_BUILD_DIR" dep
make -C "$PJPROJECT_BUILD_DIR" -j"$RPI_BUILD_JOBS"

echo "PJProject cross-build completed: $PJPROJECT_BUILD_DIR"
