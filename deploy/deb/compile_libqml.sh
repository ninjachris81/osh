#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/deb/compile_libqml.sh <instance_name> [architecture]

Build the libsml1 Debian package for the requested architecture (default: arm64).
The resulting package is written to build-deb/.
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -gt 1 ]]; then
    echo "At most one target architecture may be specified." >&2
    usage >&2
    exit 2
fi

INSTANCE_NAME="$1"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
LIBSML_DIR="$ROOT_DIR/libsml"
OUTPUT_DIR="$ROOT_DIR/build-deb/$INSTANCE_NAME"
TARGET_ARCH="${2:-arm64}"
BUILD_ARCH="$(dpkg --print-architecture)"
if [[ "$TARGET_ARCH" == "arm64" ]]; then
    HOST_GNU_TYPE="aarch64-linux-gnu"
else
    HOST_GNU_TYPE="$(dpkg-architecture -a"$TARGET_ARCH" -qDEB_HOST_GNU_TYPE)"
fi

if [[ ! -f "$LIBSML_DIR/debian/control" ]]; then
    echo "Debian packaging metadata not found in $LIBSML_DIR/debian" >&2
    exit 3
fi

if [[ "$TARGET_ARCH" != "$BUILD_ARCH" ]]; then
    sudo dpkg --add-architecture "$TARGET_ARCH"
fi
sudo apt update
if [[ "$TARGET_ARCH" == "$BUILD_ARCH" ]]; then
    sudo apt install -y debhelper uuid-dev dh-exec
else
    sudo apt install -y debhelper uuid-dev dh-exec "uuid-dev:$TARGET_ARCH"
fi

if [[ "$TARGET_ARCH" == "$BUILD_ARCH" ]]; then
    CROSS_CC="${CC:-gcc}"
    CROSS_LD="${LD:-ld}"
    CROSS_AR="${AR:-ar}"
else
    CROSS_CC="${CC:-${HOST_GNU_TYPE}-gcc}"
    CROSS_LD="${LD:-${HOST_GNU_TYPE}-ld}"
    CROSS_AR="${AR:-${HOST_GNU_TYPE}-ar}"
fi

for tool in dpkg-buildpackage dpkg-deb "$CROSS_CC" "$CROSS_LD" "$CROSS_AR"; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "Required build tool not found: $tool" >&2
        exit 3
    fi
done

BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/compile-libsml.XXXXXX")"
trap 'rm -rf "$BUILD_DIR"' EXIT
cp -a "$LIBSML_DIR" "$BUILD_DIR/libsml"
cat >> "$BUILD_DIR/libsml/debian/rules" <<'EOF'

override_dh_auto_build:
	$(MAKE) -C sml
EOF

echo "Building libsml1 for $TARGET_ARCH"
(
    cd "$BUILD_DIR/libsml"
    CC="$CROSS_CC" LD="$CROSS_LD" AR="$CROSS_AR" \
        dpkg-buildpackage --build=any --host-arch="$TARGET_ARCH" --unsigned-source --unsigned-changes
)

shopt -s nullglob
PACKAGE_FILES=("$BUILD_DIR"/libsml1_*.deb)
if [[ ${#PACKAGE_FILES[@]} -ne 1 ]]; then
    echo "Expected one libsml1 package from the build, found ${#PACKAGE_FILES[@]}." >&2
    exit 4
fi

mkdir -p "$OUTPUT_DIR"
PACKAGE_PATH="${PACKAGE_FILES[0]}"
PACKAGE_ARCH="$(dpkg-deb -f "$PACKAGE_PATH" Architecture)"
if [[ "$PACKAGE_ARCH" != "$TARGET_ARCH" ]]; then
    echo "Built package architecture $PACKAGE_ARCH does not match requested $TARGET_ARCH." >&2
    exit 4
fi

cp -f "$PACKAGE_PATH" "$OUTPUT_DIR/"
echo "Created $OUTPUT_DIR/$(basename "$PACKAGE_PATH")"
