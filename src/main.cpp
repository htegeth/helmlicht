// ATTiny 85 PINS
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//

#include <Arduino.h>
#include <atRcRwitch.h>
#include <FastLED.h>
#include "BlinkMuster.h"
#include "Control.h"
#include <EEPROM.h>

#define INTERRUPT_PIN PCINT1 // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1          // Interrupt-Pin nach Wahl: PB1 (wie PCINT1)
#define LED_PIN PB3          // LED für das Feedback für enfnagene Nachrichten
#define CONTROL_LED PB2      // LED um anzuzeigen welcher Knopf der Fernbedienung gedrückt wurde
#define TONE_PIN 0
#define PCINT_VECTOR PCINT0_vect // This step is not necessary - it's a naming thing for clarit
#define NUM_LEDS 23
#define DATA_PIN 4

boolean lightsOn = false;

// Seltsam, wenn currentCode long ist, liefert  Control.hasCodeChanged() zu oft true. Bei typ int ist das kein Problem
unsigned int currentCodeMain = 0;

// Fernbedienungscodes. Ausgelesen über RCSwitch.getReceivedValue()
//    _________ 
//  |     =     |
//  | (1)   (2) |
//  |           | 
//  | (3)   (4) |
//  |           |
//  |           |
//    _________   
const unsigned long taste1 = 753832;
const unsigned long taste2 = 753828;
const unsigned long taste3 = 753826;
const unsigned long taste4 = 753825;

RCSwitch mySwitch = RCSwitch();
CRGB leds[NUM_LEDS];
BlinkMuster blinker = BlinkMuster();

//const int8_t max_mode =2;
static int8_t mode = 0;
static unsigned int lastTaste3Pressed=0;

void beep(unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
  int x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }
}

void setup()
{
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
  mode=EEPROM.read(0);
}

void blinkControll(int times, int unsigned frequence)
{
  for (int i = 0; i < times; i++)
  {
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

void runBacklightAnimation(){
    switch (mode)
    {
    case 1:
      blinker.drawComet();
      break;
    default:
      blinker.drawKitt();            
    }
    //TODO: 
    //full read
    //dimming red LED
}

void loop()
{


  if (mySwitch.available())
  {    
    currentCodeMain = (int)mySwitch.getReceivedValue();       
    mySwitch.resetAvailable();
  }

  switch (currentCodeMain)
  {
  case (int)taste1:
    tone(TONE_PIN, 150, 200);
    blinker.blinkLeft();
    break;
  case (int)taste2:
    tone(TONE_PIN, 50, 200);
    blinker.blinkRight();
    break; 
  case (int)taste3: // nächsten Blinkmode auswählen    
    if((millis()-lastTaste3Pressed) < 160 ) break;   //Bester Kompromiss um ein schnelles Switchen zu verhindern 
    if(++mode>1) mode=0;     
    currentCodeMain=0;
    EEPROM.write(0,mode);
    lastTaste3Pressed=millis();   
    break; 
  default:
    runBacklightAnimation();
    break;
  }
}
