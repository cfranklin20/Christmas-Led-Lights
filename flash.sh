#!/bin/bash
arduino-cli compile -b arduino:avr:mega "arduino_lights/$1"
arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:mega "arduino_lights/$1"