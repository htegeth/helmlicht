#include <Arduino.h>
#include <avr/io.h>

void setup() {
    pinMode(PB4, OUTPUT);
}

void loop(){
  digitalWrite(PB4, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(PB4, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
}