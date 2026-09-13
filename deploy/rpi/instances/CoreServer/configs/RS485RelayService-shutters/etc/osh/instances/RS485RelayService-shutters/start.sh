#!/bin/bash

SCRIPT_DIR=$(dirname "$(realpath "$0")")
CONFIG_FILE=$SCRIPT_DIR/config.ini

/etc/osh/scripts/start.sh RS485RelayService RS485RelayService-shutters "$CONFIG_FILE"
