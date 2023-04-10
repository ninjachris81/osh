#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

SERVICES_FILE="localservices.txt"
if test -f "$SERVICES_FILE"; then
    echo "$SERVICES_FILE exists"
else
   echo "$SERVICES_FILE not found"
   exit 2
fi

echo "Stopping all services"
while read s; do
  echo "Stopping service $s"
  service $s stop 
done <$SERVICES_FILE

echo "Building all services"
while read s; do
  echo "Building service $s"
  ./deploy.sh $s
done <$SERVICES_FILE

echo "Starting all services"
while read s; do
  echo "Starting service $s"
  service $s start
done <$SERVICES_FILE
