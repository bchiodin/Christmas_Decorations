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
Useful timer functions:

static absolute_time_t make_timeout_time_us(uint64_t us);
void sleep_until (absolute_time_t target);
void sleep_us (uint64_t us);
void sleep_ms (uint32_t ms);
bool best_effort_wfe_or_timeout (absolute_time_t timeout_timestamp);
*/