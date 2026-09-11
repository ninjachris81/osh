#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_qt6.sh <sysroot> [qt-target-root]

This builds Qt6 into the provided sysroot and then builds & installs qtmqtt
into the cross target prefix.
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
RPI_QT_BUILD_DIR="${RPI_QT_BUILD_DIR:-$ROOT_DIR/qt-build-rpi}"
RPI_BUILD_JOBS="${RPI_BUILD_JOBS:-3}"
RPI_QT_TARGET_MKSPEC="${RPI_QT_TARGET_MKSPEC:-linux-aarch64-gnu-g++}"
RPI_QT_MKSPECS_DIR="${RPI_QT_MKSPECS_DIR:-$RPI_QT_SRC_DIR/qtbase/mkspecs}"
RPI_QTMQTT_BUILD_DIR="${RPI_QTMQTT_BUILD_DIR:-$ROOT_DIR/qtmqtt-build-rpi}"
RPI_QTMQTT_INSTALL="${RPI_QTMQTT_INSTALL:-$ROOT_DIR/qtmqtt-install-rpi}"

if [[ -n "${2:-}" ]]; then
    if [[ "${2}" == "/usr" ]]; then
        RPI_QT_ROOT="$RPI_SYSROOT/usr"
    elif [[ "${2}" == /* ]]; then
        RPI_QT_ROOT="$2"
    else
        RPI_QT_ROOT="$RPI_SYSROOT/$2"
    fi
else
    RPI_QT_ROOT="$RPI_SYSROOT/usr"
fi

if [[ ! -e "$RPI_SYSROOT" ]]; then
    echo "Required path does not exist: $RPI_SYSROOT" >&2
    exit 3
fi
if [[ ! -d "$RPI_QT_SRC_DIR" || ! -x "$RPI_QT_SRC_DIR/configure" ]]; then
    echo "Qt source tree not found: $RPI_QT_SRC_DIR" >&2
    exit 3
fi
if [[ ! -d "$RPI_QT_MKSPECS_DIR" ]]; then
    echo "Qt mkspecs directory not found: $RPI_QT_MKSPECS_DIR" >&2
    exit 3
fi
if [[ ! -x "$RPI_QT_HOST_ROOT/bin/qmake" ]]; then
    echo "Host Qt install not found: $RPI_QT_HOST_ROOT" >&2
    exit 3
fi

CROSS_C_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}gcc"
CROSS_CXX_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}g++"
for compiler in "$CROSS_C_COMPILER" "$CROSS_CXX_COMPILER"; do
    if [[ ! -x "$compiler" ]]; then
        echo "Required host compiler is not executable: $compiler" >&2
        exit 3
    fi
done

QT6_CONFIG="$(find "$RPI_QT_ROOT" -path '*/cmake/Qt6/Qt6Config.cmake' -print -quit)"
if [[ -z "$QT6_CONFIG" ]]; then
    echo "Qt6Config.cmake was not found below $RPI_QT_ROOT. Building Qt 6 from source..."
    rm -rf "$RPI_QT_BUILD_DIR"
    mkdir -p "$RPI_QT_BUILD_DIR"
    pushd "$RPI_QT_BUILD_DIR" >/dev/null
    "$RPI_QT_SRC_DIR/configure" \
        -prefix "$RPI_QT_ROOT" \
        -release -opensource -confirm-license \
        -submodules qtbase,qtshadertools,qtmultimedia,qtserialbus,qtserialport \
        -nomake examples -nomake tests -sql-psql -openssl-linked -no-feature-ffmpeg \
        -- -G "Unix Makefiles" \
        -DCMAKE_C_COMPILER="$CROSS_C_COMPILER" \
        -DCMAKE_CXX_COMPILER="$CROSS_CXX_COMPILER" \
        -DCMAKE_SYSROOT="$RPI_SYSROOT" \
        -DCMAKE_FIND_ROOT_PATH="$RPI_SYSROOT" \
        -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER \
        -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
        -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
        -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=BOTH \
        -DCMAKE_PREFIX_PATH="$RPI_SYSROOT/usr;$RPI_QT_HOST_ROOT" \
        -DQT_HOST_PATH="$RPI_QT_HOST_ROOT" \
        -DQt6HostInfo_DIR="$RPI_QT_HOST_ROOT/lib/cmake/Qt6HostInfo" \
        -DQT_MKSPECS_DIR="$RPI_QT_MKSPECS_DIR" \
        -DQT_QMAKE_TARGET_MKSPEC="$RPI_QT_TARGET_MKSPEC" \
        -DCMAKE_CXX_FLAGS="-include cstdint"

    cmake --build . --parallel "$RPI_BUILD_JOBS"
    sudo "$(command -v cmake)" --install .
    popd >/dev/null
    QT6_CONFIG="$(find "$RPI_QT_ROOT" -path '*/cmake/Qt6/Qt6Config.cmake' -print -quit)"
    if [[ -z "$QT6_CONFIG" ]]; then
        echo "Qt6Config.cmake was still not found below $RPI_QT_ROOT after building Qt." >&2
        exit 4
    fi
else
    echo "Qt6Config.cmake found: $QT6_CONFIG"
fi

QT6_PLATFORM_DIR="$(dirname "$QT6_CONFIG")/platforms"
if [[ -d "$QT6_PLATFORM_DIR" ]]; then
    sudo rm -rf "$QT6_PLATFORM_DIR"
fi

QT6_MKSPECS_DIR="$RPI_QT_ROOT/lib/aarch64-linux-gnu/qt6/mkspecs"
if [[ ! -d "$QT6_MKSPECS_DIR/linux-g++" ]]; then
    sudo mkdir -p "$QT6_MKSPECS_DIR"
    sudo ln -sfn "$RPI_QT_MKSPECS_DIR/linux-g++" "$QT6_MKSPECS_DIR/linux-g++"
fi

TARGET_QT_PREFIX_PATH="$RPI_QT_ROOT;$RPI_QT_HOST_ROOT"

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

if [[ -f "$RPI_QTMQTT_BUILD_DIR/CMakeCache.txt" ]]; then
    rm -rf "$RPI_QTMQTT_BUILD_DIR"
fi

cmake -S "$ROOT_DIR/qtmqtt" -B "$RPI_QTMQTT_BUILD_DIR" \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    "-DCMAKE_PREFIX_PATH=$TARGET_QT_PREFIX_PATH" \
    -DQT_HOST_PATH="$RPI_QT_HOST_ROOT" \
    -DQt6HostInfo_DIR="$RPI_QT_HOST_ROOT/lib/cmake/Qt6HostInfo" \
    -DQT_MKSPECS_DIR="$RPI_QT_MKSPECS_DIR" \
    -DQT_QMAKE_TARGET_MKSPEC="$RPI_QT_TARGET_MKSPEC" \
    -DQT_GENERATE_SBOM=OFF \
    "-DCMAKE_INSTALL_PREFIX=$RPI_QTMQTT_INSTALL" \
    -DQT_NO_PACKAGE_VERSION_CHECK=TRUE \
    -DQT_BUILD_EXAMPLES=OFF \
    -DQT_BUILD_TESTS=OFF \
    -DQT_BUILD_DOCS=OFF \
    "${TOOLCHAIN_ARGS[@]}"
cmake --build "$RPI_QTMQTT_BUILD_DIR" --parallel "$RPI_BUILD_JOBS"
cmake --install "$RPI_QTMQTT_BUILD_DIR"

echo "Qt6 + qtmqtt cross-build completed: $RPI_QT_ROOT and $RPI_QTMQTT_INSTALL"
