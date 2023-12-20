#include "Pin_defines.h"
/*
 * Pins aus "Pin_defines.h":
 *  - Pin_CLK_RSW - Clock-Pin des Drehschalters
 *  - Pin_DT_RSW - Daten-Pin des Drehschalters
 *  - Pin_SW_RSW - Knopf-Pin des Drehschalters
*/
#include "Control_Unit.hpp"

//Drehschalter-Klasse Initialisieren -> zum Steuern der Ein-/Ausgabe
RSW_Control_Unit Drehschalter(Pin_CLK_RSW,Pin_DT_RSW,Pin_SW_RSW);

void setup() {
  //Serielle Kommunikation initialisieren
  Serial.begin(9600);

  //Initialisierungen des Drehschalters
  Drehschalter.init();

  Serial.println("Hello Munke");
}

void display_control(Display_Commands cmd){
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

void loop() {
  //Überprüft die Eingabe des Drehschalters
  //Per Übergabe einer Funktion, kann der 
  Drehschalter.Checkup(display_control);
}
