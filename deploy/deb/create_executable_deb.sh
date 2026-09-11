#!/bin/bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./create_executable_deb.sh <rpi_bin_dir> <instance-name> <deb-name> <deb-version> <deb-dependencies> <deb-postinst-script> <deb-libraries> <output-deb-dir>

Optional variables:
    DEB_EMAIL            Email of the maintainer (default: cbstar@web.de)
    DEB_MAINTAINER      Maintainer of the package (default: ninjachris81 <cbstar@web.de>)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -lt 8 || $# -gt 8 ]]; then
    echo "An rpi bin dir, instance name, deb name, version, deb dependencies, deb postinst script, deb libraries, and output deb dir are required." >&2
    usage >&2
    exit 2
fi

pushd . > /dev/null

RPI_BIN_DIR="$1"
INSTANCE_NAME="$2"
DEB_NAME="$3"
DEB_VERSION="$4"
DEB_DEPENDENCIES="$5"
DEB_POSTINST_SCRIPT="$6"
read -r -a DEB_LIBRARIES <<< "$7"
OUTPUT_DEB_DIR="$8"

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
Package: osh-${DEB_NAME,,}
Version: ${DEB_VERSION}
Depends: ${DEB_DEPENDENCIES}
Section: base
Priority: optional
Architecture: arm64
Maintainer: ${DEB_MAINTAINER:-ninjachris81 <${DEB_EMAIL:-cbstar@web.de}>}
Description: ${DEB_NAME} package
EOF

if [ -n "$DEB_POSTINST_SCRIPT" ]; then

cat <<EOF > DEBIAN/postinst
#!/bin/bash
set -e
if [ "\$1" = "configure" ]; then
    echo "Executing post-installation script"
    ${DEB_POSTINST_SCRIPT}
fi
exit 0
EOF
chmod 755 DEBIAN/postinst

fi

# copy executable
SERVICE_DIR="$PACKAGE_ROOT/etc/osh/${DEB_NAME}"
mkdir -p "${SERVICE_DIR}"
cp "$RPI_BIN_DIR/${DEB_NAME}/${DEB_NAME}" "${SERVICE_DIR}/${DEB_NAME}"
chmod +x "${SERVICE_DIR}/${DEB_NAME}"

# copy libraries
for lib in "${DEB_LIBRARIES[@]}"; do
    echo "Copying library $lib"
    cp "$RPI_BIN_DIR/${lib}/lib${lib}.so" "${SERVICE_DIR}/"
done

sudo chown -R root:root "$PACKAGE_ROOT"

popd > /dev/null