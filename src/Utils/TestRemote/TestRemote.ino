/*
   (!) Benutze den Sketch in der Arduino IDE oder schreibe eine eigene platformio.ini dafür.

  Hier können die Signale der Fernbedienung ausgelesen werden, wenn sie dekodiert werden können.
  Bitte daran denken, dass aus Platzgründen das Helmlicht nicht jedes Protokoll unterstützt. 
  Sondern nur das Protokoll 1:
  Pulslänge 350 Mirkosekunden, 31 Pulse als Synchronisation zwischen den Signalen, 1 high Puls 
  and 3 low Pulse für 0 und genau umgekehrt für 1

  Andere Protokolle können abweichen und müssen entweder in BlinkMuster.cpp eingetragen werden 
  oder die Fernbedienung muss neu programmiert werden
  
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

    mySwitch.resetAvailable();
  }
}