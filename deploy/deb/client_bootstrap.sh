
#!/usr/bin/env bash
set -e

usage() {
    cat <<'EOF'
Usage:
    ./client_bootstrap.sh <instance-name>

EOF
}

if [[ $# -lt 1 || $# -gt 1 ]]; then
    echo "An instance name is required." >&2
    usage >&2
    exit 2
fi

INSTANCE_NAME="$1"

curl -k -fsSL https://192.168.177.7/client_setup.sh | bash

sudo apt update
sudo apt install -y "osh-${INSTANCE_NAME,,}-common"

cd /etc/osh/scripts/
sudo ./apt_update_all.sh