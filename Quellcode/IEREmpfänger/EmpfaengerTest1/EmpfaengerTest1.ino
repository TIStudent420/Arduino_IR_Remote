//Arduino Empfänger Test

#include <IRremote.h>

int irPin = 52; //Pin am Arduino UNO für den IR Receiver

IRrecv irrecv(irPin); //Objekt initialisieren für die IR Übertragung
decode_results results;

void setup() {
  pinMode(irPin, INPUT);  //Den IR Pin als Eingang deklarieren.
  irrecv.enableIRIn(); //Den IR Pin aktivieren
  Serial.begin(9600); //Serielle kommunikation mit 9600 Baud beginnen.
}

void loop() {
  if (irrecv.decode(&results)) { //Wenn etwas gelesen wurde dann...
    if (irrecv.getProtocolString() == "SONY") {
      unsigned long value  = results.value;
      //Ausgabe des Wertes auf die Serielle Schnittstelle.
      Serial.println(char(value));
    }
    irrecv.resume(); // auf den nächsten Wert warten
  }
}