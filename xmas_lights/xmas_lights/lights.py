#!/usr/bin/env python3
import board
import neopixel

pixels = neopixel.NeoPixel(board.D18, 30)

while True:
    pixels.fill((0,255,0))
