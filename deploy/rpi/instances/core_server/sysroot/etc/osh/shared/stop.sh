#!/bin/bash

set -euo pipefail

PID_FILE="/run/osh/$1.pid"

if [[ ! -f "$PID_FILE" ]]; then
	echo "PID file not found: $PID_FILE" >&2
	exit 1
fi

PID=$(cat "$PID_FILE")

if [[ -z "$PID" ]] || ! kill -0 "$PID" 2>/dev/null; then
	rm -f "$PID_FILE"
	exit 0
fi

if [[ -e "/proc/$PID/fd/0" ]]; then
	printf "q\r" > "/proc/$PID/fd/0" || true
fi

sleep 2

kill "$PID" 2>/dev/null || true

sleep 1

kill -9 "$PID" 2>/dev/null || true

rm -f "$PID_FILE"
