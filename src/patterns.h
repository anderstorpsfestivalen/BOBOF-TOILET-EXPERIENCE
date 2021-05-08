#include "settings.h"
#include <FastLED.h>



class BOBOFLamp {
    public:
        CRGB leds[NUM_LEDS];
        FastLED.addLeds<APA102, 11, 13, BGR>(leds, NUM_LEDS)
};