#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/cross_compile_wiringpi.sh <sysroot>

Build WiringPi into <sysroot>/usr
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -ne 1 ]]; then
    echo "A sysroot is required." >&2
    usage >&2
    exit 2
fi

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
RPI_SYSROOT="$1"
RPI_CROSS_PREFIX="aarch64-linux-gnu-"
CROSS_C_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}gcc"
CROSS_CXX_COMPILER="/usr/bin/${RPI_CROSS_PREFIX}g++"

TOOLCHAIN_ARGS=(
    "-DCMAKE_SYSTEM_NAME=Linux"
    "-DCMAKE_SYSTEM_PROCESSOR=aarch64"
    "-DCMAKE_SYSROOT=$RPI_SYSROOT"
    "-DCMAKE_C_COMPILER=$CROSS_C_COMPILER"
    "-DCMAKE_CXX_COMPILER=$CROSS_CXX_COMPILER"
    "-DCMAKE_C_FLAGS=--sysroot=$RPI_SYSROOT"
    "-DCMAKE_CXX_FLAGS=--sysroot=$RPI_SYSROOT"
    "-DCMAKE_EXE_LINKER_FLAGS=--sysroot=$RPI_SYSROOT"
    "-DCMAKE_SHARED_LINKER_FLAGS=--sysroot=$RPI_SYSROOT"
    "-DCMAKE_MAKE_PROGRAM=/usr/bin/gmake"
    "-DCMAKE_FIND_ROOT_PATH=$RPI_SYSROOT"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER"
    "-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY"
    "-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY"
)

# Export flags derived from the toolchain args for Makefile consumers
SYSROOT_FLAG="--sysroot=$RPI_SYSROOT"
export CFLAGS="$SYSROOT_FLAG"
export CXXFLAGS="$SYSROOT_FLAG"
export LDFLAGS="$SYSROOT_FLAG -L$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -L$RPI_SYSROOT/lib/aarch64-linux-gnu -L$RPI_SYSROOT/usr/lib -L$RPI_SYSROOT/lib"

# Also extract any explicit flags from TOOLCHAIN_ARGS (e.g. -DCMAKE_C_FLAGS)
for arg in "${TOOLCHAIN_ARGS[@]}"; do
    case "$arg" in
        -DCMAKE_C_FLAGS=*)
            CFLAGS="$CFLAGS ${arg#*=}"
            ;;
        -DCMAKE_CXX_FLAGS=*)
            CXXFLAGS="$CXXFLAGS ${arg#*=}"
            ;;
        -DCMAKE_EXE_LINKER_FLAGS=*|-DCMAKE_SHARED_LINKER_FLAGS=*)
            LDFLAGS="$LDFLAGS ${arg#*=}"
            ;;
    esac
done
export CFLAGS CXXFLAGS LDFLAGS

if [[ ! -e "$RPI_SYSROOT" ]]; then
    echo "Required path does not exist: $RPI_SYSROOT" >&2
    exit 3
fi
if [[ ! -x "$CROSS_C_COMPILER" ]]; then
    echo "Required cross-compiler not found or not executable: $CROSS_C_COMPILER" >&2
    exit 3
fi

# Create a temporary compiler wrapper so we don't modify source files on disk
BUILD_WRAPPER="$(mktemp /tmp/wiringpi_cc_wrapper.XXXXXX.sh)"
trap 'rm -f "$BUILD_WRAPPER"' EXIT

cat << EOF > "$BUILD_WRAPPER"
#!/usr/bin/env bash
args=("\$@")
has_wiringpi=0
for arg in "\${args[@]}"; do
    if [[ "\$arg" == *"wiringPi.c" ]]; then
        has_wiringpi=1
        break
    fi
done

if [[ \$has_wiringpi -eq 1 ]]; then
    new_args=()
    target_file=""
    for arg in "\${args[@]}"; do
        if [[ "\$arg" == *"wiringPi.c" ]]; then
            target_file="\$arg"
            new_args+=("-x" "c" "-")
        else
            new_args+=("\$arg")
        fi
    done
    sed 's/const unsigned int RP1_STATUS_LEVEL_LOW/enum { RP1_STATUS_LEVEL_LOW = 0x00400000 }; \/\/ const unsigned int RP1_STATUS_LEVEL_LOW/; s/const unsigned int RP1_STATUS_LEVEL_HIGH/enum { RP1_STATUS_LEVEL_HIGH = 0x00800000 }; \/\/ const unsigned int RP1_STATUS_LEVEL_HIGH/' "\$target_file" | exec "$CROSS_C_COMPILER" "\${new_args[@]}"
else
    exec "$CROSS_C_COMPILER" "\$@"
fi
EOF
chmod +x "$BUILD_WRAPPER"

LINK_FLAGS="-B$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -B$RPI_SYSROOT/lib/aarch64-linux-gnu -L$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -L$RPI_SYSROOT/lib/aarch64-linux-gnu -Wl,-rpath-link,$RPI_SYSROOT/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$RPI_SYSROOT/lib/aarch64-linux-gnu"

echo "Building WiringPi into $RPI_SYSROOT/usr/local"
make -C "$ROOT_DIR/WiringPi/wiringPi" clean >/dev/null || true
make -C "$ROOT_DIR/WiringPi/wiringPi" \
    CC="$BUILD_WRAPPER --sysroot=$RPI_SYSROOT $LINK_FLAGS" \
    EXTRA_CFLAGS="$CFLAGS" \
    CXXFLAGS="$CXXFLAGS" \
    LDFLAGS="$LDFLAGS $LINK_FLAGS" \
    LDCONFIG=true \
    DESTDIR="$RPI_SYSROOT/usr" \
    PREFIX=/local
sudo make -C "$ROOT_DIR/WiringPi/wiringPi" install \
    CC="$BUILD_WRAPPER --sysroot=$RPI_SYSROOT $LINK_FLAGS" \
    EXTRA_CFLAGS="$CFLAGS" \
    CXXFLAGS="$CXXFLAGS" \
    LDFLAGS="$LDFLAGS $LINK_FLAGS" \
    LDCONFIG=true \
    DESTDIR="$RPI_SYSROOT/usr" \
    PREFIX=/local
    
echo "WiringPi cross-build completed"
