#!/bin/bash

PID=$(pidof $1)
printf "q\r" > /proc/$PID/fd/0

sleep 2

/usr/bin/killall -9 $1
