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
    ["GPIOInputService"]="1.0"
    ["RS485EnergyMeterService"]="1.0"
    ["RS485RelayService"]="1.0"
    ["ShutterService"]="1.0"
    ["WBB12Service"]="1.0"
)

# Define services and their versions in an associative array
declare -A SERVICE_CONFIGURATIONS=(
    ["AudioService"]="1.0"
    ["CoreService"]="1.0"
    ["GPIOInputService"]="1.0"
    ["RS485EnergyMeterService"]="1.0"
    ["RS485RelayService-lights"]="1.0"
    ["RS485RelayService-shutters"]="1.0"
    ["ShutterService-eg"]="1.0"
    ["ShutterService-og"]="1.0"
    ["WBB12Service"]="1.0"
)


# Create Executable DEB files
for service in "${!SERVICE_EXECUTABLES[@]}"; do
    version="${SERVICE_EXECUTABLES[$service]}"
    echo "Creating executable DEB for $service version $version"
    ./create_executable_deb.sh "$RPI_BIN_DIR" "$INSTANCE_NAME" "$service" "$version" "$OUTPUT_DEB_DIR"
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