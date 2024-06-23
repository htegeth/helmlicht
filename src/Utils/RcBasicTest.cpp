// ATTiny 85 PINS
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

/* Hier wird der Interupt des ATtiny genutzt um das Signal von ledPin auf High oder LOW zu setzen.
wird anschließend das Kabel vom ATtiny PB4 auf auf PIN2 eines Arduino Uno gesetzt und das 
Example Skript examples/ReceiveDemo_Simple/ReceiveDemo_Simple.ino ausgeführt kann das Remote Signal entrschlüsselt und angezeigt werden
*/

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int ledPin = PB4;
const int interruptPin = PCINT1;
volatile bool event = false;
volatile bool isBurning = false;
volatile int rythM = 10;
volatile long lastChange=0;
volatile long duration = 0;

ISR (PCINT0_vect){
    
    if(isBurning)
    {
        digitalWrite(ledPin, LOW); 
        isBurning=false;                
    }else{
        digitalWrite(ledPin, HIGH); 
        isBurning=true;            
    }      

    // duration= micros()- lastChange;
    // if (abs(duration-320)<100 ) {
    //     event = true;    
    // }
    // lastChange=micros();
 }

void setup() {
    pinMode(ledPin, OUTPUT);
    GIMSK |= (1<<PCIE); // General Interrupt Mask Register
    PCMSK = (1<<PCINT1); // 3 = PCINT3
    lastChange=micros();
    delay(2000);
}

void loop() {
    delay(200);
}