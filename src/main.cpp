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
#include <EEPROM.h>

#define INTERRUPT_PIN PCINT1 // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1          // Interrupt-Pin nach Wahl: PB1 (wie PCINT1)
#define LED_PIN PB3          // LED für das Feedback für enfnagene Nachrichten
#define CONTROL_LED PB2      // LED um anzuzeigen welcher Knopf der Fernbedienung gedrückt wurde
#define PCINT_VECTOR PCINT0_vect // This step is not necessary - it's a naming thing for clarit
#define NUM_LEDS 23
#define DATA_PIN 4

// Anzhal der zulässigen maxmialmodes
#define MAX_MODES 4

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

//Diese Werte werden durch die Build Paramter von platfomio.ini gesetzt.
const unsigned long taste1 = TASTE1_CODE;
const unsigned long taste2 = TASTE2_CODE;
const unsigned long taste3 = TASTE3_CODE;
const unsigned long taste4 = TASTE4_CODE;

RCSwitch mySwitch = RCSwitch();
CRGB leds[NUM_LEDS];
BlinkMuster blinker = BlinkMuster();

static int8_t mode = 0;
static unsigned long lastTaste3Pressed=0;

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
    case 2:
      blinker.drawHollywood();
      break;
    case 3:
      blinker.drawFullRed(150);
      break;   
    case 4:
      blinker.drawFullRed(200);
      break;
    default:      
      blinker.drawKitt();                  
    }
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
    blinker.setBlinkLeft();
    break;
  case (int)taste2:
    blinker.setBlinkRight();
    break; 
  case (int)taste3: // nächsten Blinkmode auswählen       
    if((millis()-lastTaste3Pressed) > 250 ){   
      tone(TONE_PIN, 200, 50);
      if(++mode>MAX_MODES) mode=0;
      EEPROM.write(0,mode);
      runBacklightAnimation();                                
    }
    lastTaste3Pressed=millis();  
    currentCodeMain=0;    
    break;
  default:
    runBacklightAnimation();
    break;
  }
}
