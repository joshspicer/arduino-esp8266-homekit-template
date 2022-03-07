#!/bin/bash

# https://blog.g3rt.nl/arduino-serial-over-tcp-openwrt.html

DEV=/dev/ttyACM0
PORT=50000
BAUD=9600

while true; do 
    if [ -e $DEV ]
    then
        socat tcp-l:$PORT,reuseaddr,fork file:$DEV,nonblock,raw,echo=0,waitlock=/var/run/tty,b$BAUD
    else
        sleep 2
    fi
done