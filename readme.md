
# Helmlicht
Das Helmlicht ist für Fahrradhelme von Abus Modell Hud-Y gedacht. Es passt in die dafür vorgesehene Einsparung in der das orginal rücklich eingesteckt wird. 
Es werden für die Beleutung WS2812B eingesetzt die über einen ATTiny angsteuert werden. Zusätzlich wird eine Fernbedienung unterstützt, um eine Blickfunktion 
im Lichtstreifen zu integrieren.

## Schritt für Schritt
1. Fuse des ATtiny richtig setzen über PlatformIO/Project Tasks/Attiny_Helmlich/Platform/Set Fuses

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

## RX Nodule
Der XY-MK-5V ist das Standardmodul für 433Mhz Funkübertragung meist im Set mit dem FS1000A, Der Sender und der Empfäger sind relative primitive Konstruktionen, bei der eine Spule in Schwingung versetzt wird und diese Schwingung beim RX Modul verstärkt an dem Datenpin angelegt wird.
Der XY-MK-5V ist ein Pendlerempfaenger, mit einer sehr geringen Reichweite. Ausserdem scheint er kein sauberes Signal zu liefern, so dass ein Sender in unmittelbarer Entfernung zum Empfänger stehen muss. Desweiteren braucht der Empfänger zwingen mehr als 3V Spannung, um zu funktionieren. 
Besser sind hier Superheterodyne Empfänger die auch bei 3V saubere Ergebisse erzielen. Hervorrangend. der RXB14, dieser hat eine sehr kleine Bauform und arbeitet zuverlässig schon bei 3V und kann damit auch mit einer Knopfzelle betrieben werden. Der Verbrauch würde dabei bei ca. 6.88 mW liegen. Bei einer Kapazität einer Cr2032 von 0,22 Ah wären ein Betrieb von 95 Stunden also ca 4 Tagen Dauerbetrieb möglich.


## Funktionserklärung rc-switch
### ATtiny 
Für den ATtiny wurden extra der Boolean RCSwitchDisableReceiving auf true gesetzt weil angeblich udivmodhi4 fehlt. Allerdings ist dies mit der ATtinycore lib auch nicht nötig. Es funktioniert also auch ohne. Aller dings muss die einbettung in das Interupt Magement geändert werden da der Arduino Befehl attachInterrupt hier nicht funktioniert. Also diese Zeile auskommentieren und RCSwitchDisableReceiving ebenso der Aufruf interruptChange(), da diesem beim ATtiny nicht gibt.

### Signalverarbeitung
Die Herausfoderung bei der Signalverarbeitung ist es zuerst die Störungen herauszufiltern und dann das Signal korrekt zu interpretieren. Dies wird wie folgt gemacht:
- Es wird ein Array vorbereitet, in dem die identifizierten Signale(die dauer dieser) gespeichert werden
- Die Funktion handleInterrupt wird in die Interuptverarbeitung eingehängt.
  - Abstand seit dem letzten Aufruf bestimmen
  - Wenn der Abstand seit dem letzten Aufruf länger als 4300 micros ist (eine Signallücke) dann
    - wird der Cursor für das Array der Signal zurückgesetzt (egal was vorher war)
    - wenn das eine Signallücke ist (am Anfang oder zwischen den Signalen) und diese schon das zweite mal auftritt
      - dann könnte eine ganze Signalkette vorliegen, diese wird an receiveProtocol weitergegeben zum analysiere
    

