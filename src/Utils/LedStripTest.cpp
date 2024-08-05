// testet ob der LED Streifen auch funktioniert. 
#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 23
#define DATA_PIN 4


// array of leds
CRGB leds[NUM_LEDS];

#define NUM_COLORS 5

int g_Brightness = 255;   



class Drawer{
    private:
    byte marqueeHue = 4;
    int marqueeScroll = 0;


    public:
    void DrawTwinkle()
    {
        FastLED.clear(false);

        const CRGB TwinkleColors [NUM_COLORS] = 
        {
            CRGB::Red,
            CRGB::Blue,
            CRGB::Purple,
            CRGB::Green,
            CRGB::Yellow
        };

        for (int i=0; i<NUM_LEDS/4; i++) 
        {
            leds[random(NUM_LEDS)] = TwinkleColors[random(0, NUM_COLORS)];
            FastLED.show(g_Brightness);
            delay(200);
        }
    }


    void DrawMarqueeMirrored()
    {        
        (marqueeHue < 255) ? marqueeHue+=4:0;
        byte newHue = marqueeHue;
        
        CRGB c;
        for (int i = 0; i < (NUM_LEDS + 1) / 2; i ++)
        {
            leds[i].setHue(newHue).fadeToBlackBy(100);
            leds[NUM_LEDS - 1 - i].setHue(newHue).fadeToBlackBy(100); 
            // die set anweisung verbraucht entweder zuviel Speicher oder
            // erzeugt einne Überlauf. deswegen im Hauptprogramm herausgenommen
            (newHue < 255) ? newHue+=8: newHue=0;
        }
        
        leds[random(NUM_LEDS)].setColorCode(CRGB::White).maximizeBrightness();                         
    }
};


Drawer drawer;


void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    drawer = Drawer();
    
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



void loop() { 
  // // Turn the LED on, then pause
  // leds[0] = CRGB::Red;
  // FastLED.show();
  // delay(500);
  // // Now turn the LED off, then pause
  // leds[0] = CRGB::Black;
  // FastLED.show();
  // delay(500);

 //DrawMarqueeMirrored();


  drawer.DrawMarqueeMirrored();
  delay(50);
  //FastLED.setBrightness(20);
  FastLED.show();
}