#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_osh_services.sh <sysroot> [qt-target-root]

Optional variables:
    RPI_QT_SRC_DIR      Qt 6.8.2 source tree (default: $HOME/qt-src)
    RPI_QT_HOST_ROOT    Host Qt 6.8.2 install (default: $HOME/qt-6.8.2)
    RPI_BUILD_DIR       Main build directory (default: build-rpi)
    RPI_BUILD_JOBS      Parallel build jobs (default: 2)
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

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
RPI_SYSROOT="$1"
RPI_QT_SRC_DIR="${RPI_QT_SRC_DIR:-$HOME/qt-src}"
RPI_QT_HOST_ROOT="${RPI_QT_HOST_ROOT:-$HOME/qt-6.8.2}"
RPI_CROSS_PREFIX="aarch64-linux-gnu-"
RPI_BUILD_DIR="${RPI_BUILD_DIR:-$ROOT_DIR/build-rpi}"
RPI_QT_BUILD_DIR="${RPI_QT_BUILD_DIR:-$ROOT_DIR/qt-build-rpi}"
RPI_BUILD_JOBS="${RPI_BUILD_JOBS:-3}"
RPI_QT_TARGET_MKSPEC="${RPI_QT_TARGET_MKSPEC:-linux-aarch64-gnu-g++}"
RPI_QT_MKSPECS_DIR="${RPI_QT_MKSPECS_DIR:-$RPI_QT_SRC_DIR/qtbase/mkspecs}"

if [[ -n "${2:-}" ]]; then
    if [[ "$2" == "/usr" ]]; then
        RPI_QT_ROOT="$RPI_SYSROOT/usr"
    elif [[ "$2" == /* ]]; then
        RPI_QT_ROOT="$2"
    else
        RPI_QT_ROOT="$RPI_SYSROOT/$2"
    fi
else
    RPI_QT_ROOT="$RPI_SYSROOT/usr"
fi

if [[ ! "$RPI_BUILD_JOBS" =~ ^[1-9][0-9]*$ ]]; then
    echo "RPI_BUILD_JOBS must be a positive integer: $RPI_BUILD_JOBS" >&2
    exit 2
fi

CROSS_C_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}gcc"
CROSS_CXX_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}g++"

if [[ ! -e "$RPI_SYSROOT" ]]; then
    echo "Required path does not exist: $RPI_SYSROOT" >&2
    exit 3
fi

for compiler in "$CROSS_C_COMPILER" "$CROSS_CXX_COMPILER"; do
    if [[ ! -x "$compiler" ]]; then
        echo "Required host compiler is not executable: $compiler" >&2
        exit 3
    fi
done

TARGET_QT_PREFIX_PATH="${RPI_QT_ROOT};${RPI_QT_HOST_ROOT}"

TOOLCHAIN_ARGS=(
    "-DCMAKE_SYSTEM_NAME=Linux"
    "-DCMAKE_SYSTEM_PROCESSOR=aarch64"
    "-DCMAKE_SYSROOT=$RPI_SYSROOT"
    "-DCMAKE_C_COMPILER=$CROSS_C_COMPILER"
    "-DCMAKE_CXX_COMPILER=$CROSS_CXX_COMPILER"
    "-DCMAKE_C_FLAGS=--sysroot=$RPI_SYSROOT -B$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -B$RPI_SYSROOT/lib/aarch64-linux-gnu"
    "-DCMAKE_CXX_FLAGS=--sysroot=$RPI_SYSROOT -B$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -B$RPI_SYSROOT/lib/aarch64-linux-gnu"
    "-DCMAKE_EXE_LINKER_FLAGS=--sysroot=$RPI_SYSROOT -L$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -L$RPI_SYSROOT/lib/aarch64-linux-gnu"
    "-DCMAKE_SHARED_LINKER_FLAGS=--sysroot=$RPI_SYSROOT -L$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -L$RPI_SYSROOT/lib/aarch64-linux-gnu"
    "-DCMAKE_MAKE_PROGRAM=/usr/bin/gmake"
    "-DCMAKE_FIND_ROOT_PATH=$RPI_SYSROOT"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER"
    "-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY"
    "-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY"
)

cmake -S "$ROOT_DIR" -B "$RPI_BUILD_DIR" \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    "-DCMAKE_PREFIX_PATH=${TARGET_QT_PREFIX_PATH}" \
    -DQT_HOST_PATH="$RPI_QT_HOST_ROOT" \
    -DQt6HostInfo_DIR="$RPI_QT_HOST_ROOT/lib/cmake/Qt6HostInfo" \
    -DQT_MKSPECS_DIR="$RPI_QT_MKSPECS_DIR" \
    -DQT_QMAKE_TARGET_MKSPEC="$RPI_QT_TARGET_MKSPEC" \
    -DQT_GENERATE_SBOM=OFF \
    "${TOOLCHAIN_ARGS[@]}"

cmake --build "$RPI_BUILD_DIR" --target OSHServices --parallel "$RPI_BUILD_JOBS"

echo "OSHServices cross-build completed: $RPI_BUILD_DIR"
