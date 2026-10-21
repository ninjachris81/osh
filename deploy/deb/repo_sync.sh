#!/usr/bin/env bash
set -euo pipefail

source instance_config.sh

for service in "${!SERVICE_EXECUTABLES[@]}"; do
    version="${SERVICE_EXECUTABLES[$service]}"
    ./repo_add.sh "Osh-$service-$version.deb"
done

for service in "${!SERVICE_CONFIGURATIONS[@]}"; do
    version="${SERVICE_CONFIGURATIONS[$service]}"
    ./repo_add.sh "Osh-$INSTANCE_NAME-$service-$version.deb"
done

./repo_add.sh "Osh-Qt6-6.8.2.deb"
./repo_add.sh "Osh-Common-1.0.deb"
./repo_add.sh "Osh-${INSTANCE_NAME}-Common-1.0.deb"

HAS_WIRINGPI=false
for dependencies in "${SERVICE_DEPENDENCIES[@]}"; do
    if [[ "$dependencies" =~ (^|,)[[:space:]]*osh-wiringpi[[:space:]]*(,|$) ]]; then
        HAS_WIRINGPI=true
        break
    fi
done

if [[ "$HAS_WIRINGPI" == true ]]; then
    ./repo_add.sh "Osh-WiringPi-1.0.deb"
fi

HAS_PJSUPPORT=false
for dependencies in "${SERVICE_DEPENDENCIES[@]}"; do
    if [[ "$dependencies" =~ (^|,)[[:space:]]*osh-pjsupport[[:space:]]*(,|$) ]]; then
        HAS_PJSUPPORT=true
        break
    fi
done

if [[ "$HAS_PJSUPPORT" == true ]]; then
    ./repo_add.sh "Osh-PJSupport-1.0.deb"
fi
