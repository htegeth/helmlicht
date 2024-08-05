#include <BlinkMuster.h>

BlinkMuster::BlinkMuster()
{
}

void BlinkMuster::setLeds(CRGB *leds)
{
    this->leds = leds;
}


void BlinkMuster::blinkLeft()
{
    FastLED.clear();
    FastLED.show();
    delay(BLINK_DELAY_MAIN);
    for (int i = NUM_LEDS - LED_FRAGMENT; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB::CRGB::CRGB::Orange;
        FastLED.show();
        delay(BLINK_DELAY_SUB);
    }
    delay(BLINK_DELAY_MAIN);
}

void BlinkMuster::blinkRight()
{
    FastLED.clear();
    FastLED.show();
    delay(BLINK_DELAY_MAIN);
    for (int i = RIGHT_BEGIN - 1; i >= 0; i--)
    {
        leds[i] = CRGB::CRGB::CRGB::Orange;
        FastLED.show();
        delay(BLINK_DELAY_SUB);
    }
    delay(BLINK_DELAY_MAIN);
}



void BlinkMuster::drawComet()
{
    int cometSize = 1;
    hue += deltaHue;
    iPos += iDirection;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;

    for (int i = 0; i < cometSize; i++)
        leds[iPos + i].setHue(hue);

    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(10) > 5)
            leds[j] = leds[j].fadeToBlackBy(FADEAMT);
    FastLED.show();
    delay(60);
}

void BlinkMuster::drawKitt()
{
    iPos += iDirection;
    if (iPos == (NUM_LEDS - 1) || iPos == 0)
        iDirection *= -1;

    FastLED.clear();
    leds[iPos].setHue(HUE_RED).fadeLightBy(0);
    if ((iPos + 1) < NUM_LEDS)
         leds[iPos + 1].setHue(HUE_RED).fadeToBlackBy(150);
    leds[iPos - 1].setHue(HUE_RED).fadeToBlackBy(150);
    FastLED.show();
    delay(43);
}

void BlinkMuster::drawHollywood()
{
    (marqueeHue < 255) ? marqueeHue+=4:0;
    byte newHue = marqueeHue;
    
    CRGB c;
    for (int i = 0; i < (NUM_LEDS + 1) / 2; i ++)
    {   
        leds[i]=  c.setHue(newHue);
        leds[NUM_LEDS - 1 - i]=  leds[i];
        (newHue < 255) ? newHue+=8: newHue=0;
    }    
    leds[random(NUM_LEDS)].setColorCode(CRGB::White).maximizeBrightness();   
    FastLED.show();
    delay(50);          
}

void BlinkMuster::drawFullRed(uint8_t brightness){
    for (int i=0; i< NUM_LEDS; i++)
    {
        leds[i] = CRGB::Red;
        leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    delay(50);  
}