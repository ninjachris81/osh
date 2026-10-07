#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_libqml.sh <sysroot>

Cross-compile libsml and install it into <sysroot>/usr/local.
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

if [[ ! -d "$1" ]]; then
    echo "Required sysroot directory does not exist: $1" >&2
    exit 3
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
LIBSML_DIR="$ROOT_DIR/libsml"
RPI_SYSROOT="$(cd "$1" && pwd)"
RPI_CROSS_PREFIX="${RPI_CROSS_PREFIX:-aarch64-linux-gnu-}"
RPI_BUILD_JOBS="${RPI_BUILD_JOBS:-4}"
CROSS_C_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}gcc"
CROSS_LINKER="/usr/bin/${RPI_CROSS_PREFIX}ld"
CROSS_ARCHIVER="/usr/bin/${RPI_CROSS_PREFIX}ar"

if [[ ! -x "$CROSS_C_COMPILER" ]]; then
    echo "Required cross-compiler not found or not executable: $CROSS_C_COMPILER" >&2
    exit 3
fi
if [[ ! -x "$CROSS_LINKER" ]]; then
    echo "Required cross-linker not found or not executable: $CROSS_LINKER" >&2
    exit 3
fi
if [[ ! -x "$CROSS_ARCHIVER" ]]; then
    echo "Required cross-archiver not found or not executable: $CROSS_ARCHIVER" >&2
    exit 3
fi

SYSROOT_FLAGS="--sysroot=$RPI_SYSROOT -march=armv8-a -O2 -pipe -DNDEBUG -isystem $RPI_SYSROOT/usr/include/aarch64-linux-gnu -B$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -B$RPI_SYSROOT/lib/aarch64-linux-gnu"
SYSROOT_LINK_FLAGS="--sysroot=$RPI_SYSROOT -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -L$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -L$RPI_SYSROOT/lib/aarch64-linux-gnu"
LIBSML_CFLAGS="$SYSROOT_FLAGS -I./include/ -fPIC -fno-stack-protector -g -std=c99 -Wall -Wextra -pedantic"
LIBSML_LDFLAGS="$SYSROOT_LINK_FLAGS -Wl,-soname=libsml.so.1 -shared"
MAKE_ARGS=(
    "-j$RPI_BUILD_JOBS"
    "CC=$CROSS_C_COMPILER"
    "LD=$CROSS_LINKER"
    "AR=$CROSS_ARCHIVER"
    "CFLAGS=$LIBSML_CFLAGS"
    "LDFLAGS=$LIBSML_LDFLAGS"
)

echo "Building libsml for AArch64 using sysroot $RPI_SYSROOT"
make -C "$LIBSML_DIR/sml" "${MAKE_ARGS[@]}"
sudo make -C "$LIBSML_DIR/sml" \
    "${MAKE_ARGS[@]}" \
    install \
    DESTDIR="$RPI_SYSROOT" \
    prefix=/usr/local

echo "libsml cross-build completed"
