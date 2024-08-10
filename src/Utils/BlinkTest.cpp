#include <Arduino.h>
// Smoketest
// Einfacher Arduino Blink Sketch um zu testen, ob der Build, der Programmer des ATtiny und der ATtiny selbst funktionieren.
//

//                                 +-\/-+
//                 Ain0 (D5) PB5  1|    |8  Vcc
//                 Ain3 (D3) PB3  2|    |7  PB2 (D2) Ain1
//                 Ain2 (D4) PB4  3|    |6  PB1 (D1) pwm1                 
//                           GND  4|    |5  PB0 (D0) pwm0    <===  #LED (+)
//                                 +----+


void setup() {
    pinMode(PB0, OUTPUT);
}

void loop(){
  digitalWrite(PB0, HIGH); 
  delay(1000);                   
  digitalWrite(PB0, LOW);   
  delay(1000);  
}