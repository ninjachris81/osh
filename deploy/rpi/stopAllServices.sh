#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

echo "CoreService"
service CoreService stop
echo "RS485RelayService"
service RS485RelayService stop
service RS485RelayService2 stop
echo "ShutterService"
service ShutterService stop
service ShutterService2 stop
echo "WBB12Service"
service WBB12Service stop
echo "RS485EnergyMeterService"
service RS485EnergyMeterService stop

echo "Finished"
