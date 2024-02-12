# Arduino_IR_Remote

Entwurf einer Universellen IR-Fernbedienung mit dem Arduino

 - Steuerung über Joystick,
 - Menue/auswahl über LCD-Display,
 - Empfangen des IR-Signals einer Fernbedienung 
   -> Konfiguration der Signale zum Senden (temporär gespeichert)
   -> Speichern (permanent?)
 - Senden eines IR-Signals an Gerät
   -> vorher bzw. zur Laufzeit analysierte Signale wiedergeben

Ansteuerung über Raspberry (*NICHT* teil dieser Belegarbeit)
 - Datenbus: I2C
 - Abspeicherung der Möglichen Sende-Signale
 - übergeben dieser Codes zum ansteuren der Geräte