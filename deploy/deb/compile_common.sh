#!/bin/bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./compile_common.sh <instance_name>

Optional variables:
    DEB_EMAIL            Email of the maintainer (default: cbstar@web.de)
    DEB_MAINTAINER      Maintainer of the package (default: ninjachris81 <cbstar@web.de>)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi


if [[ $# -lt 1 || $# -gt 1 ]]; then
    echo "An instance name is required." >&2
    usage >&2
    exit 2
fi

pushd . > /dev/null
INSTANCE_NAME="$1"
DEB_NAME="Osh-Common"
DEB_VERSION="1.0"

DEB_FULL_NAME="${DEB_NAME}-${DEB_VERSION}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUTPUT_DEB_DIR="$ROOT_DIR/../../build-deb"
PACKAGE_ROOT="$OUTPUT_DEB_DIR/${INSTANCE_NAME}/${DEB_FULL_NAME}"
RPI_CONF_DIR="$ROOT_DIR/../rpi/instances/Common"

if [[ ! -e "$RPI_CONF_DIR" ]]; then
    echo "Required path does not exist: $RPI_CONF_DIR" >&2
    exit 3
fi

sudo rm -rf "${PACKAGE_ROOT}"

mkdir -p "$PACKAGE_ROOT"
cd "$PACKAGE_ROOT"

mkdir -p DEBIAN
cat <<EOF > DEBIAN/control
Package: ${DEB_NAME,,}
Version: ${DEB_VERSION}
Section: base
Priority: optional
Architecture: arm64
Maintainer: ${DEB_MAINTAINER:-ninjachris81 <${DEB_EMAIL:-cbstar@web.de}>}
Description: ${DEB_NAME} package
EOF

# copy rootfs
cp -R "$RPI_CONF_DIR/." "${PACKAGE_ROOT}"

# copy apt_update_all.sh script
mkdir -p "$PACKAGE_ROOT/etc/osh/scripts"
cp "$ROOT_DIR/$INSTANCE_NAME/apt_update_all.sh" "$PACKAGE_ROOT/etc/osh/scripts"
cp "$ROOT_DIR/$INSTANCE_NAME/services.sh" "$PACKAGE_ROOT/etc/osh/scripts"

sudo chown -R root:root "$PACKAGE_ROOT"

popd > /dev/null

./build_deb.sh "$INSTANCE_NAME" "$DEB_NAME" "$DEB_VERSION" "$OUTPUT_DEB_DIR"