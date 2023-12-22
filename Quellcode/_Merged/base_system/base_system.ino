#include "base_definitions.h" //Pin-definitionen, Enum für Displayschnittstelle
#include "IRremote_RE_Input_Control.hpp" //Drehschalter
#include "IRremote_Display_Control_System.hpp" //Display
#include "IRremote_Sensor_Actor_System.hpp" //Sender / Empfänger
 
//Drehschalter-Klasse Initialisieren -> zum Steuern der Ein-/Ausgabe
RE_Input_Control Drehschalter(Pin_RE_CLK, Pin_RE_DT, Pin_RE_SW);
//Display-Klasse Initialisieren (mit Pins)
Display_Control_System Display(Pin_LCD_RS,Pin_LCD_E,Pin_LCD_D4,Pin_LCD_D5,Pin_LCD_D6,Pin_LCD_D7);
//IR_Sensor initialisieren
Sensor_Actor_System IR_System(Pin_IR_RECV,Pin_IR_RECV_FEEDBACK,Pin_IR_LED,Pin_IR_LED_FEEDBACK);

void setup() {
  //Serielle Kommunikation initialisieren
  Serial.begin(9600);

  //Display setup
  Display.Init();
  //Initialisierungen/Setup des Drehschalters
  Drehschalter.Init();
  //Initialisierungen/Setup des Empfängers/des Senders
  IR_System.Init();

  Serial.println("Hello Munke");
}

//Diese Funktion wird als callback an den Drehschalter übergeben
// -> wöllte ich die Member-Funktion der Display-Klasse übergeben,
//   müsste ich diese ebenfalls in der Drehschalter-Klasse implementieren
//     -> das würde gegen das Prinzip der unabhängigkeit der Module untereinander verstoßen
void display_callback_layer(Display_Commands cmd){
  Display.control(cmd);
}

void loop() {
  //Überprüft die Eingabe des Drehschalters
  //Per Übergabe einer Funktion, kann der
  Drehschalter.Checkup(display_callback_layer);
  
  //Überprüft den IR-Sensor
  IR_System.Recive();
}
