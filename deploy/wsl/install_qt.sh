#!/bin/bash

set -e

QT_VERSION="6.8.2"
INSTALL_PREFIX="$HOME/qt-${QT_VERSION}"
SRC_DIR="$HOME/qt-src"
BUILD_DIR="$HOME/qt-build"
CLEAN_SOURCE=false

while [[ $# -gt 0 ]]; do
    case "$1" in
        --clean)
            CLEAN_SOURCE=true
            shift
            ;;
        *)
            echo "Unbekannter Parameter: $1"
            exit 1
            ;;
    esac
done

sudo apt-get update
sudo apt-get install -y build-essential libgl1-mesa-dev libglu1-mesa-dev \
libxcb-xinerama0-dev libxcb1-dev libx11-xcb-dev libxcb-keysyms1-dev \
libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev \
libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev \
libxcb-util-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev \
cmake ninja-build git python3 libasound2-dev libpulse-dev libswresample-dev \
linux-headers-generic libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libpq-dev \
libavcodec-dev libavformat-dev libswscale-dev libavutil-dev

if [ "$CLEAN_SOURCE" = true ] || { [ -d "$SRC_DIR" ] && [ ! -d "$SRC_DIR/.git" ]; }; then
    echo "Cleaning Qt source code..."
    rm -rf "$SRC_DIR"
fi

if [ ! -d "$SRC_DIR" ]; then
    echo "Cloning Qt source code..."
    git clone --branch ${QT_VERSION} https://code.qt.io/qt/qt5.git "$SRC_DIR"
else
    echo "Using existing Qt source code..."
fi

cd "$SRC_DIR"

git submodule update --init --recursive \
  qtbase \
  qtshadertools \
  qtdeclarative \
  qtmultimedia \
  qtserialbus \
  qtserialport

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

"$SRC_DIR/configure" \
    -prefix "$INSTALL_PREFIX" \
    -release \
    -opensource \
    -confirm-license \
    -submodules qtbase,qtshadertools,qtdeclarative,qtmultimedia,qtserialbus,qtserialport \
    -nomake examples \
    -nomake tests \
    -sql-psql \
    -- -G Ninja -DCMAKE_CXX_FLAGS="-include cstdint"

cmake --build . --parallel
cmake --install .

if [ -f "$INSTALL_PREFIX/bin/qmake" ]; then
    "$INSTALL_PREFIX/bin/qmake" --version
else
    exit 1
fi
