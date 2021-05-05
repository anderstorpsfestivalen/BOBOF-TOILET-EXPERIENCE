#include "settings.h"
#include <Arduino.h>
#include <SPI.h>

#include "patterns.h"


void setup()
{	
	Serial.begin(115200);
	Serial.write("HELLO");

	//Config button led
	pinMode(BUTTON_LED, OUTPUT); 
	analogWrite(BUTTON_LED, 127);

	FastLED.addLeds<APA102, 11, 13, BGR>(leds, NUM_LEDS);
}

void loop()
{
	rainbow();
	FastLED.show();

	FastLED.delay(1000/FRAMES_PER_SECOND); 
}