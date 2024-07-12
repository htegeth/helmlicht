
# Das Helmlicht
Der Fahrradhelm Modell Hud-Y von Abus ähneln dem eines Roboterkopfes. Als Fan von Filmen wie Robocop defenitiv ein Kaufgrund. Die Helme dieses Modells haben ein Rücklicht integriert, das Leuchten und Blinken kann und das entfernt werden kann! Doch wenn man schon einen Robotorhelm hat und ein Rücklicht vorhanden ist, warum soll es dann nicht aussehen wie die "Augen" der Zylonen aus Battlestar Galactica? Und das Rücklicht könnte auch beim Abbiegen blinken, so wie es Motorräder oder Autos machen.
Um das Umzusetzen, habe ich eine Box für die Ausparung im Helm als 3D Modell konstruiert, in dem ein ATtiny85 arbeitet. Dieser steuert einen WS2812B LED Strip, einen Piezo Summer und lässt sich über ein 433Mhz Empfängermodul steuern.

Mit einer programmierbaren 433Mhz Standardfernbedienung wird das Rücklicht angesteuert und die Fahrrichtung durch Blinken angezeigt. Der Summer gibt das Feedback an den Fahrer, dass der Blinker an ist.


<img src="doc/Vorfuehrung_Offstreet-Tiny.gif" width=700>


# Stückliste
Folgende Teile werden verbaut:
Bauteil               | Beschreibung | Quelle | Kosten
--------              |--------------|------- | -----
Mikroprozessor  | ATTINY 85-20 PU      | [reichelt](https://www.reichelt.de/8-bit-attiny-avr-risc-mikrocontroller-8-kb-20-mhz-dip-8-attiny-85-20-pu-p69299.html) | 1,70€
IC-Sockel             | GS 8P IC-Sockel, 8-polig| [reichelt](https://www.reichelt.de/ic-sockel-8-polig-superflach-gedreht-gs-8p-p8231.html) | 0,30€
Piezo Speaker         | DC-Signalgeber, 85dB | [reichelt](https://www.reichelt.de/dc-signalgeber-85db-2300-hz-3-v-pb12n23mpw03aq-p360872.html)| 0,92€
433Mhz Receiver | 433Mhz Superheterodyne RXB14| [ebay](https://www.ebay.de/itm/263855073600?var=563220548601)|1,19€
Schiebeschalter | Mini Schiebeschalter SS2212F15VG6 3 Pol, 2 Gänge| [ebay](https://www.ebay.de/itm/315307042120?var=613779717314)| 2,20€*
Lipo Lademodul|  USB-C 18650 tp4056 Lithium-Batterie Lademodul | [aliexpress](https://de.aliexpress.com/item/1005005982385924.html)| 1,37€
Lipo Akku| 3,7 V 150-300mAh Lipo-Batterien mit PCM| [aliexpress](https://de.aliexpress.com/item/1005006680244682.html)| 1,43€
LED Strip| WS2812 144LEDs/meter Schwarz IP65, 12mm| [amazon](https://www.amazon.de/dp/B088JPLP2H)| 15,99€*
Magnete | Neodym Magnete 8x2mm| [amazon](https://www.amazon.de/dp/B0CPJ1GJKS)| 6,99€*
JST Stecker |  Micro JST 1,25mm 2 Pin Male & Female| [aliexpress](https://de.aliexpress.com/item/1005004732865407.html)| 2,44€*
PCB Board | PCB Board KitsDoppelseitig| [amazon](https://www.amazon.de/gp/product/B09NDNPF91)| 9,99€*
Funkfernbedienung| Programmierbare Funkfernbedienung 433Mhz| [aliexpress](https://de.aliexpress.com/item/1005006065464456.html)| 3,09€
Sonstiges|Kabel, Filament, Schrauben 
*) Set oder Meterpreise (06/2024)


<img src="doc/PartOverview.jpg" width=700><img src="doc/LED-Strip.jpg" width=700>

Ausserdem sind noch ein 3D-Drucker und ein Lötkolben erforderlich.

# Programmieren

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
    

