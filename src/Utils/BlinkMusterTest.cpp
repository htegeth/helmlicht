#include <Arduino.h>
#include <FastLED.h>
#include "BlinkMuster.h"

#define NUM_LEDS 23
#define DATA_PIN 4

CRGB leds[NUM_LEDS];
BlinkMuster blinker = BlinkMuster();


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  blinker.setLeds(leds);
  blinker.setNumberLeds(NUM_LEDS);
  blinker.init();
}

 
void loop() {    
    blinker.blinkLeft();
    blinker.blinkRight();
}

