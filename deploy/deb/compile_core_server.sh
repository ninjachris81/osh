#!/usr/bin/env bash
set -euo pipefail

INSTANCE_NAME="CoreServer"

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RPI_BIN_DIR="$ROOT_DIR/../../build-rpi"
OUTPUT_DEB_DIR="$ROOT_DIR/../../build-deb"
RPI_CONF_DIR="$ROOT_DIR/../rpi/instances/${INSTANCE_NAME}/configs"

if [[ ! -e "$RPI_CONF_DIR" ]]; then
    echo "Required path does not exist: $RPI_CONF_DIR" >&2
    exit 3
fi

if [[ ! -e "$RPI_BIN_DIR" ]]; then
    echo "Required path does not exist: $RPI_BIN_DIR" >&2
    exit 3
fi

sudo rm -rf "$OUTPUT_DEB_DIR/${INSTANCE_NAME}"

# Define executables and their versions in an associative array
declare -A SERVICE_EXECUTABLES=(
    ["AudioService"]="1.0"
    ["CoreService"]="1.0"
    ["DoorCameraService"]="1.0"
    ["GPIOInputService"]="1.0"
    ["RS485EnergyMeterService"]="1.0"
    ["RS485RelayService"]="1.0"
    ["ShutterService"]="1.0"
    ["WBB12Service"]="1.0"
)

# Define service dependencies
declare -A SERVICE_DEPENDENCIES=(
    ["AudioService"]="mpg123"
    ["CoreService"]="postgresql, mosquitto"
    ["DoorCameraService"]="livemedia-utils"
    ["GPIOInputService"]="i2c-tools, libi2c-dev"
    ["RS485EnergyMeterService"]=""
    ["RS485RelayService"]=""
    ["ShutterService"]=""
    ["WBB12Service"]=""
)

# Define service scripts
declare -A SERVICE_SCRIPTS=(
    ["AudioService"]=""
    ["CoreService"]=""
    ["DoorCameraService"]=""
    ["GPIOInputService"]="raspi-config nonint do_i2c 0"
    ["RS485EnergyMeterService"]=""
    ["RS485RelayService"]=""
    ["ShutterService"]=""
    ["WBB12Service"]=""
)

# Define service libraries
declare -A SERVICE_LIBRARIES=(
    ["AudioService"]="Core AudioController QMqttCommunicationManager"
    ["CoreService"]="Core CoreServer QMqttCommunicationManager"
    ["DoorCameraService"]="Core DoorCameraController QMqttCommunicationManager"
    ["GPIOInputService"]="Core GPIOInputController QMqttCommunicationManager"
    ["RS485EnergyMeterService"]="Core CoreSerial RS485EnergyMeterController QMqttCommunicationManager"
    ["RS485RelayService"]="Core CoreSerial RS485RelayController QMqttCommunicationManager"
    ["ShutterService"]="Core ShutterController QMqttCommunicationManager"
    ["WBB12Service"]="Core CoreSerial WBB12Controller QMqttCommunicationManager"
)

# Define services and their versions in an associative array
declare -A SERVICE_CONFIGURATIONS=(
    ["AudioService"]="1.0"
    ["CoreService"]="1.0"
    ["DoorCameraService"]="1.0"
    ["GPIOInputService"]="1.0"
    ["RS485EnergyMeterService"]="1.0"
    ["RS485RelayService-lights"]="1.0"
    ["RS485RelayService-shutters"]="1.0"
    ["ShutterService-eg"]="1.0"
    ["ShutterService-og"]="1.0"
    ["WBB12Service"]="1.0"
)

if [ "${#SERVICE_EXECUTABLES[@]}" -ne "${#SERVICE_DEPENDENCIES[@]}" ]; then
    echo "Mismatch between number of service executables and their dependencies" >&2
    exit 4
fi

if [ "${#SERVICE_EXECUTABLES[@]}" -ne "${#SERVICE_SCRIPTS[@]}" ]; then
    echo "Mismatch between number of service executables and their scripts" >&2
    exit 4
fi

if [ "${#SERVICE_EXECUTABLES[@]}" -ne "${#SERVICE_LIBRARIES[@]}" ]; then
    echo "Mismatch between number of service executables and their libraries" >&2
    exit 4
fi

# Create Executable DEB files
for service in "${!SERVICE_EXECUTABLES[@]}"; do
    version="${SERVICE_EXECUTABLES[$service]}"
    echo "Creating executable DEB for $service version $version"
    dependencies="${SERVICE_DEPENDENCIES[$service]}"
    postinst_script="${SERVICE_SCRIPTS[$service]}"
    libraries="${SERVICE_LIBRARIES[$service]}"
    ./create_executable_deb.sh "$RPI_BIN_DIR" "$INSTANCE_NAME" "$service" "$version" "$dependencies" "$postinst_script" "$libraries" "$OUTPUT_DEB_DIR"
done

# Build DEB files
for service in "${!SERVICE_EXECUTABLES[@]}"; do
    version="${SERVICE_EXECUTABLES[$service]}"
    ./build_deb.sh "$INSTANCE_NAME" "$service" "$version" "$OUTPUT_DEB_DIR"
done

# Create Configuration DEB files
for service in "${!SERVICE_CONFIGURATIONS[@]}"; do
    version="${SERVICE_CONFIGURATIONS[$service]}"
    echo "Creating configuration DEB for $service version $version"
    ./create_configuration_deb.sh "$RPI_CONF_DIR" "$INSTANCE_NAME" "$service" "$version" "$OUTPUT_DEB_DIR"
done

# Build DEB files
for service in "${!SERVICE_CONFIGURATIONS[@]}"; do
    version="${SERVICE_CONFIGURATIONS[$service]}"
    FILENAME_PREFIX="${INSTANCE_NAME}-" ./build_deb.sh "$INSTANCE_NAME" "$service" "$version" "$OUTPUT_DEB_DIR"
done

./compile_common.sh "$INSTANCE_NAME"
./compile_qt6.sh "$INSTANCE_NAME"