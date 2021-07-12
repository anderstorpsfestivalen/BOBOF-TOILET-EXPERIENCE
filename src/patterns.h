#include "settings.h"
#include <FastLED.h>

struct State {
  CRGB leds[NUM_LEDS] = {};
  uint8_t hue;
};

typedef void (*PatternList)(State*);

void solid(State* state);
void strobe(State* state);
void turborave(State* state);
