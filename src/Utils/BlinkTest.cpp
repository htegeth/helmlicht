#include <Arduino.h>
#include <avr/io.h>

void setup() {
    pinMode(PB4, OUTPUT);

    cli(); // Disable interrupts
    CLKPR = (1<<CLKPCE); // Prescaler enable
    CLKPR = 0x00; // Clock division factor
    sei(); // Enable interrupts

  
}

void loop(){
  digitalWrite(PB4, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(PB4, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
}