#!/usr/bin/env bash
set -euo pipefail

INSTANCE_NAME="CoreServer"

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

for service in "${!SERVICE_EXECUTABLES[@]}"; do
    version="${SERVICE_EXECUTABLES[$service]}"
    ./repo_add.sh "Osh-$service-$version.deb"
done

for service in "${!SERVICE_CONFIGURATIONS[@]}"; do
    version="${SERVICE_CONFIGURATIONS[$service]}"
    ./repo_add.sh "Osh-$INSTANCE_NAME-$service-$version.deb"
done

./repo_add.sh "Osh-Qt6-6.8.2.deb"
./repo_add.sh "Osh-WiringPi-1.0.deb"
./repo_add.sh "Osh-Common-1.0.deb"