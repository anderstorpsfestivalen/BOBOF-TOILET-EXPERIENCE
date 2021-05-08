#include "settings.h"
#include <Arduino.h>
#include <SPI.h>
#include <FastLED.h>
#include "InputDebounce.h"
#include "patterns.h"

CRGB leds[NUM_LEDS];


static InputDebounce lightButton;
int buttonState = 0;
int lightState = 0;
int lastPress = millis();


void buttonTest_pressedCallback(uint8_t pinIn) {
	if (lightState == LOW)
		{
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

	FastLED.addLeds<APA102, 11, 13, BGR>(leds, NUM_LEDS);


}

void loop()
{

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
			leds[i] = CRGB::White;
		}
		else
		{
			leds[i] = CRGB::Black;
		}
	}
	FastLED.show();
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}
