#!/bin/bash

set -euo pipefail

SOUNDCARD_COUNT=2
/etc/osh/scripts/trigger_alsa.sh "$SOUNDCARD_COUNT"