#pragma once
#include "settings.h"
#include <Arduino.h>
#include <SPI.h>
#include <FastLED.h>
#include "InputDebounce.h"
#include "patterns.h"


PatternList functions[] = { solid, strobe, turborave };

static InputDebounce lightButton;
int buttonState = 0;
int lightState = 0;

unsigned long lastPress = millis();
unsigned int currentMode = 0;
bool cp = false;

State state;

void buttonTest_pressedCallback(uint8_t pinIn) {
	if (lightState == LOW)
		{
			lastPress = millis();
			lightState = HIGH;
		}	
		else
		{
			lightState = LOW;
		}
}

void releasedDurationCallback(uint8_t pinIn, unsigned long duration) {
	//Serial.println(duration);
}

void checkCP() {
	if (lastPress + TIME_TO_RESET > millis()) {
		cp = true;
	} else {
		cp = false;
	}
}

void selectPattern() {

}


void setup()
{
	Serial.begin(115200);
	Serial.write("HELLO");

	//Config button led
	pinMode(BUTTON_LED, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
	analogWrite(BUTTON_LED, 255);

	lightButton.registerCallbacks(buttonTest_pressedCallback, NULL, NULL, releasedDurationCallback);
	lightButton.setup(BUTTON_PIN, 20, InputDebounce::PIM_INT_PULL_UP_RES, 0, InputDebounce::ST_NORMALLY_CLOSED);

	FastLED.addLeds<WS2812B, 11, GRB>(*state.leds, NUM_LEDS);


}

void loop()
{	
	checkCP();

	lightButton.process(millis());
	
	if (lightState == LOW)
	{
		analogWrite(BUTTON_LED, 255);
	}
	else
	{
		analogWrite(BUTTON_LED, 0);
	}

	for (int i = 0; i < NUM_LEDS; i++)
	{
		if (lightState == HIGH)
		{
			if(cp) {
			 	
			} else {
				functions[0](&state);
			}

		}
		else
		{
			*state.leds[i] = CRGB::Black;
		}
	}


	FastLED.show();
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}


