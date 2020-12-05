#!/usr/bin/env python3
from gpiozero import LED
from time import sleep

# Put the relay on RPi Pin 23
relay = LED(23)
# Turn the relay on
relay.on()
# Sleep for 5 hours
sleep(18000)
# Turn the relay off
relay.off()