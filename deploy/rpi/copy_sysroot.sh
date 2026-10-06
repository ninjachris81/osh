#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./deploy/rpi/copy_sysroot2.sh <IP> <user>

Optional variables:
  RPI_SSH_PORT             SSH port (default: 22)
  RPI_SSH_KEY              SSH private key to use
  RPI_REMOTE_RSYNC_PATH    Remote rsync command (default: rsync)
EOF
}

RPI_REMOTE_HOST="$1"
RPI_REMOTE_USER="$2"

SYSROOT=/opt/rpi/sysroot2

sudo apt install symlinks

mkdir -p "$SYSROOT/lib"
rsync -avzS --rsync-path="rsync" --delete "$RPI_REMOTE_USER"@"$RPI_REMOTE_HOST":/lib/* "$SYSROOT/lib"

mkdir -p "$SYSROOT/usr"
rsync -avzS --rsync-path="rsync" --delete "$RPI_REMOTE_USER"@"$RPI_REMOTE_HOST":/usr/include/* "$SYSROOT/usr/include"

rsync -avzS --rsync-path="rsync" --delete "$RPI_REMOTE_USER"@"$RPI_REMOTE_HOST":/usr/lib/* "$SYSROOT/usr/lib"

#mkdir -p "$SYSROOT/opt"# rsync -avzS --rsync-path="rsync" --delete "$RPI_REMOTE_USER"@"$RPI_REMOTE_HOST":/opt/vc "$SYSROOT/opt/vc"

symlinks -rc "$SYSROOT"