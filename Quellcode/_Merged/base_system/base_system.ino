#include "base_definitions.h" //Pin-definitionen, Enum für Displayschnittstelle
#include "IRremote_RE_Input_Control.hpp"
#include "IRremote_Display_Control_System.hpp"
#include "IRremote_IR_Reciver.hpp"

//Drehschalter-Klasse Initialisieren -> zum Steuern der Ein-/Ausgabe
RE_Input_Control Drehschalter(Pin_RE_CLK, Pin_RE_DT, Pin_RE_SW);
//Display-Klasse Initialisieren
Display_Control_System lcd_display;
//IR_Sensor initialisieren
IR_Revicer IR_Sensor;

void setup() {
  //Serielle Kommunikation initialisieren
  Serial.begin(9600);

  lcd_display.init();
  //Initialisierungen/Setup des Drehschalters
  Drehschalter.Init();
  //Initialisierungen/Setup des Empfängers
  IR_Sensor.Init();
  Serial.println("Hello Munke");
}

//Diese Funktion wird als callback an den Drehschalter übergeben
// -> wöllte ich die Member-Funktion der Display-Klasse übergeben,
//   müsste ich diese ebenfalls in der Drehschalter-Klasse implementieren
//     -> das würde gegen das Prinzip der unabhängigkeit der Module untereinander verstoßen
void display_callback_layer(Display_Commands cmd){
  lcd_display.control(cmd);
}

void loop() {
  //Überprüft die Eingabe des Drehschalters
  //Per Übergabe einer Funktion, kann der
  Drehschalter.Checkup(display_callback_layer);
  //Überprüft den IR-Sensor
  IR_Sensor.Recive();
}
