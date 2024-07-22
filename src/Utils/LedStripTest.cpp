// testet ob der LED Streifen auch funktioniert. 
#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 23
#define DATA_PIN 4


// array of leds
CRGB leds[NUM_LEDS];

#define NUM_COLORS 5
static const CRGB TwinkleColors [NUM_COLORS] = 
{
    CRGB::Red,
    CRGB::Blue,
    CRGB::Purple,
    CRGB::Green,
    CRGB::Yellow
};
int g_Brightness = 255;   


void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    
}
void DrawComet()
{
    const byte fadeAmt = 128;
    const int cometSize = 1;
    const int deltaHue  = 4;

    static byte hue = HUE_RED;
    static int iDirection = 1;
    static int iPos = 0;

    hue += deltaHue;

    iPos += iDirection;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        leds[iPos + i].setHue(hue);
    
     //Randomly fade the LEDs
     for (int j = 0; j < NUM_LEDS; j++)
         if (random(10) > 5)
             leds[j] = leds[j].fadeToBlackBy(fadeAmt);  

    delay(60);
}



void DrawTwinkle()
{
    FastLED.clear(false);

    for (int i=0; i<NUM_LEDS/4; i++) 
    {
        leds[random(NUM_LEDS)] = TwinkleColors[random(0, NUM_COLORS)];
        FastLED.show(g_Brightness);
        delay(200);
    }
}

void DrawMarqueeMirrored()
{
    static byte j = 0;
    j+=4;
    byte k = j;
    
    CRGB c;
    for (int i = 0; i < (NUM_LEDS + 1) / 2; i ++)
    {
        leds[i] = c.setHue(k);
        leds[NUM_LEDS - 1 - i] = c.setHue(k);
        k+= 8;
    }


    static int scroll = 0;
    scroll++;

    for (int i = scroll % 5; i < NUM_LEDS / 2; i += 5)
    {
        leds[i] = CRGB::Black;
        leds[NUM_LEDS - 1 - i] = CRGB::Black;
    }   

    delay(50);
}


void loop() { 
  // // Turn the LED on, then pause
  // leds[0] = CRGB::Red;
  // FastLED.show();
  // delay(500);
  // // Now turn the LED off, then pause
  // leds[0] = CRGB::Black;
  // FastLED.show();
  // delay(500);

  DrawMarqueeMirrored();
  FastLED.show(50);
}