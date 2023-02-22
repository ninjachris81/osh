#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

service CoreService stop
service RS485RelayService stop
service RS485RelayService2 stop
service ShutterService stop
service ShutterService2 stop
service WBB12Service stop
