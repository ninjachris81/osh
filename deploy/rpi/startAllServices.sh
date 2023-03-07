#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

echo "CoreService"
service CoreService start
echo "RS485RelayService"
service RS485RelayService start
service RS485RelayService2 start
echo "ShutterService"
service ShutterService start
service ShutterService2 start
echo "WBB12Service"
service WBB12Service start
echo "RS485EnergyMeterService"
service RS485EnergyMeterService start
