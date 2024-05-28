#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define INTERRUPT_PIN PCINT1  // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1           // Interrupt-Pin nach Wahl: PB1 (wie PCINT1) - Pin 6
#define LED_PIN PB4           // PB4 - Pin 3
#define CONTROL_LED PB3
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit


boolean volatile irFired=false;
boolean lightsOn =false;
unsigned long startTime = 0;

byte started = false;





void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(CONTROL_LED, OUTPUT);
  cli();                            // Disable interrupts during setup
  PCMSK |= (1 << INTERRUPT_PIN);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(INT_PIN, INPUT_PULLUP);   // Set our interrupt pin as input with a pullup to keep it stable
  sei();                            //last line of setup - enable interrupts after setup
}

void blinkControll(int times, int  unsigned frequence)
{
  unsigned long start =  micros(); 
  for(int i=0; i< times;i++){
    digitalWrite(CONTROL_LED, HIGH);
    while (micros()-start < frequence);
    digitalWrite(CONTROL_LED, LOW);
  }

}

// This is the interrupt handler called when there is any change on the INT_PIN
// ISR is defined in the headers - the ATtiny85 only has one handler
ISR(PCINT_VECTOR)
{ 
   if (digitalRead(INT_PIN) == LOW) {
    blinkControll(3,50);
   }else{
    blinkControll(3,150);
   }
}




void loop() {  
  cli(); 
  if(lightsOn)
  {         
    digitalWrite(CONTROL_LED, LOW); 
    lightsOn=false;
  }else{
    digitalWrite(CONTROL_LED, HIGH);
    lightsOn=true; 
  }
  sei(); 
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}

