#!/bin/bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/deb/create_executable_deb.sh <rpi_bin_dir> <instance-name> <deb-name> <deb-version> <output-deb-dir>

Optional variables:
    DEB_EMAIL            Email of the maintainer (default: cbstar@web.de)
    DEB_MAINTAINER      Maintainer of the package (default: ninjachris81 <cbstar@web.de>)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -lt 5 || $# -gt 5 ]]; then
    echo "An rpi bin dir, instance name, deb name, version, and output deb dir are required." >&2
    usage >&2
    exit 2
fi

pushd . > /dev/null

RPI_BIN_DIR="$1"
INSTANCE_NAME="$2"
DEB_NAME="$3"
DEB_VERSION="$4"
OUTPUT_DEB_DIR="$5"

DEB_FULL_NAME="${DEB_NAME}-${DEB_VERSION}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PACKAGE_ROOT="$OUTPUT_DEB_DIR/${INSTANCE_NAME}/${DEB_FULL_NAME}"

if [[ ! -e "$RPI_BIN_DIR" ]]; then
    echo "Required path does not exist: $RPI_BIN_DIR" >&2
    exit 3
fi

sudo rm -rf "${PACKAGE_ROOT}"

mkdir -p "$PACKAGE_ROOT"
cd "$PACKAGE_ROOT"

mkdir -p DEBIAN
cat <<EOF > DEBIAN/control
Package: ${DEB_NAME}
Version: ${DEB_VERSION}
Section: base
Priority: optional
Architecture: amd64
Maintainer: ${DEB_MAINTAINER:-ninjachris81 <${DEB_EMAIL:-cbstar@web.de}>}
Description: ${DEB_NAME} package
EOF

# copy executable
SERVICE_DIR="$PACKAGE_ROOT/etc/osh/${DEB_NAME}"
mkdir -p "${SERVICE_DIR}"
cp "$RPI_BIN_DIR/${DEB_NAME}/${DEB_NAME}" "${SERVICE_DIR}/${DEB_NAME}"
chmod +x "${SERVICE_DIR}/${DEB_NAME}"

sudo chown -R root:root "$PACKAGE_ROOT"

popd > /dev/null