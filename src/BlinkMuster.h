#include <FastLED.h>

class BlinkMuster
{
    private:
        const int defaultDelay = 50;
        const int runDelayTime = defaultDelay;
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

        /**
         * liefert false wenn die methode unterbrochen wurde
        */
        bool runleft();
        /**
         * liefert false wenn die methode unterbrochen wurde
        */
        bool runright();

        void wawa();

                

};