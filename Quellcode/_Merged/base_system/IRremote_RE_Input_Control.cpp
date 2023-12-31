#include <Arduino.h>
#include "IRremote_RE_Input_Control.hpp"
#include "base_definitions.h"

//Konstrunktor implementieren
RE_Input_Control::RE_Input_Control(int clk_pin, int dt_pin, int sw_pin):Rotary_Encoder_PC1(dt_pin,clk_pin){
  Pin_SW=sw_pin;
}

void RE_Input_Control::Init(){
  pinMode(Pin_SW,INPUT);
  digitalWrite(Pin_SW,HIGH); //Pullup, damit nicht ständig triggert
}

void RE_Input_Control::Checkup(Controls_Callback callback){
  //Zum rauf und runter des Encoder:
  //  - mit einem Step inkementiert der Encoder (drehschalter) um 4 
  //  - dadurch wird mit einem Schritt 4mal inkrementiert
  //  - dadurch würde es 4mal auslösen, wenn man nicht schnell ganug (schneller als der Controller) ist. 
  //  - deshalb wird hier immer mit 4/-4 Verglichen -> das entspricht genau einem Schritt
  //  - Anschließend wird der Zähler zurückgesetzt.
  if(Rotary_Encoder_PC1.read()==4){
    Serial.println("rotation left");//links=rauf
    Rotary_Encoder_PC1.readAndReset();
    //nach_oben-Funktion in der Steuerung/Display-Anwendung
    callback(Display_UP);
    return;
  }
  else if(Rotary_Encoder_PC1.read()==-4){
    Serial.println("rotation right");//rechts=runter
    Rotary_Encoder_PC1.readAndReset();
    //nach_unten-Funktion in der Steuerung/Display-Anwendung
    callback(Display_DOWN);
    return;
  }
  
  if(!digitalRead(Pin_SW)){
    Serial.println("Button Pressed");
    //kurze pause, da knöpfe sehr ungenau sind 
    //-> würde sonst mehrmals auslösen
    delay(200);
    //Auswählen-Funktion in der Steuerung/Display-Anwendung
    callback(Display_OK);
    return;
  }
  return;
}
