#include <Arduino.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN 4


// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    cli(); // Disable interrupts
    CLKPR = (1<<CLKPCE); // Prescaler enable
    CLKPR = 0x00; // Clock division factor
    sei(); // Enable interrupts
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    
}

void loop() { 
  // Turn the LED on, then pause
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}