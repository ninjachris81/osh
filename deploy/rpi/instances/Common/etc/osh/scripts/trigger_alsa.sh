#!/bin/bash

# Get the number of cards from the first parameter (default to 6 if not provided)
NUM_CARDS=${1:-6}

# Helper function to kick the softvol device and set its volume to 50% (0.5)
initialize_and_set_volume() {
    local dev_name="$1"
    
    # Kick the device to register the softvol control
    timeout 0.1 aplay -D "$dev_name" /dev/zero >/dev/null 2>&1
    
    # Set volume to 50% (0.5). Tries 'Master' first, falls back to the device name.
    amixer -D "$dev_name" sset Master 50% >/dev/null 2>&1 || \
    amixer -D "$dev_name" sset "$dev_name" 50% >/dev/null 2>&1
}

echo "Initializing and setting softvol controls for cards 0 to ${NUM_CARDS} to 0.5..."

# 1. Process all individual mono channels
for ((card=0; card<=NUM_CARDS; card++)); do
    for sub in {0..1}; do
        initialize_and_set_volume "mono${card}_${sub}_sv"
    done
done

# 2. Process global master channels
initialize_and_set_volume "all_mono_mono_sv"
initialize_and_set_volume "all_mono_stereo_sv"

echo "All softvol devices kicked and volumes set to 0.5 (50%). Check alsamixer now!"
