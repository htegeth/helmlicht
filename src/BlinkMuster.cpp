#include <BlinkMuster.h>
#include "Control.h"

BlinkMuster::BlinkMuster()
{
}

void BlinkMuster::setLeds(CRGB *leds)
{
    this->leds = leds;
}

void BlinkMuster::setNumberLeds(int numberLeds)
{
    this->numberLeds = numberLeds;
}

void BlinkMuster::init()
{
    ledFragment = numberLeds / 3;
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
    for (int i = numberLeds - ledFragment; i < numberLeds; i++)
    {
        leds[i] = CRGB::CRGB::CRGB::Orange;
        if (Control::hasCodeChanged())
            return;
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
    for (int i = rightBegin - 1; i >= 0; i--)
    {
        leds[i] = CRGB::CRGB::CRGB::Orange;
        if (Control::hasCodeChanged())
            return;
        FastLED.show();
        delay(blinkDelaySub);
    }
    delay(blinkDelayMain);
}



void BlinkMuster::drawComet()
{
    int cometSize = 1;
    hue += deltaHue;
    iPos += iDirection;
    if (iPos == (numberLeds - cometSize) || iPos == 0)
        iDirection *= -1;

    for (int i = 0; i < cometSize; i++)
        leds[iPos + i].setHue(hue);

    // Randomly fade the LEDs
    for (int j = 0; j < numberLeds; j++)
        if (random(10) > 5)
            leds[j] = leds[j].fadeToBlackBy(fadeAmt);
    FastLED.show();
    delay(60);
}

void BlinkMuster::drawKitt()
{
    iPos += iDirection;
    if (iPos == (numberLeds - 1) || iPos == 0)
        iDirection *= -1;

    FastLED.clear();
    leds[iPos].setHue(HUE_RED);
     if ((iPos + 1) < numberLeds)
         leds[iPos + 1].setHue(HUE_RED).fadeToBlackBy(200);
    leds[iPos - 1].setHue(HUE_RED).fadeToBlackBy(200);
    FastLED.show();
    delay(50);
}
