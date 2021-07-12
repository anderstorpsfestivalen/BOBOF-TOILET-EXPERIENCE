#pragma once
#include "settings.h"
#include <Arduino.h>
#include <SPI.h>
#include <FastLED.h>
#include "InputDebounce.h"
#include "patterns.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

PatternList functions[] = { solid, strobe, turborave };

static InputDebounce lightButton;
int buttonState = 0;
int lightState = 0;

unsigned long lastPress = millis();
unsigned int currentMode = 0;
unsigned long patternLength = millis();
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
		unsigned long k = lastPress+TIME_TO_RESET; 
		Serial.print(lastPress);
		Serial.print(k);
		Serial.write("\n");
		Serial.print(millis());
		Serial.write("\n\n");
	//	if(random(0, 10)  > 7) {
			cp = true;
		//}
	} else {
		Serial.write("NOT CP \n");
		cp = false;
	}
}

void selectPattern() {
	if (millis() + (1 * 1000) < lastPress) {
		solid(&state);
	} else {
		if (millis() > patternLength) {
			currentMode = random(0,ARRAY_SIZE(functions)-1);
			patternLength = millis() + (random(0,15)*1000);
		}

		functions[currentMode](&state);
	}
}

void buttonLight() {
	if (lightState == LOW)
	{
		analogWrite(BUTTON_LED, 255);
	}
	else
	{
		analogWrite(BUTTON_LED, 0);
	}	
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

	FastLED.addLeds<WS2812B, 11, GRB>(state.leds, NUM_LEDS);

}

void loop()
{	
	checkCP();

	lightButton.process(millis());
	buttonLight();	


	for (int i = 0; i < NUM_LEDS; i++)
	{
		if (lightState == HIGH)
		{
			if(cp) {
				selectPattern();
			} else {
				functions[0](&state);
			}

		}
		else
		{
			state.leds[i] = CRGB::Black;
		}
	}


	FastLED.show();
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}


