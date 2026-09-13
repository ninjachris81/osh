#!/bin/bash

set -euo pipefail

EXEC_NAME="$1"
PID_NAME="${2:-$1}"

PID_DIR="/run/osh"
PID_FILE="$PID_DIR/$PID_NAME.pid"

mkdir -p "$PID_DIR"

if [[ -f "$PID_FILE" ]]; then
        OLD_PID=$(cat "$PID_FILE")
        if [[ -n "$OLD_PID" ]] && kill -0 "$OLD_PID" 2>/dev/null; then
                echo "Already running with PID $OLD_PID" >&2
                exit 1
        fi
        rm -f "$PID_FILE"
fi

echo "$$" > "$PID_FILE"

cd "/etc/osh/$EXEC_NAME"
exec "./$EXEC_NAME"
