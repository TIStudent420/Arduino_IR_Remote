#include <stdint.h>

#include "base_definitions.h" //Pin-definitionen, Enum für Displayschnittstelle
#include "IRremote_RE_Input_Control.hpp"
#include "IRremote_Display_Control_System.hpp"
#include "Menue_Control_Layer.hpp"

//IR Sensor und Empfänger

//Drehschalter-Klasse Initialisieren -> zum Steuern der Ein-/Ausgabe
RE_Input_Control Drehschalter(Pin_RE_CLK, Pin_RE_DT, Pin_RE_SW);
//Display-Klasse Initialisieren
Display_Control_System lcd_display(Pin_LCD_RS,Pin_LCD_E,Pin_LCD_D4,Pin_LCD_D5,Pin_LCD_D6,Pin_LCD_D7);
//Menü
Menue_Control_Layer Menue;

void setup() {
  //Serielle Kommunikation initialisieren
  Serial.begin(9600);

  lcd_display.Init();
  //Initialisierungen/Setup des Drehschalters
  Drehschalter.Init();


  Serial.println("Hello Munke");
}

uint8_t curr_menu_index=0;
enum Menue_Titles curr_Title;

void display_menu(){
  //Name vom aktuellen und nachfolgenden Menü-eintrag anzeigeindex
  Menue_Entry_s curr_entry;
  String entry_text_1;
  String entry_text_2;
  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index);  
  entry_text_1 = curr_entry.name;
  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index+1);
  entry_text_2 = curr_entry.name;
  lcd_display.Update_Display_Text(entry_text_1,entry_text_2);
  return;
}

void check_menue_entry(){
  //Menü eintrag überprüfen:
  // -> folgt ein weiteres Menü?
  // -> wenn nicht, dann folgt eine Funktion
  // -> senden, empfangen oder callback??
}

//Diese Funktion wird als callback an den Drehschalter übergeben
void base_system(Display_Commands cmd){
 
  switch (cmd) {
    case Display_UP:
      {
        Serial.println("UP"); 
        //Menü anzeigeindex erhöhen
        curr_menu_index++;
        //Display Aktualisieren
        display_menu();
        break;
      }
    case Display_DOWN:
      {
        Serial.println("DOWN");
        //Menü anzeigeindex verringern
        curr_menu_index--;
        //Display Aktualisieren
        display_menu();
        break;
      }
    case Display_OK:
      {
        Serial.println("OK");
        check_menue_entry();
        break;
      }
    default:
      break;
  }
}


/**
 * @param toSend true wenn die funktion senden soll, flase wenn Daten Empfangen werden sollen 
 * @param send_value der zusendende Command, bzw die sende-strucktur
*/
void menue_callback_layer(bool toSend,int send_value){
  if (toSend){
    Serial.println("Sendevorgang einleiten...");
  }
  else{
    Serial.println("Empfangvorgang einleiten...");
  }
}

void loop() {
  //Überprüft die Eingabe des Drehschalters
  //Übergabe einer Funktion, diese aktualisiert das Menü/Aufgabe und das Display 
  Drehschalter.Checkup(base_system);
}
