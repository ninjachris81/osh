#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/copy_sysroot.sh [--clean] <IP> <user>

Optional variables:
  RPI_SSH_PORT             SSH port (default: 22)
  RPI_SSH_KEY              SSH private key to use
  RPI_REMOTE_RSYNC_PATH    Remote rsync command (default: rsync)
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

CLEAN_SYSROOT=false
if [[ ${1:-} == "--clean" ]]; then
    CLEAN_SYSROOT=true
    shift
fi

if [[ $# -ne 2 ]]; then
    echo "Exactly an IP address and user are required." >&2
    usage >&2
    exit 2
fi

RPI_REMOTE_HOST="$1"
RPI_REMOTE_USER="$2"
RPI_SYSROOT="/opt/rpi/sysroot"
RPI_SSH_PORT="${RPI_SSH_PORT:-22}"
RPI_SSH_KEY="${RPI_SSH_KEY:-}"
RPI_REMOTE_RSYNC_PATH="${RPI_REMOTE_RSYNC_PATH:-rsync}"

if [[ -z "$RPI_REMOTE_HOST" || -z "$RPI_REMOTE_USER" || -z "$RPI_SYSROOT" ]]; then
    echo "RPI_REMOTE_HOST, RPI_REMOTE_USER, and RPI_SYSROOT are required." >&2
    usage >&2
    exit 2
fi

if ! command -v rsync >/dev/null 2>&1; then
    echo "rsync is required on the host." >&2
    exit 3
fi

if ! command -v ssh >/dev/null 2>&1; then
    echo "ssh is required on the host." >&2
    exit 3
fi

SSH_ARGS=(-p "$RPI_SSH_PORT")
RSYNC_ARGS=(-aHAX --numeric-ids --delete)
if [[ -n "$RPI_SSH_KEY" ]]; then
    SSH_ARGS+=(-i "$RPI_SSH_KEY")
fi

REMOTE="${RPI_REMOTE_USER}@${RPI_REMOTE_HOST}"
SSH_COMMAND=(ssh "${SSH_ARGS[@]}")
RSYNC_SSH="ssh"
for ssh_arg in "${SSH_ARGS[@]}"; do
    RSYNC_SSH+=" $(printf '%q' "$ssh_arg")"
done

if ! "${SSH_COMMAND[@]}" "$REMOTE" "$RPI_REMOTE_RSYNC_PATH --version" >/dev/null; then
    echo "Unable to connect to $REMOTE or run rsync remotely." >&2
    echo "Check the hostname, SSH credentials, and that rsync is installed on the Raspberry Pi." >&2
    exit 4
fi

if [[ "$CLEAN_SYSROOT" == true ]]; then
    sudo rm -rf "$RPI_SYSROOT"
fi

sudo mkdir -p "$RPI_SYSROOT"

sudo mkdir -p "$RPI_SYSROOT/lib" "$RPI_SYSROOT/usr/lib" "$RPI_SYSROOT/usr/include" "$RPI_SYSROOT/usr/local"

for dir in "/lib/" "/usr/lib/" "/usr/include/" "/usr/local/lib/" "/usr/local/include/"; do
    echo "Kopiere $dir..."
    sudo rsync "${RSYNC_ARGS[@]}" \
        -e "$RSYNC_SSH" \
        "$REMOTE:$dir" \
        "$RPI_SYSROOT$dir" || true
done

sudo rm -f "$RPI_SYSROOT"/lib/libQt6*
sudo rm -f "$RPI_SYSROOT"/usr/lib/libQt6*

sudo rm -f "$RPI_SYSROOT"/lib/libwiringPi*
sudo rm -f "$RPI_SYSROOT"/usr/lib/libwiringPi*

echo "Sysroot copied from $REMOTE to $RPI_SYSROOT"
