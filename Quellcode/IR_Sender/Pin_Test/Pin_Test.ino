#include <IRremote.h>

#define IR_PIN 3

void setup() {
  Serial.begin(0);
  //Pinmodus einstellen
  pinMode(IR_PIN,OUTPUT);
  Serial.print(F("Send IR signals at pin "));
  Serial.println(IR_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:

}
