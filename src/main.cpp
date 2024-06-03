#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <atRcRwitch.h>
#include <BlinkMuster.h>

#define INTERRUPT_PIN PCINT1  // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1           // Interrupt-Pin nach Wahl: PB1 (wie PCINT1) - Pin 6
#define LED_PIN PB3           // PB4 - Pin 3
#define CONTROL_LED PB4
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit


const int anzahlLeds=20;
boolean volatile irFired=false;
boolean lightsOn =false;
unsigned long startTime = 0;
unsigned int currentCode=0;
CRGB leds[anzahlLeds];

const unsigned int taste1 = 32936;
const unsigned int taste2 = 32932;

byte started = false;
RCSwitch mySwitch = RCSwitch();
BlinkMuster blinkMuster = BlinkMuster(leds,anzahlLeds);




void setup() {
  
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

  delay (1000);
  switch (currentCode)
  {
    case taste1:   
      blinkControll(1,200);
      break;
    case taste2:
      blinkControll(2,200);
      break;
    default:
      break;
  }
    
}

   
   
  
  


