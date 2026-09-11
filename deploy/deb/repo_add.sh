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

REPO_BASE_DIR="/var/www/debian-repo"
CODENAME="bookworm"                        # e.g., bookworm, trixie, jammy, focal

sudo reprepro -b "$REPO_BASE_DIR" remove "$CODENAME" "$1"
sudo reprepro -b "$REPO_BASE_DIR" includedeb "$CODENAME" "$1"