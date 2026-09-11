#!/bin/bash

REPO_BASE_DIR="/var/www/debian-repo"
CODENAME="bookworm"

PACKAGES=$(reprepro -b "$REPO_BASE_DIR" list "$CODENAME" | awk '{print $2}' | sort -u)

if [ -n "$PACKAGES" ]; then
    reprepro -b "$REPO_BASE_DIR" remove "$CODENAME" $PACKAGES
fi

reprepro -b "$REPO_BASE_DIR" deleteunreferenced
reprepro -b "$REPO_BASE_DIR" export "$CODENAME"
