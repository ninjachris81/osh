#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

service CoreService start
service RS485RelayService start
service RS485RelayService2 start
service ShutterService start
service ShutterService2 start
service WBB12Service start
service RS485EnergyMeterService start
