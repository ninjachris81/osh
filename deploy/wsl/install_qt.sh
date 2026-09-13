#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

QT_VERSION="6.8.2"
INSTALL_PREFIX="$HOME/qt-${QT_VERSION}"
SRC_DIR="$ROOT_DIR/qt6"
BUILD_DIR="$ROOT_DIR/qt-build"
BUILD_JOBS="${BUILD_JOBS:-3}"

cd "$ROOT_DIR"

sudo apt-get update
sudo apt-get install -y build-essential libgl1-mesa-dev libglu1-mesa-dev \
libxcb-xinerama0-dev libxcb1-dev libx11-xcb-dev libxcb-keysyms1-dev \
libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev \
libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev \
libxcb-util-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev \
cmake ninja-build git python3 libasound2-dev libpulse-dev libswresample-dev \
linux-headers-generic libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libpq-dev \
libssl-dev openssl pkg-config libxext-dev

cd "$ROOT_DIR"

# skip recursive update for qt6 as we will handle it separately
git submodule update --init qt6

cd "$SRC_DIR"

git submodule update --init --recursive \
  qtbase \
  qtshadertools \
  qtmultimedia \
  qtserialbus \
  qtserialport

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

"$SRC_DIR/configure" \
    -prefix "$INSTALL_PREFIX" \
    -release \
    -opensource \
    -confirm-license \
    -submodules qtbase,qtshadertools,qtmultimedia,qtserialbus,qtserialport \
    -nomake examples \
    -nomake tests \
    -sql-psql \
    -openssl-linked \
    -no-feature-ffmpeg \
    -- -G Ninja -DCMAKE_CXX_FLAGS="-include cstdint"

cmake --build . --parallel "$BUILD_JOBS"
cmake --install .

if [ -f "$INSTALL_PREFIX/bin/qmake" ]; then
    "$INSTALL_PREFIX/bin/qmake" --version
else
    exit 1
fi


cd "$ROOT_DIR"

# Build and install qtmqtt
git submodule update --init --recursive qtmqtt

rm -rf qtmqtt-build qtmqtt-install

cmake -S qtmqtt -B qtmqtt-build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="$INSTALL_PREFIX" \
  -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"

cmake --build qtmqtt-build --parallel
cmake --install qtmqtt-build

cmake -S . -B build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_C_COMPILER=/usr/bin/gcc \
  -DCMAKE_CXX_COMPILER=/usr/bin/g++ \
  -DCMAKE_PREFIX_PATH="$INSTALL_PREFIX" \
  -DQt6Mqtt_DIR="$INSTALL_PREFIX/lib/cmake/Qt6Mqtt"