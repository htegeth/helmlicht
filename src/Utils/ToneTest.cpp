//Wird nicht wirklich benötigt da der tiny auch tone() aus der Aurdiono Bibliothek richtig umsetzt, allerdings nur auf PWM fähigen PINS
#include <Arduino.h>

#define TONE_PIN 0



void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ 
  int  x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));  
  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }  
}


void setup()
{
    pinMode(TONE_PIN, OUTPUT);
}

void loop()
{
    beep(TONE_PIN,200,500);
    delay(2000);
}