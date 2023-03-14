#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

service mosquitto stop

rm /var/lib/mosquitto/mosquitto.db

service mosquitto start
