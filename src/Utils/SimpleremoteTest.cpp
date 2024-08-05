#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <atRcRwitch.h>


#define INTERRUPT_PIN PCINT1     // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1              // Interrupt-Pin nach Wahl: PB1 (wie PCINT1)
#define CONTROL_LED1 PB3         // LED für das Feedback für enfnagene Nachrichten
#define CONTROL_LED2 PB4         // LED um anzuzeigen welcher Knopf der Fernbedienung gedrückt wurde
#define PCINT_VECTOR PCINT0_vect // This step is not necessary - it's a naming thing for clarit

boolean lightsOn = false;
unsigned long startTime = 0;
unsigned long currentCode = 0;

// Fernbedienungscodes. Ausgelesen über RCSwitch.getReceivedValue()
const unsigned long taste1 = 753832;
const unsigned long taste2 = 753828;

byte started = false;
RCSwitch mySwitch = RCSwitch();

void setup()
{
  pinMode(CONTROL_LED1, OUTPUT);
  pinMode(CONTROL_LED2, OUTPUT);
  cli();
  PCMSK |= (1 << INTERRUPT_PIN);
  GIMSK |= (1 << PCIE);
  pinMode(INT_PIN, INPUT_PULLUP);
  mySwitch.enableReceive(0);
  sei();
}

void blinkControll(uint8_t pin, int times, int unsigned frequence)
{
  for (int i = 0; i < times; i++)
  {

    digitalWrite(pin, HIGH);
    delay(frequence);
    digitalWrite(pin, LOW);
    delay(frequence);
  }
}

ISR(PCINT_VECTOR)
{
  mySwitch.handleInterrupt();
}

void loop()
{
  if (mySwitch.available())
  {
    unsigned long code = mySwitch.getReceivedValue();
    currentCode = code;
    mySwitch.resetAvailable();
  }

  // delay (2000);
  switch (currentCode)
  {
  case taste1:
    blinkControll(CONTROL_LED1, 30, 100);
    break;
  case taste2:
    blinkControll(CONTROL_LED2, 30, 100);
    break;
  default:
    break;
  }
}
