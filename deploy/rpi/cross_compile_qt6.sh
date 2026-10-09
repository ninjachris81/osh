#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./cross_compile_qt6.sh [--clean] <sysroot>

This builds Qt6 into the provided sysroot and then builds & installs qtmqtt
into the cross target prefix.
EOF
}

CLEAN=false

POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)
            usage
            exit 0
            ;;
        --clean)
            CLEAN=true
            shift
            ;;
        *)
            POSITIONAL_ARGS+=("$1")
            shift
            ;;
    esac
done

if [[ ${#POSITIONAL_ARGS[@]} -gt 0 ]]; then
    set -- "${POSITIONAL_ARGS[@]}"
else
    set --
fi

RPI_SYSROOT="$1"
CMAKE_SYSROOT="$RPI_SYSROOT"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$SCRIPT_DIR/../.."
RPI_QT_SRC_DIR="${RPI_QT_SRC_DIR:-$ROOT_DIR/qt6}"
RPI_QT_ROOT="$RPI_SYSROOT/usr/local/qt6"
RPI_INSTALL_PATH="$RPI_QT_ROOT"
RPI_QT_HOST_ROOT="${RPI_QT_HOST_ROOT:-$HOME/qt-6.8.2}"
RPI_QT_MKSPECS_DIR="${RPI_QT_MKSPECS_DIR:-$RPI_QT_SRC_DIR/qtbase/mkspecs}"
RPI_QT_BUILD_DIR="${RPI_QT_BUILD_DIR:-$ROOT_DIR/qt-build-rpi}"
RPI_BUILD_JOBS="${RPI_BUILD_JOBS:-4}"

if [[ "$CLEAN" == true ]]; then
    echo "Cleaning build directory: $RPI_QT_BUILD_DIR"
    rm -rf "$RPI_QT_BUILD_DIR"
fi

mkdir -p "$RPI_QT_BUILD_DIR"
cd "$RPI_QT_BUILD_DIR"


"$RPI_QT_SRC_DIR/configure" -release  -opensource -confirm-license -nomake examples -nomake tests -sql-psql -openssl-linked -no-feature-ffmpeg \
    -submodules qtbase,qtshadertools,qtmultimedia,qtserialbus,qtserialport \
-qt-host-path "$RPI_QT_HOST_ROOT" -prefix "$RPI_INSTALL_PATH" -device linux-rasp-pi4-aarch64 \
-device-option CROSS_COMPILE=aarch64-linux-gnu- \
-- -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/xcompile_toolchain.cmake" \
  -DCMAKE_SYSROOT="$RPI_SYSROOT" \
  -DQt6HostInfo_DIR="$RPI_QT_HOST_ROOT/lib/cmake/Qt6HostInfo" \
  -DQT_MKSPECS_DIR="$RPI_QT_MKSPECS_DIR"

cmake --build . --parallel "$RPI_BUILD_JOBS"
sudo "$(command -v cmake)" --install .

# qtmqtt
./cross_compile_qtmqtt.sh "$RPI_SYSROOT"