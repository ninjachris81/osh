#!/bin/bash

# Get the number of cards from the first parameter (default to 6 if not provided)
NUM_CARDS=${1:-6}

echo "Initializing softvol controls for cards 0 to ${NUM_CARDS}..."

# 1. Trigger all individual mono channels instantly
for ((card=0; card<=NUM_CARDS; card++)); do
    for sub in {0..1}; do
        timeout 0.1 aplay -D "mono${card}_${sub}_sv" /dev/zero >/dev/null 2>&1
    done
done

# 2. Trigger global master channels
timeout 0.1 aplay -D "all_mono_mono_sv" /dev/zero >/dev/null 2>&1
timeout 0.1 aplay -D "all_mono_stereo_sv" /dev/zero >/dev/null 2>&1

echo "All softvol devices kicked. Check alsamixer now!"
