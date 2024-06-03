#include <BlinkMuster.h>

BlinkMuster::BlinkMuster()
{
    
}

void BlinkMuster::setLeds(CRGB* leds)
{
    this->leds=leds;
}


void BlinkMuster::setNumberLeds(int numberLeds)
{
    this->numberLeds=numberLeds;
}

void BlinkMuster::init()
{
    ledFragment =  numberLeds/3;
    rightBegin = ledFragment;
    leftBegin = numberLeds - ledFragment;
    blinkDelayMain = 500;
    blinkDelaySub = blinkDelayMain / ledFragment;
}

void BlinkMuster::blinkLeft()
{
    FastLED.clear();
    FastLED.show();
    delay(blinkDelayMain);
    for (int i = 15; i < 21 ;i++ ){
        leds[i] = CRGB::CRGB::CRGB::Yellow;
        FastLED.show();
        delay(blinkDelaySub);  
    }
    delay(blinkDelayMain);
}

void BlinkMuster::blinkRight()
{
    FastLED.clear();
    FastLED.show();
    delay(blinkDelayMain);
    for (int i = rightBegin-1; i >= 0 ;i-- ){
        leds[i] = CRGB::CRGB::CRGB::Yellow;
        FastLED.show();
        delay(blinkDelaySub);  
    }
    delay(blinkDelayMain);
}