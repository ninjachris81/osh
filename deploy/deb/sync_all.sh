#!/usr/bin/env bash
set -euo pipefail

ALL_INSTANCES=(
    "Basement"
    "CoreServer"
    "DG"
)

for INSTANCE_NAME in "${ALL_INSTANCES[@]}"; do
    pushd "$INSTANCE_NAME" || exit 1
    ./compile.sh || exit 1
    popd || exit 1
done

echo "Syncing all instances to the target device"
for INSTANCE_NAME in "${ALL_INSTANCES[@]}"; do
    ./repo_push.sh 192.168.177.7 ${INSTANCE_NAME} || exit 1
done
