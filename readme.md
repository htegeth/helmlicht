
# Helmlicht
Das Helmlicht ist für Fahrradhelme von Abus Modell Hud-Y gedacht. Es passt in die dafür vorgesehene Einsparung in der das orginal rücklich eingesteckt wird. 
Es werden für die Beleutung WS2812B eingesetzt die über einen ATTiny angsteuert werden. Zusätzlich wird eine Fernbedienung unterstützt, um eine Blickfunktion 
im Lichtstreifen zu integrieren.

## Schritt für Schritt
1. Fuse des ATtiny richtig setzen über PlatformIO/Project Tasks/ Attiny_Helmlich/Platform/Set Fuses

# Utils
## BlickTest
Um den Arduino der eingesetzt werden soll zu testen wird dieses simple Programm verwendet. Es steuert eine LED an und lästs diese Blinken. Dies ist ein Smoketest, ob der 
eingesetzt Prozessor funktioniert hinsichtlich Programmierung, Ausführung und Ansteuerung

## RemoteDecoder
Für das Programm werden zwei LEDs und ein 433RX Board benötigt. Zusätzlich noch eine Fernbedienung. Es dient dazu die Codes der Funkfernbedienung auszulesen und zwar so wie der ATTiny diese mit der lib RCSwitch interpretiert. 

# Tipps und Tricks
## Timmings und Clock
https://community.platformio.org/t/attiny-8mhz-wrong-timing-in-delay-fastled-and-neopixel/24992/4
HIer werden Probleme angesprochen, dass der delay nicht rictig fuktioniert weil die CPU unter 1Mhz läuft bei eingestellten 8 
!! Es kann auch ein Grund dafür sein, dass der NEOPiXEL nicht meh rrichtig klappt

Auf dieser Seite gibt es einen Taktrechner: https://www.engbedded.com/fusecalc/
