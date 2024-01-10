#include <stdint.h>

#include "base_definitions.h" //Pin-definitionen, Enum für Displayschnittstelle, Enum und Strucktur für Menüeinträge
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
  display_menu();
}

//globale Variablen
int curr_menu_index = 0;
enum Menue_Titles curr_Title = -1;

//Wenn Display_UP || Display_DOWN
//neuen Menüeintrag auf display anzeigen (ermittelt über aktuellen Menü-Titel und aktuellen Index)
void display_menu(){
  //Speichervariable für aktuellen Menüeintrag
  Menue_Entry_s curr_entry;
  //Bezeichnung des Eintrages -> wird auf Display angezeigt
  String entry_text_1;
  String entry_text_2;

  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index);  
  entry_text_1 = curr_entry.name;
  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index+1);
  entry_text_2 = curr_entry.name;
  
  lcd_display.Update_Display_Text(entry_text_1,entry_text_2);

  //TODO: Testausgabe wieder entfernen:
  Serial.print(" anzeige text1: ");
  Serial.print(entry_text_1);
  Serial.print(" anzeige text2: ");
  Serial.print(entry_text_2);
  Serial.println(" ");

  Serial.print(" titel: ");
  Serial.print(curr_Title);
  Serial.print(" index: ");
  Serial.print(curr_menu_index);
  Serial.println(" ");
  return;
}

//Wenn Display_OK:
void check_menue_entry(){
  //Menü eintrag überprüfen:
  // -> folgt ein weiteres Menü?
  // -> wenn nicht, dann folgt eine Funktion
  // -> senden, empfangen oder callback??
  Menue_Entry_s curr_entry;
  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index);

  if(curr_entry.followed_by==Funktion){//es soll eine Funktion (senden oder empfangen ausgeführt werden)
    //callback oder andere Funktion ausführen
    if(curr_Title==Menue_Entry_Senden){
      //Sende-funktion aufrufen
    }else if(curr_Title==Menue_Entry_Empfangen){
      //empfang-Schleife aufrufen
  }
  }else{  
    curr_Title=curr_entry.followed_by;
  }
  return;
}

//Diese Funktion wird als callback an den Drehschalter übergeben
void base_system(Display_Commands cmd){
  int checker = Menue.Check_Index(curr_Title,curr_menu_index);
  switch (cmd) {
    case Display_UP:
      {
        //index Kontrolle(
        if(checker==1||checker==3)
          break;  
        curr_menu_index++; //Menü anzeigeindex erhöhen
        break;
      }
    case Display_DOWN:
      {
        //index Kontrolle
        if(checker==2||checker==3)
          break;  
        curr_menu_index--; //Menü anzeigeindex verringern
        break;
      }
    case Display_OK:
      {
        check_menue_entry();
        //index zurückstezten
        curr_menu_index=0;
        break;
      }
    default:
      break;
  }
  //display aktualisieren
  display_menu();
}

void loop() {
  //Überprüft die Eingabe des Drehschalters
  //Übergabe einer Funktion, diese aktualisiert das Menü/Aufgabe und das Display 
  Drehschalter.Checkup(base_system);
}
