#include <Arduino.h>
#include "base_definitions.h"
#include "IRremote_Display_Control_System.hpp"
#include <LiquidCrystal.h>
#include <string>
#include <iostream>

//Konstruktor implementieren
Display_Control_System::Display_Control_System():current_Menu(1), cursor_Position(0), Menu_Index(0) {
  // Initialisierung der Werte-Liste mit Nullen
  for (int i = 0; i < 10; ++i) {
            values[i] = 0;
        }
}
LiquidCrystal lcd(Pin_LCD_RS ,Pin_LCD_E ,Pin_LCD_D4 ,Pin_LCD_D5 ,Pin_LCD_D6 , Pin_LCD_D7);

void Display_Control_System::init(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Hello, Munke!");
  Update_Display_Text();
}

void Display_Control_System::control(Display_Commands cmd){
  switch (cmd){
    case Display_UP:{
      Serial.println("UP");
      myDisplay.Move_Cursor(0)
      break;
    }
    case Display_DOWN:{
      Serial.println("DOWN");
      myDisplay.Move_Cursor(1)
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
void Display_Control_System::Update_Values(int index, int value){
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

public:
        //Initialisieren der Menu und Cursor führung
    

    void Update_Display_Text() {
        switch (current_Menu)
        {
        case 1:
          if (cursor_Position = 0){
            lcd.setCursor(0, 0);
            lcd.print("->" + MenuStart(0));
            lcd.setCursor(0, 1);
            lcd.print(MenuStart(1));
          }
          if (cursor_Position = 1){
            lcd.setCursor(0, 0);
            lcd.print(MenuStart(0));
            lcd.setCursor(0, 1);
            lcd.print("->" + MenuStart(1));
          }
          break;
        case 2:
          if (cursor_Position = 0){
            lcd.setCursor(0, 0);
            lcd.print("->" + MenuSenden(Menu_Index));
            lcd.setCursor(0, 1);
            lcd.print(MenuSenden(Menu_Index + 1));
          }
          if (cursor_Position = 1){
            lcd.setCursor(0, 0);
            lcd.print(MenuSenden(Menu_Index - 1));
            lcd.setCursor(0, 1);
            lcd.print("->" + MenuSenden(Menu_Index));
          }
        case 3:
          if (cursor_Position = 0){
            lcd.setCursor(0, 0);
            lcd.print("->" + MenuEmpfangen(Menu_Index));
            lcd.setCursor(0, 1);
            lcd.print(MenuEmpfangen(Menu_Index + 1));
          }
          if (cursor_Position = 1){
            lcd.setCursor(0, 0);
            lcd.print(MenuEmpfangen(Menu_Index - 1));
            lcd.setCursor(0, 1);
            lcd.print("->" + MenuEmpfangen(Menu_Index));
          }
        default:
          break;
        }
    }

    void Move_Cursor(int move) {
        switch (move)
        {
        case 0:
          /* Cursor input Up */
          if (cursor_Position = 1)
            cursor_Position = 0;
          if (Menu_Index != 0)
            Menu_Index--;
          
          Update_Display_Text()
          break;
        case 1:
          /* Cursor input Down */
          if (cursor_Position = 0)
            cursor_Position = 1;
          if (current_Menu = 1 && Menu_Index = 2)
            break;
          if (current_Menu = 2 && Menu_Index = 10)
            break;
          if (current_Menu = 3 && Menu_Index = 3)
            break;
          Menu_Index++;
          Update_Display_Text()
          break;
        case 2:
        /* Cursor Input Ok*/
        switch (current_Menu)
        {
        case 1:
          if (Menu_Index = 0)
            current_Menu = 2;
          if (Menu_Index = 1)
            current_Menu = 3;
          break;
        case 2:

        default:
          break;
        }
        cursor_Position = 0;
        Menu_Index = 0;
        break;
        default:
          break;
        }
    }

    // Funktion zum Aktualisieren der Werte-Liste an einem bestimmten Index
    void UpdateValuesAtIndex(int index, int value) {
        Update_Values(index, value);
    }
    int GetValueAtIndex(int index) const {
        // Überprüfe den Index, um sicherzustellen, dass er gültig ist
        if (index >= 0 && index < 10) {
            return values[index];
        } else {
            return -1; // Hier könnte auch eine andere spezielle Rückgabewert verwendet werden
        }
    }

