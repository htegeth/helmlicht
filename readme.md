
# Helmlicht
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

# Programmierung
Für die Programmierung des ATtiny benötigt man ein Programmiergerät oder ein Arduino Board. Setzt man den Attiny auf ein Breadboard und verwendte den Arduino als ISP Programmer, können an den Anschlüssen des Attiny zugleich auch die später zu verbauenden Module getestet werden. Es ist nicht notwenig, den LED Strip, das Funkmodul oder auch den Piezo Summer beim Programmieren zu entfernen. Lässt man alles verbaut kann soft man will die Programmierung wiederholt werden. 

1. Vorbereitung des Arduino als ISP Programmer
2. Setzen der Fuse des ATtiny 
3. Build und Upload des Codes

## Vorbedreitung des Arduino Boards und des ATtiny
Der Code um den Arduino als ISP nutzen zu können ist Teil der Examples der Arduino IDE: https://www.arduino.cc/en/software
Dazu wird das Arduino Board über USB mit dem Rechner verbunden, und mit dem Skript File/Examples/11.ArduinoISP programmiert ([Arduino Examples](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/))

Der Ardino wird bemäß Pin Layout angeschlossen:

<img src="doc/ISP-Schaltung.png" width=700>

Nicht vergessen: Sollte der Arduino erneut programmiert werden muss der Kondensator entfernt werden.

Falls direkt getestet werden soll ob die Schaltung auf korrekt programmiert wurde können alle später verbauten Teile angeschlossen werden um die Korrektheit zu prüfen.

<img src="doc/ISP-Schaltung-Teststand.png" width=700>

Der angeschlossene Piezo Buzzer wird jetzt beim Programmiervorgang einige Geräusche machen. Davon sollte man sich nicht irritieren lassen, der Programmiervorgang wird trotzdem erfolgreich sein.

## Programmierung über PlatformIO
Nachdem der Arduino als ISP programmiert wurde, kann die Arduino IDE geschlossen werden. Sie wird im Projekt nicht mehr benötigt. Statt dessen wird Visual Studio Code eingesetzt mit dem Plugin PlatformIO.
- Download und install von [VS Code](https://code.visualstudio.com/download)
- PlatformIO IDE als Plugin installieren
- Arduino für Visual Studio Code als Plugin installieren
- Korrekten Port einstellen und in platformio.ini unter upload_port eintragen
- Fuse Einstellung für den ATTiny85
- Upload durchführen

In der Ini-Datei platmormio.ini wird nun die Kofiguration für den ATTiny85 eingetragen wie in [platfomio.org ](https://docs.platformio.org/en/latest/boards/atmelavr/attiny85.html#) beschrieben. Für das Projekt sind bereits alle notwendige Einstellungen festgelegt worden. Lediglich der Port muss noch eingetragen werden der bei Windows im Gerätemanager unter Ports zu finden ist und bei Linux über <code>ls /dev/tty*</code> angezeigt wird.

Der ATtiny muss bei 8Mhz betrieben werden sonst versagt die FastLED Bibliothek ihren Dienst. Damit trotzdem das Timing korrekt funktfunktioniert muss der CKDIV8=0 deaktiviert sein. Dazu wird die lfuse auf 0xE2 gesetzt. Um diesen Wert zu setzen muss unter
<code>PLATFORMIO(Ameisenkopf linke Steuerungsleiste)/Platform/ Set Fuse</code> per Klick ausgeführt werden.

Wenn das alles erfolgreich war kann der Code den Mircocontroller hochgeladen werden. Dazu auf den winzigen Pfeil nach rechts ganz unten klicken.

Im Terminal sollte der Upload mit Status SUCCESS beendet werden.

# Fernbedienung
Als Steuerung des Helmlichtes wird eine programmierbare 433Mhz (oder 315Mhz - in DE obsolet)  Fernbedienung verwendet. In der Regel werden diese Fernbedienungen schon vorprogrammiert geliefert. Ist dies nicht der Fall oder der Fernbedienungscode ein anderer als im Sourcecode der <code>Main.class</code> hinterlegt:
```cpp
// Fernbedienungscodes. Ausgelesen über RCSwitch.getReceivedValue()
const unsigned long taste1 = 753832;
const unsigned long taste2 = 753828;
const unsigned long taste3 = 605660;
const unsigned long taste4 = 605665;
```
muss die Fernbedienung programmiert werden. Um dies zu tun, wird eine weiteres Modul benötigt. Ein Sendemodul wie das MX-FS-03V reicht dafür aus. Zum Versenden kann der auch hier als Grundlage verwendet Code des Projektes rc-switch [rc-switch](https://github.com/sui77/rc-switch/) verwendet werden. Dazu kann man die Arduino IDE starten ein neues Skript öffnen und für <code>taste1</code> folgenden Code in den Sketch kopieren:
```cpp
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  //Modul Data an Arduino PIN10
  mySwitch.enableTransmit(10);  
}

void loop() {
  mySwitch.send(753832, 24);
}
```
Den Arduino nun starten und die Fernbedienung den Code lernen lassen. Bei den meisten aus China stammenden lernenden Fernbedienungen muss dazu in der Lernvorgang gestartet werden z.B. durch gleichzeitiges Drücken der Taste A und B bis die Bestätigungs LED dreimal blinkt anschließend B drücken. Dannach die Fernbedienung in die Nähe des Sendemoduls halten und den gewünschten Knopf solange gedrückt halten bis aus dem Blinken der Kontrol-LED ein Flackern geworden ist.
Anschließend im Sketch den Code der Taste ändern, auf den Arduino laden und die nächste Taste gedrückt halten.

# Montage
Für die Montage muss die Helmlicht Box ausgedruckt werden. Auch wenn PLA als Druckmatrial zunächst ausreicht wäre für den intensiven Outdoor Einsatz ASA eventuell geigneter. Allerdings ist der Deckel der Box nur verpresst montiert und nicht komplett wasserdicht. 

Das PCB Board wird auf 18 Loch lang und 6 Loch hoch gekürzt. Es lässt sich zusägen oder es werden mit einem Cutter Messer die Bruchkanten eingeritzt um anschließend mit einer Zange die überstehenden Bereiche abzuknicken.
Liegt die Box mit der Aussparrung nach vorne zeigend vor einem, wird auf der linken Seite das Akku-Lademodul in die Ausparrung geklemmt. Der Schiebeschalter wird mit den ausgedruckten Nieten an der Box verschmolzen. Dazu die Nieten durch die Montagelöcher schieben und mit einem Lötkolben von Aussen verschmelzen. Vorher den Schalter und das Lademodul mit Kabeln und Steckern verbinden. Auf der Linken Seite sollte nun noch soviel Platz sein, dass der Akku so in den Raum gelegt werden kann, dass der Decke sich schließen lässt.




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

Auf dieser Seite gibt es einen Taktrechner: https://www.engbedded.com/fusecalc/ und noch mehr. Es gibt hier einige Einstellungen die über Fuse geregelt werden und die das Verhalten der ATtiny vor dem Startup regeln.

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
    
