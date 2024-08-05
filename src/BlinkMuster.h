#include <FastLED.h>

#define NUM_LEDS 23   
        
class BlinkMuster
{
     private:
        const byte fadeAmt = 128;
        const int8_t deltaHue  = 4;


        //const int defaultDelay = 50;
        const int runDelayTime = 50;       
        CRGB* leds;
        int8_t ledFragment = 0;
        int8_t rightBegin = 0;
        int8_t leftBegin = 0;
        int blinkDelayMain = 0;
        int blinkDelaySub = 0;


        byte hue = HUE_RED;
        int8_t iDirection = 1;
        int8_t iPos = 0;

        byte marqueeHue = 4;


    public:
        BlinkMuster();
        void setLeds(CRGB* leds);        
        void init();       
       
        void blinkRight();       
        void blinkLeft();

        void drawComet();
        void drawKitt();
        void drawHollywood();
        void drawFullRed(uint8_t brightness);

                

};