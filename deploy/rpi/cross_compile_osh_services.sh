#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_osh_services.sh <sysroot> <qt-root>

Optional variables:
  RPI_BUILD_DIR       Main build directory (default: build-rpi)
  RPI_QTMQTT_BUILD_DIR qtmqtt build directory (default: qtmqtt-build-rpi)
  RPI_QTMQTT_INSTALL  qtmqtt install directory (default: qtmqtt-install-rpi)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -ne 2 ]]; then
    echo "A sysroot and an ARM64 Qt root are required." >&2
    usage >&2
    exit 2
fi

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
RPI_SYSROOT="$1"
RPI_QT_ROOT="$2"
RPI_CROSS_PREFIX="aarch64-linux-gnu-"
RPI_BUILD_DIR="${RPI_BUILD_DIR:-$ROOT_DIR/build-rpi}"
RPI_QTMQTT_BUILD_DIR="${RPI_QTMQTT_BUILD_DIR:-$ROOT_DIR/qtmqtt-build-rpi}"
RPI_QTMQTT_INSTALL="${RPI_QTMQTT_INSTALL:-$ROOT_DIR/qtmqtt-install-rpi}"

CROSS_C_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}gcc"
CROSS_CXX_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}g++"
for required_path in "$RPI_SYSROOT" "$RPI_QT_ROOT"; do
    if [[ ! -e "$required_path" ]]; then
        echo "Required path does not exist: $required_path" >&2
        exit 3
    fi
done
for compiler in "$CROSS_C_COMPILER" "$CROSS_CXX_COMPILER"; do
    if [[ ! -x "$compiler" ]]; then
        echo "Required host compiler is not executable: $compiler" >&2
        exit 3
    fi
done

QT6_CONFIG="$(find "$RPI_QT_ROOT" -path '*/cmake/Qt6/Qt6Config.cmake' -print -quit)"
if [[ -z "$QT6_CONFIG" ]]; then
    echo "Qt6Config.cmake was not found below $RPI_QT_ROOT." >&2
    echo "Expected a path such as <qt-root>/lib/aarch64-linux-gnu/cmake/Qt6/Qt6Config.cmake." >&2
    exit 4
fi

TOOLCHAIN_ARGS=(
    "-DCMAKE_SYSTEM_NAME=Linux"
    "-DCMAKE_SYSTEM_PROCESSOR=aarch64"
    "-DCMAKE_SYSROOT=$RPI_SYSROOT"
    "-DCMAKE_C_COMPILER=$CROSS_C_COMPILER"
    "-DCMAKE_CXX_COMPILER=$CROSS_CXX_COMPILER"
    "-DCMAKE_MAKE_PROGRAM=/usr/bin/gmake"
    "-DCMAKE_FIND_ROOT_PATH=$RPI_SYSROOT"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER"
    "-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY"
    "-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=BOTH"
)

if [[ -f "$RPI_QTMQTT_BUILD_DIR/CMakeCache.txt" || -f "$RPI_BUILD_DIR/CMakeCache.txt" ]]; then
    echo "Removing stale RPi CMake caches"
    rm -rf "$RPI_QTMQTT_BUILD_DIR" "$RPI_BUILD_DIR"
fi

cmake -S "$ROOT_DIR/qtmqtt" -B "$RPI_QTMQTT_BUILD_DIR" \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    "-DCMAKE_PREFIX_PATH=$RPI_QT_ROOT;/usr" \
    -DQT_HOST_PATH=/usr \
    -DQt6HostInfo_DIR=/usr/lib/x86_64-linux-gnu/cmake/Qt6HostInfo \
    "-DCMAKE_INSTALL_PREFIX=$RPI_QTMQTT_INSTALL" \
    -DQT_NO_PACKAGE_VERSION_CHECK=TRUE \
    -DQT_BUILD_EXAMPLES=OFF \
    -DQT_BUILD_TESTS=OFF \
    -DQT_BUILD_DOCS=OFF \
    "${TOOLCHAIN_ARGS[@]}"
cmake --build "$RPI_QTMQTT_BUILD_DIR" --parallel
cmake --install "$RPI_QTMQTT_BUILD_DIR"

cmake -S "$ROOT_DIR" -B "$RPI_BUILD_DIR" \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    "-DCMAKE_PREFIX_PATH=$RPI_QT_ROOT;$RPI_QTMQTT_INSTALL" \
    "-DOSH_QTMQTT_ROOT=$RPI_QTMQTT_INSTALL" \
    "${TOOLCHAIN_ARGS[@]}"
cmake --build "$RPI_BUILD_DIR" --target OSHServices --parallel

echo "OSHServices cross-build completed: $RPI_BUILD_DIR"
