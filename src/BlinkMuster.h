#include <FastLED.h>

class BlinkMuster
{
    private:
        int numberLeds;
        CRGB* leds;
        int ledFragment = 0;
        int rightBegin = 0;
        int leftBegin = 0;
        int blinkDelayMain = 0;
        int blinkDelaySub = 0;

    public:
        BlinkMuster();
        void setLeds(CRGB* leds);
        void setNumberLeds(int numberLeds);
        void init();
       
        void blinkRight();
        void blinkLeft();

};