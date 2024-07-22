#include <FastLED.h>

   
        
class BlinkMuster
{
     private:
        const byte fadeAmt = 128;
        //const int cometSize = 1;
        const int8_t deltaHue  = 4;


        //const int defaultDelay = 50;
        const int runDelayTime = 50;
        int8_t numberLeds;
        CRGB* leds;
        int8_t ledFragment = 0;
        int8_t rightBegin = 0;
        int8_t leftBegin = 0;
        int blinkDelayMain = 0;
        int blinkDelaySub = 0;

        byte hue = HUE_RED;
        int8_t iDirection = 1;
        int8_t iPos = 0;


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

        void drawComet();

        void drawKitt();

                

};