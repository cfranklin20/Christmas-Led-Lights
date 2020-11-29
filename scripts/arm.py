#!/usr/bin/env python3
from gpiozero import LED
from datetime import datetime, timedelta

# Put the relay on RPi Pin 23
relay = LED(23)
# Set the time to turn off 5 hours from now
endTime = datetime.now() + timedelta(hours=5)
# Loop until 5 hours has passed
while True:
    # Check if the time elapsed has been 5 hours
    if datetime.now() >= endTime:
        # Turn off the relay
        relay.off()
        break
    # Keep the relay on
    relay.on()
