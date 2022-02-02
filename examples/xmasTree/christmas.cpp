#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "Adafruit_NeoPixel.hpp"

#define PIN1 1
#define PIN2 7
#define PIN3 8
#define PIN4 9
#define PIN5 10

#define TRUE 1
#define FALSE 0
#define DEFAULTBRIGHTNESS 255
#define WHITE 0x100d06
#define TREESLEEP 250
#define BLINKSLEEP 50
/*
    Update rate information:
    NeoPixels receive data from a fixed-frequency 800 KHz datastream 
    (except for “V1” Flora pixels, which use 400 KHz). 
    Each bit of data therefore requires 1/800,000 sec — 1.25 microseconds. 
    One pixel requires 24 bits (8 bits each for red, green blue) — 30 microseconds/pixel. 
    After the last pixel’s worth of data is issued, the stream must stop for at least 
    50 microseconds for the new colors to “latch.”

    A 50 pixel string: (50*30)+50 = 1550 uS.
*/    
const int numberOfStrips = 2;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip[numberOfStrips] = 
{
    Adafruit_NeoPixel(50, PIN1, NEO_RGB + NEO_KHZ800),
    Adafruit_NeoPixel(50, PIN2, NEO_RGB + NEO_KHZ800) 
};

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void randomTree(int stripNumber,u_int16_t &n, u_int8_t reInit)
{
    u_int32_t randomColor;
    u_int32_t blinkColor[6] = { 0x800000,   /* red    */
                                0x808000,   /* yellow */
                                0x008000,   /* green  */
                                0x808080,   /* white  */
                                0x000080,   /* blue   */
                                0x800080 }; /* purple */

    if (reInit) // all one color
    {
        strip[stripNumber].setPixelColor(n,WHITE);
    }
    else // set a random pixel to a random bright color
    {
        n = rand() % strip[stripNumber].numPixels();
        randomColor = blinkColor[rand() % 6];
        strip[stripNumber].setPixelColor(n,randomColor);
    }
}
int main()
{
  u_int8_t reInit[numberOfStrips];
  u_int16_t pixelNumber[numberOfStrips]; // save last pixel changed


  stdio_init_all();
//
//  Init trees
//
    for (int i=0; i < numberOfStrips; i++)
    {
        strip[i].begin();
        strip[i].setBrightness(DEFAULTBRIGHTNESS);
        strip[i].clear();
        strip[i].show();
        strip[i].fill(WHITE,0,strip[i].numPixels());
        strip[i].show();
        reInit[i] = FALSE;
        pixelNumber[i] = 0;
    }

    while(1)
    {
        for (int i = 0; i < numberOfStrips; i++)
        {
            if (strip[i].canShow())
            {
                randomTree(i, pixelNumber[i], reInit[i]);  // set a pixel and color
                strip[i].show();
                reInit[i] = TRUE;
                sleep_ms(BLINKSLEEP);
                randomTree(i, pixelNumber[i], reInit[i]);  // set pixel back to original color
                strip[i].show();
                reInit[i] = FALSE;
            }
        }
        sleep_ms(TREESLEEP);
    }  
}
