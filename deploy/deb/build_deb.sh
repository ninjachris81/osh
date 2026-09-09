#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/deb/build_deb.sh <instance> <package> <version> <output-deb-dir>

Optional variables:
    FILENAME_PREFIX        Prefix for the generated .deb file (default: empty)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -lt 4 || $# -gt 4 ]]; then
    echo "An instance name, package name, version, and output deb dir are required." >&2
    usage >&2
    exit 2
fi

dpkg-deb --build "$4/$1/${FILENAME_PREFIX:-}$2-$3"