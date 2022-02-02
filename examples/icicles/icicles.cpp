/*
 * Code to similuate dripping icicles using Arduino and multiple NeoPixel strips
 * be sure to weatherize if you are putting this outdoors
 */
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "Adafruit_NeoPixel.hpp"

void delay(uint32_t ms) {
	sleep_ms(ms);
};

#define PIN1 1
#define PIN2 7
#define PIN3 8
#define PIN4 9
#define PIN5 10

#define UP 1
#define DOWN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

const int numberOfStrips = 2;

struct icicle_t
{
  int startPixel;
  int length;
  int dir;
  // Adafruit_NeoPixel strip; 
} ;

icicle_t icicles[numberOfStrips];
Adafruit_NeoPixel string = Adafruit_NeoPixel(50, PIN1, NEO_RGB + NEO_KHZ800);

/*
// initialize strips using an array
// if you use a number of strips differing from 5, then the array needs to be adjusted accordingly
Adafruit_NeoPixel strip[numberOfStrips] = 
{
  Adafruit_NeoPixel(8, PIN1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(8, PIN2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(8, PIN3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(8, PIN4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(8, PIN1, NEO_RGB + NEO_KHZ800)
  };
*/

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

//Dripping icicle by @GreenMoonArt

void drippingIcicle(int i, uint32_t wait) 
{  
  uint32_t color1 = string.Color(128,128,128);
  uint32_t color2 = string.Color(64,64,64);
  uint32_t color3 = string.Color(32,32,32);
  uint32_t color4 = string.Color(16,16,16);
  uint32_t colorOff = string.Color(0, 0, 0);

//  printf("color1 = %08x, color2 = %08x, color3 = %08x, color4 = %08x, colorOff = %08x\n", color1,color2,color3,color4,colorOff);

  for (int j=0; j<icicles[i].length+3; j++) 
  {
//  printf("i = %d, j = %d, dir = %d, pixel = %d\n",i, j, icicles[i].dir, icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j) : j);

    if(j >= 3) 
    {
//      printf("j(%d) >= 3:relative pixel# = %d, color1\n",j,(icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+3) : j-3),j);
      string.setPixelColor((icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+3) : j-3), color1);
    }
    if(j >= 2) 
    {
//      printf("j(%d) >= 2:relative pixel# = %d, color2\n",j,(icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+2) : j-2),j);
      string.setPixelColor((icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+2) : j-2), color2);
    }
    if(j >= 1) 
    {
//      printf("j(%d) >= 1:relative pixel# = %d, color3\n",j,(icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+1) : j-1),j);
      string.setPixelColor((icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+1) : j-1), color3);
    }

//    printf("j(%d) relative pixel# = %d, color4\n",j,(icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j) : j),j);
    string.setPixelColor((icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j) : j), color4);

    // turn off trailing LEDs
    if(j >= 4)
    {
//      printf("j(%d) >= 4:relative pixel# = %d, colorOff\n",j,(icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j) : j)-4,j);
      string.setPixelColor((icicles[i].dir ? (icicles[i].startPixel + icicles[i].length - j+4) : j-4), colorOff);
    }

    string.show();
    delay(wait);
  }
}

void ledsOff(int i, u_int32_t wait)
{
  for(uint16_t j=0; j<string.numPixels(); j++) 
  {
    string.setPixelColor(j, string.Color(0, 0, 0));
  }
  string.show();
  delay(wait);
}

int main()
{
  int dripRate = 100;               // time in mSec each pixel is lit

// initialize the icicles

  icicles[0].startPixel = 0;
  icicles[0].length = 16;
  icicles[0].dir = DOWN;

  icicles[1].startPixel = 17;
  icicles[1].length = 16;
  icicles[1].dir = UP;

  stdio_init_all();
  string.begin();
  string.setBrightness(255);
  string.show(); // Initialize all pixels to 'off'

  while(1)
    for (int i = 0; i < numberOfStrips; i++)
    {
      int randomStrip = rand() % numberOfStrips;
      int randomDelay = rand() % 1000;

      drippingIcicle(randomStrip, dripRate);

      ledsOff(i, 100);

      delay(randomDelay);
    }
}
