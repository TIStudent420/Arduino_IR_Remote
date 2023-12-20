#ifndef RSW_Control_Unit_H
#define RSW_Control_Unit_H

#include <Arduino.h>

#import <Encoder.h> //Encoder-Bibliothek im Quellcode-Ordner

class RSW_Control_Unit{
public:
  RSW_Control_Unit(int clk_pin, int dt_pin, int sw_pin); //Konstruktor
  void init(); //Initilisierungs funktion

  //Callback für Displaysteuerung
  using Display_Callback = void (*)(int);
  void Checkup(Display_Callback callback);
  
private:
  int Pin_SW;
  Encoder RSW_Encoder;
};

#endif //RSW_Control_Unit_H
