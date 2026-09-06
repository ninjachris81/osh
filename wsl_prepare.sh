sudo apt-get update
sudo apt-get install -y \
  qt6-base-dev \
  qt6-base-private-dev \
  qt6-declarative-dev \
  qt6-multimedia-dev \
  qt6-serialbus-dev \
  qt6-serialport-dev

git submodule update --init --recursive qtmqtt WiringPi

make -C WiringPi/wiringPi
sudo make -C WiringPi/wiringPi install

cmake -S qtmqtt -B qtmqtt-build \
  -G "Unix Makefiles" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH=/usr \
  -DCMAKE_INSTALL_PREFIX="$PWD/qtmqtt-install"

cmake --build qtmqtt-build --parallel
cmake --install qtmqtt-build

cmake -S . -B build \
  -G "Unix Makefiles" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_C_COMPILER=/usr/bin/gcc \
  -DCMAKE_CXX_COMPILER=/usr/bin/g++