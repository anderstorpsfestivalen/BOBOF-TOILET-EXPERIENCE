#include "patterns.h"


typedef void (*PatternList[])();
PatternList gPatterns = { rainbow };

uint8_t gHue = 0;
CRGB leds[NUM_LEDS];

void init() {
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } 
}

void rainbow() 
{
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}