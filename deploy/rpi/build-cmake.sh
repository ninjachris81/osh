#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/build-cmake.sh <target>

Targets:
    AudioService CoreService CoreUI KMTronicRelayService RS232InputService
    GPIOInputService ShutterService WBB12Service OBISService RS485RelayService
    RS485EnergyMeterService DoorAudioService DoorUnlockService DoorCameraService
    GPIOWaterMeterService

Optional variables:
    OSH_BUILD_DIR       Main build directory (default: build-cmake)
    QTMQTT_BUILD_DIR    qtmqtt build directory (default: qtmqtt-build-cmake)
    QTMQTT_INSTALL_DIR  qtmqtt install directory (default: qtmqtt-install)
    CMAKE_GENERATOR     CMake generator (default: Ninja)
    CMAKE_BUILD_TYPE    Build type (default: Release)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -ne 1 ]]; then
    usage >&2
    exit 2
fi

BUILD_TARGET="$1"
case "$BUILD_TARGET" in
    AudioService|CoreService|CoreUI|KMTronicRelayService|RS232InputService|GPIOInputService|ShutterService|WBB12Service|OBISService|RS485RelayService|RS485EnergyMeterService|DoorAudioService|DoorUnlockService|DoorCameraService|GPIOWaterMeterService)
        ;;
    *)
        echo "Invalid build target: $BUILD_TARGET" >&2
        usage >&2
        exit 2
        ;;
esac

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
OSH_BUILD_DIR="${OSH_BUILD_DIR:-$ROOT_DIR/build-cmake}"
QTMQTT_BUILD_DIR="${QTMQTT_BUILD_DIR:-$ROOT_DIR/qtmqtt-build-cmake}"
QTMQTT_INSTALL_DIR="${QTMQTT_INSTALL_DIR:-$ROOT_DIR/qtmqtt-install}"
CMAKE_GENERATOR="${CMAKE_GENERATOR:-Ninja}"
CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Release}"

RPI_MODEL="$(tr -d '\0' </proc/device-tree/model 2>/dev/null || true)"
if [[ "$RPI_MODEL" == *Zero* ]]; then
    MAKE_CORE_COUNT=1
else
    MAKE_CORE_COUNT=4
fi

cmake_prefix_args=()
if [[ -n "${OSH_QT_ROOT:-}" ]]; then
    cmake_prefix_args+=("-DCMAKE_PREFIX_PATH=$OSH_QT_ROOT")
fi

build_qtmqtt() {
    echo "Building QtMqtt in $QTMQTT_BUILD_DIR"
    cmake -S "$ROOT_DIR/qtmqtt" -B "$QTMQTT_BUILD_DIR" \
        -G "$CMAKE_GENERATOR" \
        -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" \
        "${cmake_prefix_args[@]}" \
        -DCMAKE_INSTALL_PREFIX="$QTMQTT_INSTALL_DIR" \
        -DQT_BUILD_EXAMPLES=OFF \
        -DQT_BUILD_TESTS=OFF \
        -DQT_BUILD_DOCS=OFF
    cmake --build "$QTMQTT_BUILD_DIR" --parallel "$MAKE_CORE_COUNT"
    cmake --install "$QTMQTT_BUILD_DIR"
}

build_wiringpi() {
    echo "Building WiringPi in $ROOT_DIR/WiringPi"
    (cd "$ROOT_DIR/WiringPi" && ./build)
}

build_pjproject() {
    echo "Configuring PJProject in $ROOT_DIR/pjproject"
    (cd "$ROOT_DIR/pjproject" && ./configure --disable-libwebrtc --enable-shared)
    echo "Building PJProject in $ROOT_DIR/pjproject"
    make -C "$ROOT_DIR/pjproject" dep
    make -C "$ROOT_DIR/pjproject" -j"$MAKE_CORE_COUNT"
}

case "$BUILD_TARGET" in
    GPIOInputService|DoorUnlockService|GPIOWaterMeterService)
        build_wiringpi
        ;;
esac

if [[ "$BUILD_TARGET" == DoorAudioService ]]; then
    build_pjproject
fi

build_qtmqtt

echo "Configuring OSH in $OSH_BUILD_DIR"
cmake -S "$ROOT_DIR" -B "$OSH_BUILD_DIR" \
    -G "$CMAKE_GENERATOR" \
    -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    "${cmake_prefix_args[@]}" \
    -DOSH_QTMQTT_ROOT="$QTMQTT_INSTALL_DIR"

echo "Building $BUILD_TARGET"
cmake --build "$OSH_BUILD_DIR" --target "$BUILD_TARGET" --parallel "$MAKE_CORE_COUNT"

echo "CMake build completed: $BUILD_TARGET"
