#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "Root directory: $ROOT_DIR"
echo "Instance name: $INSTANCE_NAME"

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

source calculate_dependencies.sh

sudo rm -rf "$OUTPUT_DEB_DIR/${INSTANCE_NAME}"

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
    # correct filename
    mv "$OUTPUT_DEB_DIR/${INSTANCE_NAME}/${service}-${version}.deb" "$OUTPUT_DEB_DIR/${INSTANCE_NAME}/Osh-${service}-${version}.deb"
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
    # correct filename
    mv "$OUTPUT_DEB_DIR/${INSTANCE_NAME}/${INSTANCE_NAME}-${service}-${version}.deb" "$OUTPUT_DEB_DIR/${INSTANCE_NAME}/Osh-${INSTANCE_NAME}-${service}-${version}.deb"
done

./compile_common.sh "$INSTANCE_NAME"
./compile_instance_common.sh "$INSTANCE_NAME"
./compile_wiringpi.sh "$INSTANCE_NAME"
./compile_qt6.sh "$INSTANCE_NAME"