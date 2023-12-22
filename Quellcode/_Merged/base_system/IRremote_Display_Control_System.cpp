#include <Arduino.h>
#include "base_definitions.h"
#include "IRremote_Display_Control_System.hpp"

//Konstruktor implementieren
Display_Control_System::Display_Control_System(int rs_pin, int e_pin, int d4_pin, int d5_pin, int d6_pin, int d7_pin)
  :lcd(rs_pin, e_pin, d4_pin, d5_pin, d6_pin, d7_pin) {


}


void Display_Control_System::Init() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Hello, Munke!");
  /* 1. Menü einlesen
     ab index==0 darstellen (2-Zeilen) 
     mit pfeil vorm ersten
     --> Funktion: Show_Menu_at_Index(int index);
  */
  Update_Display_Text();
}

/* 

variablen:
kurrent menue: enum... -> im konstrucktor initialisert
kurrentz index: int...

Kalsse menue_entry(bool vorgänger_oder_nachfolger,fkt(NULL) oder menue(enum), bezeichnung, wert, *Callback?)
enum menue_entry //hier stehen alle Menue, die es gibt aufgelistet

void Display_Control_System::load_menue(){
  // switch (current_menue (enum))
  //return *array
}

void Display_Control_System::Show_Menu_Index_DOWN(*menu_entry_array){
  //aktueller_Index -> kontrollieren, ob dieser dem maximalen index entspricht (Methode zu berechnen der größe des Menu-Arrays?)
  //-> falls nicht: inkrementiert den Index 
}

void Display_Control_System::Show_Menu_Index_UP(*menue_entry_array){
  //aktueller_Index -> kontrollieren, ob dieser 0 ist
  //-> falls nicht: inkrementiert aktuellen_Index 
  Show_Menu_At_Index(aktueller_Index)
}

//dieser Funktion wir mit bereits überprüften Index aufgerufen
void Display_Control_System::Show_Menu_At_Index(int index, *menu_entry_array){
  // Display löschen / aktualisieren
  // anzeigen : Menu-Array[index]
  // &
  // anzeigen : Menu-Array[index+1]
}

*/

void Display_Control_System::control(Display_Commands cmd) {
  switch (cmd) {
    case Display_UP: //bedeutet menue index verringern
      {
        Serial.println("UP"); 
        /* Was passiert hier?, nach dem Befhel "UP"

        */
        /* Cursor input Up */
        if (Display_Control_System::cursor_Position == 1)
          cursor_Position = 0;
        if (Display_Control_System::Menu_Index != 0)
          Menu_Index--;

        Update_Display_Text();
        break;
      }
    case Display_DOWN: //bedeutet menue index erhöhen
      {
        Serial.println("DOWN");
        /* Cursor input Down 
        if (Display_Control_System::cursor_Position = 0)
          cursor_Position = 1;
        if (Display_Control_System::current_Menu == 1 && Menu_Index == 2)
          break;
        if (Display_Control_System::current_Menu == 2 && Menu_Index == 10)
          break;
        if (Display_Control_System::current_Menu == 3 && Menu_Index == 3)
          break;
        Display_Control_System::Menu_Index++;
        Update_Display_Text();

        break;*/
      }
    case Display_OK: //bedeutet neue Funktionszuweisung (kann jedesmal eine andere FKT sein, die ausgeführt wird)
      {
        Serial.println("OK");
        /* Cursor Input Ok
        switch (Display_Control_System::current_Menu) {
          case 1:
            if (Menu_Index == 0)
              current_Menu = 2;
            if (Menu_Index == 1)
              current_Menu = 3;
            break;
          case 2:

          default:
            break;
        }
        Display_Control_System::cursor_Position = 0;
        Menu_Index = 0;
        break;*/
      }
    default:
      break;
  }
}

void Display_Control_System::Update_Values(int index, int value) {
  // Überprüfe den Index, um sicherzustellen, dass er gültig ist
  if (index >= 0 && index < 10) {
    values[index] = value;
  } else {
    return -1;
  }
  return;
}
// Funktion zum Aktualisieren der Werte-Liste an einem bestimmten Index
void Display_Control_System::UpdateValuesAtIndex(int index, int value) {
  Update_Values(index, value);
}

int Display_Control_System::GetValueAtIndex(int index) {
  // Überprüfe den Index, um sicherzustellen, dass er gültig ist
  if (index >= 0 && index < 10) {
    return values[index];
  } else {
    return -1;  // Hier könnte auch eine andere spezielle Rückgabewert verwendet werden
  }
}

void Display_Control_System::Update_Display_Text(String text_1, String text_2){
  
}

//Schreibt text auf display (gibt nur zwei spalten)
void Display_Control_System::WriteDisplayAt(String text,int position) {
  if(position  == 0 || position == 1){
    lcd.setCursor(0, position);
    lcd.print(text);
  }
}
