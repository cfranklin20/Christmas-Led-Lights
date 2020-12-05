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
#define LOWER_LED_COUNT     487

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

// Array for pre-defined colors
const uint32_t colors[5] = 
{
    upperStrand.Color(255,  0,      0),     // Red
    upperStrand.Color(0,    255,    0),     // Green
    upperStrand.Color(0,    0,      255),   // Blue
    upperStrand.Color(127,  127,    127),   // White (Half Brightness)
    upperStrand.Color(255,  165,    0)     // Orange
};

const uint8_t rgbValues[4][3] = 
{
    {255,   0,      0},     // Red
    {0,     255,    0},     // Green
    {0,     0,      255},   // Blue
    {127,   127,    127}    // White (Half Brightness)
};

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
    lowerStrand.setBrightness(LED_BRIGHTNESS);
    // Define an array of colors
}

// Run the code forever
void loop() 
{
    //colorWipe(upperStrand.Color(255, 0, 0), 10);
    twinkleLights(colors, 5, LOWER_LED_COUNT, false);
    clear();
    for (int i = 0; i < 4; i++)
    {
        runningLights(rgbValues[i], 0);
    }
    clear();
    rgbLoop();
    clear();
    for (int i = 0; i < 4; i++)
    {
        theaterChase(colors[i], 50);
    }
    clear();
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
    for (int i = 0; i < lowerStrand.numPixels(); i++)
    {
        upperStrand.setPixelColor(i, color);
        lowerStrand.setPixelColor(i, color);
        upperStrand.show();
        lowerStrand.show();
        delay(wait);
    }
}

/*************************************************
twinkleLights(color, wait, number, onlyOne)
@brief Twinkle random lights in the strip with colors passed in

@param color Array of colors to make the strip
@param wait The delay between individual pixels
@param number The number of LEDs to light up in one round
@param onlyOne Set only one LED at a time
*************************************************/
void twinkleLights(const uint32_t color[], int wait, int number, bool onlyOne)
{
    upperStrand.clear();
    lowerStrand.clear();
    for (int i = 0; i < number; i++)
    {
        upperStrand.setPixelColor(random(UPPER_LED_COUNT), color[i % 4]);
        lowerStrand.setPixelColor(random(LOWER_LED_COUNT), color[i % 4]);
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
runningLights(colors, wait)
@brief Animate a running of lights across the strip

@param colors A 2D array of RGB brightness values, 0 to 255
@param wait The wait time between runs in milliseconds
*************************************************/
void runningLights(const uint8_t colors[3], int wait)
{
    int position = 50;

    for (int j = 0; j < 50; j++)
    {
        position--;
        for (int i = 0; i < LOWER_LED_COUNT; i++)
        {
            uint8_t redCalc = ((sin(i + position) * 127 + 128) / 255) * colors[0];
            uint8_t greenCalc = ((sin(i + position) * 127 + 128) / 255) * colors[1];
            uint8_t blueCalc = ((sin(i + position) * 127 + 128) / 255) * colors[2];
            lowerStrand.setPixelColor(i, lowerStrand.Color(redCalc, greenCalc, blueCalc));
            upperStrand.setPixelColor(i, upperStrand.Color(redCalc, greenCalc, blueCalc));
        }
        showStrip();
        delay(wait);
    }
}

/*************************************************
theaterChase(color, wait)
@brief Run lights like a movie theater marquee

@param color Color value for the strip
@param wait Wait time for marquee
*************************************************/
void theaterChase(uint32_t color, int wait) 
{   
    // Repeat 10 times...
    for(int a = 0; a < 50; a++) 
    {
        // 'b' counts from 0 to 2...
        for(int b = 0; b < 3; b++) 
        { 
            clear();  //   Set all pixels in RAM to 0 (off)

            // 'c' counts up from 'b' to end of strip in steps of 3...
            for(int c = b; c < lowerStrand.numPixels(); c += 3) 
            {
                upperStrand.setPixelColor(c, color); // Set pixel 'c' to value 'color'
                lowerStrand.setPixelColor(c, color);
            }

            upperStrand.show(); // Update strip with new contents
            lowerStrand.show();
            delay(wait);  // Pause for a moment
        }
    }
}

/*************************************************
rgbLoop()
@brief Fade in and out RGB strip lights
*************************************************/

void rgbLoop()
{
    for(int j = 0; j < 3; j++ ) 
    {
        // Fade IN
        for(int k = 0; k < 256; k+=5) {
            switch(j) 
            {
                case 0: setAll(k,0,0); break;
                case 1: setAll(0,k,0); break;
                case 2: setAll(0,0,k); break;
            }
            showStrip();
            //delay(3);
        }
        // Fade OUT
        for(int k = 255; k >= 0; k-=5) 
        {
            switch(j) 
            {
                case 0: setAll(k,0,0); break;
                case 1: setAll(0,k,0); break;
                case 2: setAll(0,0,k); break;
            }
            showStrip();
            //delay(3);
        }
    }
}

// Helper Functions

void clear()
{
    upperStrand.clear();
    lowerStrand.clear();
}

void setAll(uint8_t red, uint8_t green, uint8_t blue)
{
    for(int i = 0; i < LOWER_LED_COUNT; i++) 
    {
        lowerStrand.setPixelColor(i, red, green, blue);
        upperStrand.setPixelColor(i, red, green, blue);
    }
  //showStrip();
}

void showStrip()
{
    upperStrand.show();
    lowerStrand.show();
}