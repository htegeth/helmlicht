#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <atRcRwitch.h>

#define INTERRUPT_PIN PCINT1  // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1           // Interrupt-Pin nach Wahl: PB1 (wie PCINT1) - Pin 6
#define LED_PIN PB3           // PB4 - Pin 3
#define CONTROL_LED PB4
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit


boolean volatile irFired=false;
boolean lightsOn =false;
unsigned long startTime = 0;
unsigned int currentCode=0;

unsigned int taste1 = 32936;

byte started = false;

RCSwitch mySwitch = RCSwitch();




void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(CONTROL_LED, OUTPUT);
  cli();                            // Disable interrupts during setup
  PCMSK |= (1 << INTERRUPT_PIN);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(INT_PIN, INPUT_PULLUP);   // Set our interrupt pin as input with a pullup to keep it stable
  mySwitch.enableReceive(0);
  sei();                            //last line of setup - enable interrupts after setup
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



// This is the interrupt handler called when there is any change on the INT_PIN
// ISR is defined in the headers - the ATtiny85 only has one handler

ISR(PCINT_VECTOR)
{ 
   mySwitch.handleInterrupt();
}



void blinkZiffer(unsigned int zahl){
  int ziffer=0;
  while (zahl != 0) {
    delay(1000);
    blinkControll(3,50);
    delay(1000);
    ziffer = zahl % 10;    
    blinkControll(ziffer,300);
    zahl /= 10;
    delay(500);
  }
}

void blinkBinar(unsigned int zahl){
  for (int i = 0; i < sizeof(int) * 8; ++i) {
        int bit = (zahl >> i) & 1;
        if (bit==0){
          blinkControll(1,100);          
        }else{
          blinkControll(2,100);   
        }
        delay(2000);
    }

    
}




void loop() {
 
 
  if (mySwitch.available()) {    
    unsigned int code= mySwitch.getReceivedValue();    
    currentCode = code;  
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);

      
    //blinkZiffer(code);     
    delay(2000);  
  }

  if (currentCode == taste1){
    blinkControll(5,50);
    blinkControll(2,200);
    blinkControll(5,50);
    blinkControll(2,200);
  }
  

    
}

   
   
  
  


