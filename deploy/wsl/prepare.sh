#!/bin/bash

set -e

sudo apt-get update
sudo apt-get install -y \
  gcc-aarch64-linux-gnu \
  g++-aarch64-linux-gnu
  #qt6-base-dev \
  #qt6-base-private-dev \
  #qt6-declarative-dev \
  #qt6-multimedia-dev \
  #qt6-serialbus-dev \
  #qt6-serialport-dev

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT_DIR"

git submodule update --init --recursive qtmqtt WiringPi

make -C WiringPi/wiringPi
sudo make -C WiringPi/wiringPi install

rm -rf qtmqtt-build qtmqtt-install

cmake -S qtmqtt -B qtmqtt-build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="$HOME/qt-6.8.2" \
  -DCMAKE_INSTALL_PREFIX="$PWD/qtmqtt-install"

cmake --build qtmqtt-build --parallel
cmake --install qtmqtt-build

cmake -S . -B build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_C_COMPILER=/usr/bin/gcc \
  -DCMAKE_CXX_COMPILER=/usr/bin/g++ \
  -DCMAKE_PREFIX_PATH="$HOME/qt-6.8.2;$PWD/qtmqtt-install" \
  -DOSH_QTMQTT_ROOT="$PWD/qtmqtt-install" \
  -DQt6Mqtt_DIR="$PWD/qtmqtt-install/lib/cmake/Qt6Mqtt"