#!/bin/bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./repo_add.sh <deb_file>

EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -lt 1 || $# -gt 1 ]]; then
    echo "A deb file is required." >&2
    usage >&2
    exit 2
fi

if [[ ! -f "$1" ]]; then
    echo "Error: File '$1' does not exist." >&2
    exit 1
fi

REPO_BASE_DIR="/var/www/debian-repo"
CODENAME="bookworm"

PKG_NAME=$(dpkg-deb -f "$1" Package)

echo "Removing $PKG_NAME from $CODENAME"
sudo reprepro -b "$REPO_BASE_DIR" remove "$CODENAME" "$PKG_NAME"
echo "Adding $PKG_NAME to $CODENAME"
sudo reprepro -b "$REPO_BASE_DIR" includedeb "$CODENAME" "$1"
