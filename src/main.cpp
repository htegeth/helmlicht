#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define INTERRUPT_PIN PCINT1  // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1           // Interrupt-Pin nach Wahl: PB1 (wie PCINT1) - Pin 6
#define LED_PIN PB4           // PB4 - Pin 3
#define CONTROL_LED PB3
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit

// All times in microseconds
#define Min_Gap_Time 5000 // nominal = 5600
#define Max_Gap_Time 6200 // nominal = 5600
#define One_Bit_Time 120 // nominal = 188
#define Zero_Bit_Time 500 // nominal = 564


boolean volatile irFired=false;
boolean lightsOn =false;
unsigned long startTime = 0;
int pulseWidth;
byte started = false;

byte RF_Bit_Count;
byte RF_Byte_Count;
byte RF_Byte = 0;
byte RF_Message[] = {0, 0, 0}; // 24 bits



void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(CONTROL_LED, OUTPUT);
  cli();                            // Disable interrupts during setup
  PCMSK |= (1 << INTERRUPT_PIN);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(INT_PIN, INPUT_PULLUP);   // Set our interrupt pin as input with a pullup to keep it stable
  sei();                            //last line of setup - enable interrupts after setup
}

// This is the interrupt handler called when there is any change on the INT_PIN
// ISR is defined in the headers - the ATtiny85 only has one handler
ISR(PCINT_VECTOR)
{ 
  
   if (digitalRead(INT_PIN) == LOW) {
    startTime = micros();
  }else{
     if (startTime != 0) {
      //calculate the pulse width
      pulseWidth = ((volatile int)micros() - startTime);
      //clear the timer
      startTime = 0;

      // Now check for valid message
      if (pulseWidth < Max_Gap_Time) {
        if (started == true) {
          if (pulseWidth > Zero_Bit_Time) {
            // bit = 0
            RF_Bit_Count--; // bits received MSB first
            bitClear(RF_Message[RF_Byte_Count], RF_Bit_Count);
            if (RF_Bit_Count == 0) {
              RF_Byte_Count++;
              RF_Bit_Count = 8;
            }
          }
          else if (pulseWidth > One_Bit_Time) {
            // bit = 1
            RF_Bit_Count--; // bits received MSB first
            bitSet(RF_Message[RF_Byte_Count], RF_Bit_Count);
            if (RF_Bit_Count == 0) {
              RF_Byte_Count++;
              RF_Bit_Count = 8;
            }
          }
          else { // bad bit
            started = false;
          }
        } // Started
        
        else if (pulseWidth > Min_Gap_Time) {
          // start of message
          started = true;
          RF_Byte_Count = 0;
          RF_Bit_Count = 8;
        }
      }
      else { // invalid message
        started = false;
      }


     }
  }

}

void loop() {  
  if (RF_Byte_Count > 1)
  {
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
  }
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}

