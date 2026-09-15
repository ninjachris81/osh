#!/usr/bin/env bash
set -euo pipefail

INSTANCE_NAME="CoreServer"

source services.sh

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