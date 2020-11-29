#!/bin/bash
# Compile the program for arduino mega
arduino-cli compile -b arduino:avr:mega "../arduino_lights/$1"
# Upload the program to the ardino
arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:mega "../arduino_lights/$1"