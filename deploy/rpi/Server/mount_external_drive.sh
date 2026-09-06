#!/usr/bin/env bash
set -euo pipefail

DEVICE=/dev/sda1
MOUNT_POINT=/var

if [[ $EUID -ne 0 ]]; then
    echo "Run this script as root." >&2
    exit 1
fi

if [[ ! -b "$DEVICE" ]]; then
    echo "Block device not found: $DEVICE" >&2
    exit 2
fi

if findmnt --mountpoint "$MOUNT_POINT" >/dev/null 2>&1; then
    echo "$MOUNT_POINT is already mounted."
    exit 0
fi

mkdir -p "$MOUNT_POINT"
mount "$DEVICE" "$MOUNT_POINT"

echo "Mounted $DEVICE at $MOUNT_POINT"
