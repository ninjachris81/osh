#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT_DIR"

git submodule update --init --recursive WiringPi

make -C WiringPi/wiringPi
sudo make -C WiringPi/wiringPi install