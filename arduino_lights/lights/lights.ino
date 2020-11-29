/*
File: lights.ino
Author: Clayton Franklin
Date: 26-Nov-2020
Version: 1.0
Purpose: Code to run Christmas lights for Christmas 2020
*/
#include <Adafruit_NeoPixel.h>

// Define Pins for upper and lower LED Control
#define UPPER_LED_PIN       9
#define LOWER_LED_PIN       6

// Define number of LEDs for each strand
#define UPPER_LED_COUNT     450
#define LOWER_LED_COUNT     150

// Define LED brightness
#define LED_BRIGHTNESS      192

// Create objects for upper and lower LED strands
Adafruit_NeoPixel upperStrand(UPPER_LED_COUNT, UPPER_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel lowerStrand(LOWER_LED_COUNT, LOWER_LED_PIN, NEO_GRB + NEO_KHZ800);
/*************************************************
Argument Definition:
    Arg 1: Number of LEDs in a strand
    Arg 2: Arduino pin to drive LEDs from
    Arg 3: Add flags together as needed:
        NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
        NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
        NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
        NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
        NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
*************************************************/

// Setup for the main loop
void setup() 
{
    // Initialize objects
    upperStrand.begin();
    lowerStrand.begin();
    // Turn off all lights
    upperStrand.show();
    lowerStrand.show();
    // Set brightness of LEDs on strands
    upperStrand.setBrightness(LED_BRIGHTNESS);
}

// Run the code forever
void loop() 
{
    colorWipe(upperStrand.Color(255, 0, 0), 10);
    //twinkleLights(upperStrand.Color(0, 0 , 255), 50, 100, false);
    upperStrand.clear();
    lowerStrand.clear();
}

// Functions for the lights
/*************************************************
Function colorWipe(stripColor, wait)
Argument Definition:
    Arg 1: the color of the strips
    Arg 2: the delay between changes in ms
*************************************************/
void colorWipe(uint32_t color, int wait) 
{
    for (int i = 0; i < upperStrand.numPixels(); i++)
    {
        upperStrand.setPixelColor(i, color);
        lowerStrand.setPixelColor(i, color);
        upperStrand.show();
        lowerStrand.show();
        delay(wait);
    }
}

/*************************************************
Function twinkleLights(color, wait, number, onlyOne)
Argument Definition:
    Arg 1: color to make the strip
    Arg 2: delay between individual pixels
    Arg 3: number of LEDs to light up in one round
    Arg 4: only see one LED at a time
*************************************************/
void twinkleLights(uint32_t color, int wait, int number, bool onlyOne)
{
    upperStrand.clear();
    lowerStrand.clear();
    for (int i = 0; i < number; i++)
    {
        upperStrand.setPixelColor(random(UPPER_LED_COUNT), color);
        lowerStrand.setPixelColor(random(LOWER_LED_COUNT), color);
        upperStrand.show();
        lowerStrand.show();
        delay(wait);
        if (onlyOne){
            upperStrand.clear();
            lowerStrand.clear();
        }
    }
    delay(wait);
}

/*************************************************
Function twinkleLights(red, green, blue, wait)
Argument Definition:
    Arg 1: Red value for the strip
    Arg 2: Green value for the strip
    Arg 3: Blue value for the strip 
    Arg 4: wait time in ms (milliseconds) 
*************************************************/
void runningLights(uint8_t red, uint8_t green, uint8_t blue, int wait)
{
    int position = 0;

    for (int j = 0; j < UPPER_LED_COUNT * 2; j++)
    {
        position++;
        for (int i = 0; i < UPPER_LED_COUNT; i++)
        {
            uint8_t redCalc = 0;
            //upperStrand.setPixelColor(i, upperStrand.Color());
        }
    }
}