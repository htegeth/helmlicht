#include <BlinkMuster.h>
#include "Control.h"

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
    for (int i = numberLeds-ledFragment; i < numberLeds ;i++ ){
        leds[i] = CRGB::CRGB::CRGB::Orange;
        if(Control::hasCodeChanged()) return;
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
        leds[i] = CRGB::CRGB::CRGB::Orange;
        if(Control::hasCodeChanged()) return;
        FastLED.show();
        delay(blinkDelaySub);  
    }
    delay(blinkDelayMain);
}

bool BlinkMuster::runleft()
{
  leds[0] = CRGB::CRGB::Red;
  FastLED.show();
  boolean repeat= true;
  while (repeat) {
    for (int i =0; i < numberLeds;i++ ){
        if(Control::hasCodeChanged()) return false;
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
  return true;
}

bool BlinkMuster::runright()
{
    leds[numberLeds-1] = CRGB::CRGB::Red;
    FastLED.show();
    boolean repeat= true;
    while (repeat) {
    for (int i =numberLeds-1; i >= 0 ;i-- ){
        if(Control::hasCodeChanged()) return false;
        int luma= leds[i].getLuma();
        if (luma > 0){          
            if( i > 0){              
                leds[i-1] = CRGB::CRGB::Red;
            }else{
            repeat = false;
            }
            FastLED.show();           
            leds[i] = CRGB::CRGB::Black;
            FastLED.show();
            break;
        }
                
    }
    delay(runDelayTime);  
    }
    return true;
}

void BlinkMuster::drawComet()
{
    const byte fadeAmt = 128;
    const int cometSize = 1;
    const int deltaHue  = 4;

    static byte hue = HUE_RED;
    static int iDirection = 1;
    static int iPos = 0;

    hue += deltaHue;

    iPos += iDirection;
    if (iPos == (numberLeds - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        leds[iPos + i].setHue(hue);
    
     //Randomly fade the LEDs
     for (int j = 0; j < numberLeds; j++)
         if (random(10) > 5)
             leds[j] = leds[j].fadeToBlackBy(fadeAmt);  
    FastLED.show();
    delay(60);
}


void BlinkMuster::wawa(){
    if (runleft()) runright();  
}
