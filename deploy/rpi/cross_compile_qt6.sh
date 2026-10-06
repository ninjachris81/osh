#!/usr/bin/env bash
set -euo pipefail

RPI_SYSROOT="$1"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$SCRIPT_DIR/../.."
RPI_QT_SRC_DIR="${RPI_QT_SRC_DIR:-$ROOT_DIR/qt6}"
RPI_QT_ROOT="$RPI_SYSROOT/usr/local/qt6"
RPI_INSTALL_PATH="$RPI_QT_ROOT"
RPI_QT_HOST_ROOT="${RPI_QT_HOST_ROOT:-$HOME/qt-6.8.2}"
RPI_QT_MKSPECS_DIR="${RPI_QT_MKSPECS_DIR:-$RPI_QT_SRC_DIR/qtbase/mkspecs}"
RPI_QT_BUILD_DIR="${RPI_QT_BUILD_DIR:-$ROOT_DIR/qt-build-rpi2}"
RPI_BUILD_JOBS="${RPI_BUILD_JOBS:-4}"

rm -rf "$RPI_QT_BUILD_DIR"
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
popd >/dev/null

# qtmqtt
./cross_compile_qtmqtt.sh "$RPI_SYSROOT"