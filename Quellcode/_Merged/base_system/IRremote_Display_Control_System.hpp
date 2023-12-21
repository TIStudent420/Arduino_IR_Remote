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

#include "base_definitions.h"

class Display_Control_System{
private:
int current_Menu;
    int Menu_Index;
    int cursor_Position;
    string MenuStart[2];
    string MenuSenden[11];
    string MenuEmpfangen[4];
    string Menu4[2];
    int values[10];
        // Initialisierung der Menü-Arrays
        MenuStart[0] = "Senden";
        MenuStart[1] = "Empfangen";

        MenuSenden[0] = "1";
        MenuSenden[1] = "2";
        MenuSenden[2] = "3";
        MenuSenden[3] = "4";
        MenuSenden[4] = "5";
        MenuSenden[5] = "6";
        MenuSenden[6] = "7";
        MenuSenden[7] = "8";
        MenuSenden[8] = "9";
        MenuSenden[9] = "10";
        MenuSenden[10] = "Abbrechen";

        MenuEmpfangen[0] = "Warte auf Signal...";
        MenuEmpfangen[1] = "Signal Empfangen: ";
        MenuEmpfangen[2] = "Speichern";
        MenuEmpfangen[3] = "Abbrechen";

        Menu4[0] = "Option1";
        Menu4[1] = "Option2";
    void Update_Values(int index, int value);


public:
  Display_Control_System(); //Konstruktor
  
  void init(); //Initilisierungs funktion 

  void control(Display_Commands cmd);

  void Update_Display_Text();

  void UpdateValuesAtIndex(int index, int value);
  int GetValueAtIndex(int index);
};

#endif //IRremote_DISPLAY_CONTROO_SYSTEM_HPP
