#!/usr/bin/env bash

set -euo pipefail

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <input-fstab> <output-fstab>" >&2
    exit 1
fi

input_file="$1"
output_file="$2"

if [[ ! -f "$input_file" ]]; then
    echo "Input file not found: $input_file" >&2
    exit 1
fi

boot_partuuid=$(awk '$2 == "/boot/firmware" && $3 == "vfat" { print $1; exit }' "$input_file")
root_partuuid=$(awk '$2 == "/" && $3 == "ext4" { print $1; exit }' "$input_file")

if [[ -z "$boot_partuuid" || -z "$root_partuuid" ]]; then
    echo "Could not find the /boot/firmware and / mount entries in $input_file" >&2
    exit 1
fi

generated_content=$(cat <<EOF
proc            /proc           proc    defaults          0       0
${boot_partuuid}  /boot/firmware  vfat    defaults          0       2
${root_partuuid}  /               ext4    ro,noatime,errors=remount-ro  0       1
/dev/sda1  /var           ext4    rw,noatime,defaults          0   2
tmpfs    /tmp            tmpfs    defaults,noatime,nosuid,nodev    0   0
EOF
)

echo "Preview for $output_file:"
echo "----------------------------------------"
printf '%s\n' "$generated_content"
echo "----------------------------------------"

read -r -p "Write this content to $output_file? [Y/n] " answer
case "$answer" in
    [Nn]|[Nn][Oo])
        echo "Cancelled."
        exit 0
        ;;
esac

mkdir -p "$(dirname "$output_file")"
printf '%s\n' "$generated_content" > "$output_file"
echo "Wrote $output_file"