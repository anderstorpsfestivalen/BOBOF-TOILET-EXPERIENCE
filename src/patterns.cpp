#include "patterns.h"

void solid(State* state)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        state->leds[i] = CRGB::White;
    }
}

void strobe(State* state)
{
    static uint8_t strobeCount = 0;
    for (int i = 0; i < NUM_LEDS; i++)
    {

        if (strobeCount == 1)
        {
            state->leds[i] = CRGB::White;
        }
        else
        {
            state->leds[i] = CRGB::Black;
        }
    }
    if (strobeCount == 1)
    {
        strobeCount = 0;
    }
    else
    {
        strobeCount = 1;
    }
}

void turborave(State* state)
{
    fill_rainbow(state->leds, NUM_LEDS, state->hue, 7);
}