#include <BlinkMuster.h>

BlinkMuster::BlinkMuster()
{ }

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

void BlinkMuster::runleft()
{
  leds[0] = CRGB::CRGB::Red;
  FastLED.show();
  boolean repeat= true;
  while (repeat) {
    for (int i =0; i < numberLeds;i++ ){
        int luma= leds[i].getLuma();
        if (luma > 0){
          leds[i] = CRGB::CRGB::Black;
          if( i != numberLeds-1){              
              leds[i+1] = CRGB::CRGB::Red;
          }else{
            repeat = false;
          }
          FastLED.show();
          break;
        }
                
    }
    delay(runDelayTime);  
  }
}

void BlinkMuster::runright()
{
    leds[numberLeds-1] = CRGB::CRGB::Red;
    FastLED.show();
    boolean repeat= true;
    while (repeat) {
    for (int i =numberLeds-1; i >= 0 ;i-- ){
        int luma= leds[i].getLuma();
        if (luma > 0){          
            if( i > 0){              
                leds[i-1] = CRGB::CRGB::Red;
            }else{
            repeat = false;
            }
            FastLED.show();
            delay(20);
            leds[i] = CRGB::CRGB::Black;
            FastLED.show();
            break;
        }
                
    }
    delay(runDelayTime);  
    }
}
