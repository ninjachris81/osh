#!/usr/bin/env bash

set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "Usage: $0 <input-fstab> [output-fstab]" >&2
    exit 1
fi

input_file="$1"
output_file="${2:-}"

if [[ ! -f "$input_file" ]]; then
    echo "Input file not found: $input_file" >&2
    exit 1
fi

if [[ -n "$output_file" && ! -f "$output_file" ]]; then
    echo "Output file not found: $output_file (cannot create a backup)" >&2
    exit 1
fi

generated_file=$(mktemp)
trap 'rm -f "$generated_file"' EXIT

awk '
function print_entry(source, mountpoint, type, options, dump, pass) {
    printf "%-20s  %-15s %-7s %-29s %-7s %s\n", \
        source, mountpoint, type, options, dump, pass
}

/^[[:space:]]*#/ || /^[[:space:]]*$/ {
    raw[++count] = $0
    is_raw[count] = 1
    next
}

{
    if (NF < 6) {
        printf "Invalid fstab entry on line %d in %s\n", NR, FILENAME > "/dev/stderr"
        failed = 1
        next
    }

    if ($2 == "/" && $3 == "ext4") {
        root_entries++
        $4 = "ro,noatime,errors=remount-ro"
    }

    if ($2 == "/tmp") {
        tmp_entries++
        $1 = "tmpfs"
        $3 = "tmpfs"
        $4 = "defaults,noatime,nosuid,nodev"
        $5 = "0"
        $6 = "0"
    }

    source[++count] = $1
    mountpoint[count] = $2
    type[count] = $3
    options[count] = $4
    dump[count] = $5
    pass[count] = $6
}

END {
    if (failed) {
        exit 1
    }
    if (root_entries != 1) {
        printf "Expected one ext4 root mount in %s, found %d\n", FILENAME, root_entries > "/dev/stderr"
        exit 1
    }
    if (tmp_entries > 1) {
        printf "Expected at most one /tmp mount in %s, found %d\n", FILENAME, tmp_entries > "/dev/stderr"
        exit 1
    }

    for (i = 1; i <= count; i++) {
        if (is_raw[i]) {
            print raw[i]
        } else {
            print_entry(source[i], mountpoint[i], type[i], options[i], dump[i], pass[i])
        }
    }

    if (tmp_entries == 0) {
        print_entry("tmpfs", "/tmp", "tmpfs", "defaults,noatime,nosuid,nodev", "0", "0")
    }
}
' "$input_file" > "$generated_file"

if [[ -n "$output_file" ]]; then
    cp -- "$output_file" "${output_file}_backup"
    cat "$generated_file" > "$output_file"
else
    cat "$generated_file"
fi
