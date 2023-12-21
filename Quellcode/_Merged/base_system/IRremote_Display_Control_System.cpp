#include <Arduino.h>
#include "base_definitions.h"
#include "IRremote_Display_Control_System.hpp"
#include <LiquidCrystal.h>


//Konstruktor implementieren
Display_Control_System::Display_Control_System()
  : current_Menu(1), cursor_Position(0), Menu_Index(0) {
    Serial.println("Konstruktor_Diaplay");
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

  // Initialisierung der Werte-Liste mit Nullen
  for (int i = 0; i < 10; ++i) {
    values[i] = 0;
  }
  Serial.println(current_Menu);
  Serial.println(Menu_Index);
  Serial.println(cursor_Position);

}
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void Display_Control_System::init() {
  Serial.println("init");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Hello, Munke!");
  Update_Display_Text();
}

void Display_Control_System::control(Display_Commands cmd) {
  Serial.println("control");
  switch (cmd) {
    case Display_UP:
      {
        Serial.println("UP");
        /* Cursor input Up */
        if (Display_Control_System::cursor_Position = 1)
          cursor_Position = 0;
        if (Display_Control_System::Menu_Index != 0)
          Menu_Index--;

        Update_Display_Text();
        break;
      }
    case Display_DOWN:
      {
        Serial.println("DOWN");
        /* Cursor input Down */
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

        break;
      }
    case Display_OK:
      {
        Serial.println("OK");
        /* Cursor Input Ok*/
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
        break;
      }
    default:
      break;
  }
}
void Display_Control_System::Update_Values(int index, int value) {
  Serial.println("Update_Values");
  // Überprüfe den Index, um sicherzustellen, dass er gültig ist
  if (index >= 0 && index < 10) {
    values[index] = value;
    //std::cout << "Wert an Index " << index << " in der Liste aktualisiert." << std::endl;
  } else {
    //std::cerr << "Ungültiger Index für die Werteaktualisierung." << std::endl;
    return -1;
  }
  return;
}

//Initialisieren der Menu und Cursor führung


void Display_Control_System::Update_Display_Text() {
  Serial.println("Update_Display_Text");
  switch (Display_Control_System::current_Menu) {
    case 1:
      if (Display_Control_System::cursor_Position = 0) {
        lcd.setCursor(0, 0);
        lcd.print("->" + MenuStart[0]);
        lcd.setCursor(0, 1);
        lcd.print(MenuStart[1]);
      }
      if (cursor_Position = 1) {
        lcd.setCursor(0, 0);
        lcd.print(MenuStart[0]);
        lcd.setCursor(0, 1);
        lcd.print("->" + MenuStart[1]);
      }
      break;
    case 2:
      if (cursor_Position = 0) {
        lcd.setCursor(0, 0);
        lcd.print("->" + MenuSenden[Menu_Index]);
        lcd.setCursor(0, 1);
        lcd.print(MenuSenden[Menu_Index + 1]);
      }
      if (cursor_Position = 1) {
        lcd.setCursor(0, 0);
        lcd.print(MenuSenden[Menu_Index - 1]);
        lcd.setCursor(0, 1);
        lcd.print("->" + MenuSenden[Menu_Index]);
      }
    case 3:
      if (cursor_Position = 0) {
        lcd.setCursor(0, 0);
        lcd.print("->" + MenuEmpfangen[Menu_Index]);
        lcd.setCursor(0, 1);
        lcd.print(MenuEmpfangen[Menu_Index + 1]);
      }
      if (cursor_Position = 1) {
        lcd.setCursor(0, 0);
        lcd.print(MenuEmpfangen[Menu_Index - 1]);
        lcd.setCursor(0, 1);
        lcd.print("->" + MenuEmpfangen[Menu_Index]);
      }
    default:
      break;
  }
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
