#!/usr/bin/env bash
set -euo pipefail

source services.sh

sudo apt update

for service in "${!SERVICE_EXECUTABLES[@]}"; do
    echo "Updating executable package for $service"
    sudo apt purge -y "$service"
    sudo apt install -y "$service"
done

for service in "${!SERVICE_CONFIGURATIONS[@]}"; do
    echo "Updating configuration package for $service"
    sudo apt purge -y "$service"
    sudo apt install -y "$service"
done