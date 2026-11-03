#!/bin/bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./compile_pjsupport.sh <instance_name>

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
DEB_NAME="Osh-PjSupport"
DEB_VERSION="1.0"

DEB_FULL_NAME="${DEB_NAME}-${DEB_VERSION}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUTPUT_DEB_DIR=$(realpath -m "$ROOT_DIR/../../build-deb")
PACKAGE_ROOT="$OUTPUT_DEB_DIR/${INSTANCE_NAME}/${DEB_FULL_NAME}"
PJSUPPORT_ROOT="$ROOT_DIR/../../build-rpi-pjsupport"
PJSUPPORT_DIR="$(find "$PJSUPPORT_ROOT" -mindepth 1 -maxdepth 1 -type d -name 'pjproject-*' 2>/dev/null | sort | tail -n 1)"
if [[ -z "$PJSUPPORT_DIR" && -e "$PJSUPPORT_ROOT/pjsip/lib" ]]; then
    PJSUPPORT_DIR="$PJSUPPORT_ROOT"
fi
PJSUPPORT_PACKAGE_ROOT="${PACKAGE_ROOT}/usr/local/lib"

if [[ -z "$PJSUPPORT_DIR" || ! -e "$PJSUPPORT_DIR" ]]; then
    echo "Required path does not exist: $PJSUPPORT_ROOT" >&2
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

echo "Creating dir ${PJSUPPORT_PACKAGE_ROOT}"
mkdir -p "${PJSUPPORT_PACKAGE_ROOT}"
echo "📦 Copying pjlib libraries to package root from $PJSUPPORT_DIR to ${PJSUPPORT_PACKAGE_ROOT}"
cp -d "$PJSUPPORT_DIR"/pjsip/lib/libpj*.so* "${PJSUPPORT_PACKAGE_ROOT}/"
cp -d "$PJSUPPORT_DIR"/pjmedia/lib/libpj*.so* "${PJSUPPORT_PACKAGE_ROOT}/"
cp -d "$PJSUPPORT_DIR"/pjlib-util/lib/libpj*.so* "${PJSUPPORT_PACKAGE_ROOT}/"
cp -d "$PJSUPPORT_DIR"/pjnath/lib/libpj*.so* "${PJSUPPORT_PACKAGE_ROOT}/"
cp -d "$PJSUPPORT_DIR"/pjlib/lib/libpj*.so* "${PJSUPPORT_PACKAGE_ROOT}/"
cp -d "$PJSUPPORT_DIR"/third_party/lib/lib*.so* "${PJSUPPORT_PACKAGE_ROOT}/"

sudo chown -R root:root "$PACKAGE_ROOT"

popd > /dev/null

./build_deb.sh "$INSTANCE_NAME" "$DEB_NAME" "$DEB_VERSION" "$OUTPUT_DEB_DIR"