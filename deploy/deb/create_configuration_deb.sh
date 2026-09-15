#!/bin/bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./create_configuration_deb.sh <rpi_conf_dir> <instance-name> <deb-name> <deb-version> <output-deb-dir>

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
    echo "An rpi conf dir, instance name, deb name, version, and output deb dir are required." >&2
    usage >&2
    exit 2
fi

pushd . > /dev/null

INSTANCE_NAME="$2"
DEB_NAME="$3"
DEB_VERSION="$4"
RPI_CONF_DIR="$1/${DEB_NAME}"
OUTPUT_DEB_DIR="$5"

DEB_FULL_NAME="${INSTANCE_NAME}-${DEB_NAME}-${DEB_VERSION}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PACKAGE_ROOT="$OUTPUT_DEB_DIR/${INSTANCE_NAME}/${DEB_FULL_NAME}"
TARGET_INSTANCE_DIR="/etc/osh/instances/${DEB_NAME}"

if [[ ! -e "$RPI_CONF_DIR" ]]; then
    echo "Required path does not exist: $RPI_CONF_DIR" >&2
    exit 3
fi

HAS_UDEV_RULES=false
if [ -d "$RPI_CONF_DIR/etc/udev" ]; then
    echo "Found udev directory in $RPI_CONF_DIR/etc/udev"
    HAS_UDEV_RULES=true
fi


sudo rm -rf "${PACKAGE_ROOT}"

mkdir -p "$PACKAGE_ROOT"
cd "$PACKAGE_ROOT"

mkdir -p DEBIAN
cat <<EOF > DEBIAN/control
Package: osh-${INSTANCE_NAME,,}-${DEB_NAME,,}
Version: ${DEB_VERSION}
Section: base
Priority: optional
Architecture: arm64
Maintainer: ${DEB_MAINTAINER:-ninjachris81 <${DEB_EMAIL:-cbstar@web.de}>}
Description: ${DEB_NAME} Configuration package
EOF

cat <<EOF > DEBIAN/postinst
#!/bin/bash
set -e
if [ "\$1" = "configure" ]; then
    echo "Enabling and starting ${DEB_NAME}.service..."
    systemctl daemon-reload
    systemctl enable "${DEB_NAME}.service"
    systemctl start "${DEB_NAME}.service"

    HAS_UDEV_RULES=$HAS_UDEV_RULES
    if [ \$HAS_UDEV_RULES = true ]; then
        udevadm control --reload-rules
        udevadm trigger
    fi

    if [ -f "${TARGET_INSTANCE_DIR}/configure.sh" ]; then
        echo "Running configure.sh for ${DEB_NAME} instance..."
        bash "${TARGET_INSTANCE_DIR}/configure.sh"
    fi
fi
exit 0
EOF
chmod 755 DEBIAN/postinst

cat <<EOF > DEBIAN/prerm
#!/bin/bash
set -e
if [ "\$1" = "remove" ] || [ "\$1" = "purge" ]; then
    echo "Stopping and disabling ${DEB_NAME}.service..."
    systemctl stop "${DEB_NAME}.service"
    systemctl disable "${DEB_NAME}.service"
fi
exit 0
EOF
chmod 755 DEBIAN/prerm

# copy rootfs
cp -R "$RPI_CONF_DIR/." "${PACKAGE_ROOT}"

sudo chown -R root:root "$PACKAGE_ROOT"

popd > /dev/null