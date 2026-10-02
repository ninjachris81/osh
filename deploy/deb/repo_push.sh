#!/usr/bin/env bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
    ./repo_push.sh <repo_ip> <instance_name>

EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
    usage
    exit 0
fi

if [[ $# -ne 2 ]]; then
    echo "A repo IP and an instance name are required." >&2
    usage >&2
    exit 2
fi

REPO_IP="$1"
INSTANCE_NAME="$2"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
INSTANCE_DIR="$SCRIPT_DIR/../../build-deb/$INSTANCE_NAME"

if [[ ! -d "$INSTANCE_DIR" ]]; then
    echo "Error: Instance directory '$INSTANCE_DIR' does not exist." >&2
    exit 1
fi

read -rp "SSH username: " SSH_USER

REMOTE_DIR="/tmp/repo_push_${INSTANCE_NAME}"
CONTROL_PATH="$(mktemp -u /tmp/repo_push_ssh_XXXXXX)"
SSH_OPTS=(-o ControlMaster=auto -o "ControlPath=$CONTROL_PATH" -o ControlPersist=60)

echo "Opening SSH connection to $REPO_IP (password entered once)..."
ssh "${SSH_OPTS[@]}" -fN "${SSH_USER}@${REPO_IP}"

cleanup() {
    echo "Cleaning up remote working folder $REMOTE_DIR..."
    ssh "${SSH_OPTS[@]}" "${SSH_USER}@${REPO_IP}" "rm -rf '$REMOTE_DIR'"
    ssh "${SSH_OPTS[@]}" -O exit "${SSH_USER}@${REPO_IP}" 2>/dev/null || true
}
trap cleanup EXIT

echo "Creating remote working folder $REMOTE_DIR on $REPO_IP..."
ssh "${SSH_OPTS[@]}" "${SSH_USER}@${REPO_IP}" "mkdir -p '$REMOTE_DIR'"

echo "Copying repo_sync.sh, repo_add.sh and instance_config.sh..."
scp "${SSH_OPTS[@]}" "$SCRIPT_DIR/repo_sync.sh" "$SCRIPT_DIR/repo_add.sh" "$SCRIPT_DIR/$INSTANCE_NAME/instance_config.sh" \
    "${SSH_USER}@${REPO_IP}:${REMOTE_DIR}/"

echo "Copying files from $INSTANCE_DIR..."
scp "${SSH_OPTS[@]}" "$INSTANCE_DIR"/*.deb "${SSH_USER}@${REPO_IP}:${REMOTE_DIR}/"

echo "Executing repo_sync.sh on remote..."
ssh -tt "${SSH_OPTS[@]}" "${SSH_USER}@${REPO_IP}" "cd '$REMOTE_DIR' && chmod +x repo_sync.sh repo_add.sh && ./repo_sync.sh"
