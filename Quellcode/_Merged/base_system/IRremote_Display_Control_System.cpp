#include <Arduino.h>
#include "base_definitions.h"
#include "IRremote_Display_Control_System.hpp"

//Konstruktor implementieren
Display_Control_System::Display_Control_System(){}

void Display_Control_System::init(){}

void Display_Control_System::control(Display_Commands cmd){
  switch (cmd){
    case Display_UP:{
      Serial.println("UP");
      break;
    }
    case Display_DOWN:{
      Serial.println("DOWN");
      break;
    }
    case Display_OK:{
      Serial.println("OK");
      break;
    }
    default :
      break;
  }
}
