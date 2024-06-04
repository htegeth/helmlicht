#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <atRcRwitch.h>
#include <FastLED.h>
#include "BlinkMuster.h"

#define INTERRUPT_PIN PCINT1  // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1           // Interrupt-Pin nach Wahl: PB1 (wie PCINT1) 
#define LED_PIN PB3           // LED für das Feedback für enfnagene Nachrichten
#define CONTROL_LED PB2       // LED um anzuzeigen welcher Knopf der Fernbedienung gedrückt wurde
#define TONE_PIN 0
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit
#define NUM_LEDS 21
#define DATA_PIN 4

boolean volatile irFired=false;
boolean lightsOn =false;
unsigned long startTime = 0;
unsigned int currentCode=0;

//Fernbedienungscodes. Ausgelesen aus dem RemoteDecoder
const unsigned int taste1 = 32936;
const unsigned int taste2 = 32932;

byte started = false;
RCSwitch mySwitch = RCSwitch();
CRGB leds[NUM_LEDS];
BlinkMuster blinker = BlinkMuster();



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

void setup() {
  pinMode(TONE_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  blinker.setLeds(leds);
  blinker.setNumberLeds(NUM_LEDS);
  blinker.init();
  pinMode(LED_PIN, OUTPUT);
  pinMode(CONTROL_LED, OUTPUT);
  cli();                            
  PCMSK |= (1 << INTERRUPT_PIN);    
  GIMSK |= (1 << PCIE);             
  pinMode(INT_PIN, INPUT_PULLUP);   
  mySwitch.enableReceive(0);
  sei();                            
}

void blinkControll(int times, int  unsigned frequence)
{  
  for(int i=0; i< times;i++){
    digitalWrite(CONTROL_LED, HIGH);
    delay(frequence);
    digitalWrite(CONTROL_LED, LOW);
    delay(frequence);
  }
}

ISR(PCINT_VECTOR)
{ 
   mySwitch.handleInterrupt();
}

void loop() {
  if (mySwitch.available()) {    
    unsigned int code= mySwitch.getReceivedValue();    
    currentCode = code;  
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);      
    delay(100);
    mySwitch.resetAvailable();  
  }

  //delay (500);
  
  switch (currentCode)
  {
    case taste1:   
      //blinkControll(2,50);      
      tone(TONE_PIN,150,200);
      blinker.blinkLeft();
      break;
    case taste2:
      //blinkControll(4,50);
      tone(TONE_PIN, 50,200);
      blinker.blinkRight();
      break;
    default:
      blinker.wawa();
      break;
  }
    
}
