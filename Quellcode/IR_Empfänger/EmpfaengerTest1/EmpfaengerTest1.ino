//Arduino Empfänger Test

#include <IRremote.h>

#define IR_RECV_PIN 2 //Pin am Arduino UNO für den IR Receiver
#define RECV_FEED_PIN 5

IRrecv irrecv(IR_RECV_PIN); //Objekt initialisieren für die IR Übertragung
decode_results results;

void setup() {
  pinMode(IR_RECV_PIN, INPUT);  //Den IR Pin als Eingang deklarieren.
  irrecv.enableIRIn(); //Den IR Pin aktivieren
  Serial.begin(9600); //Serielle kommunikation mit 9600 Baud beginnen.
  pinMode(RECV_FEED_PIN,OUTPUT);
  digitalWrite(RECV_FEED_PIN,LOW);
}

void loop() {
  if (irrecv.decode(&results)) { //Wenn etwas gelesen wurde dann...
      digitalWrite(RECV_FEED_PIN,HIGH);
      delay(2);
      digitalWrite(RECV_FEED_PIN,LOW);
      
      unsigned long value  = results.value;
      //Ausgabe des Wertes auf die Serielle Schnittstelle.
      Serial.print(char(value));
      
    if (irrecv.getProtocolString() == "SONY") {

    }
    irrecv.resume(); // auf den nächsten Wert warten
  }
}
