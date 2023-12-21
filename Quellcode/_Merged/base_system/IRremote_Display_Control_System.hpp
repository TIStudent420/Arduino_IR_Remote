#ifndef IRremote_DISPLAY_CONTROO_SYSTEM_HPP
#define IRremote_DISPLAY_CONTROO_SYSTEM_HPP

/* # Anschlussplan für Display:
 * LCD RS pin to digital pin 5
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 8
 * LCD D6 pin to digital pin 9
 * LCD D7 pin to digital pin 10
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K Poti: oder durch 5k Ohm Widerstand ersetzt
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3) 
* A über 220 Ohm Widerstand zu 5V
* K zu GND
 */
#include <LiquidCrystal.h>
#include "base_definitions.h"

class Display_Control_System {
public:
  Display_Control_System(int rs_pin, int e_pin,int d4_pin,int d5_pin,int d6_pin,int d7_pin);  //Konstruktor

  void Init();  //Initilisierungs funktion
  void control(Display_Commands cmd); //Reagiert auf Eingabe (hoch, runter, ok)
  void Update_Display_Text(); //Textausgabe auf Display

  void UpdateValuesAtIndex(int index, int value);
  int GetValueAtIndex(int index);

private:
  LiquidCrystal lcd;  //Display-Klasse (Bibliothek)

  int current_Menu;
  int Menu_Index;
  int cursor_Position;
  String MenuStart[2];
  String MenuSenden[11];
  String MenuEmpfangen[4];
  String Menu4[2];
  int values[10];

  void Update_Values(int index, int value);
};

#endif  //IRremote_DISPLAY_CONTROO_SYSTEM_HPP
