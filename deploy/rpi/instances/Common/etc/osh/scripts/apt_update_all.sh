#!/usr/bin/env bash
set -euo pipefail

source instance_config.sh

sudo apt update

#configurations have deps to services, so not needed
#for service in "${!SERVICE_EXECUTABLES[@]}"; do
#    echo "Updating executable package for $service"
#    sudo apt purge -y "$service"
#    sudo apt install -y "$service"
#done

for service in "${!SERVICE_CONFIGURATIONS[@]}"; do
    PACKAGE_NAME="osh-${INSTANCE_NAME,,}-${service,,}"
    echo "Updating configuration package $PACKAGE_NAME for $service"
    sudo apt purge -y "$PACKAGE_NAME"
    sudo apt install -y "$PACKAGE_NAME"
done