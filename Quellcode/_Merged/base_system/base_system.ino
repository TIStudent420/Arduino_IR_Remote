#include <stdint.h>
//#include <memory> //wie geht das in Arduino IDE??

#include "base_definitions.h"                   //Pin-definitionen, Enum für Displayschnittstelle, Enum und Strucktur für Menüeinträge, Enum und Struckturen für IR-Daten
#include "IRremote_RE_Input_Control.hpp"        //Steuerung/Eingabe
#include "IRremote_Display_Control_System.hpp"  //Display anzeige Funktionen und Spezielle Display initialisierungen
#include "IRremote_Menu_Control_Layer.hpp"              //Menü initialisierungen und zugriffsfunktionen
#include "IRremote_Sensor_Actor_System.hpp"     //IR Sensor und Empfänger

//Klassen initialisierungen
RE_Input_Control Drehschalter(Pin_RE_CLK, Pin_RE_DT, Pin_RE_SW);                                      //Drehschalter-Klasse Initialisieren -> zum Steuern der Ein-/Ausgabe
Display_Control_System lcd_display(Pin_LCD_RS,Pin_LCD_E,Pin_LCD_D4,Pin_LCD_D5,Pin_LCD_D6,Pin_LCD_D7); //Display-Klasse Initialisieren
Menu_Control_Layer Menue;                                                                            //Menü
Sensor_Actor_System IR_System(Pin_IR_RECV,Pin_IR_RECV_FEEDBACK,Pin_IR_LED,Pin_IR_LED_FEEDBACK);       //Sender & Empfänger

//globale Variablen                                     
int curr_menu_index = 0;                                //Zähler -> Aktueller Menüeintrag
enum Menu_Titles curr_Title = MENU_TITLE_GREETINGS_e;  //aktueller Menütitel (start mit Greetings)
struct Menu_Entry_s curr_entry;                        //Speichervariable für aktuellen Menüeintrag
IRData_s *received_data_ptr = nullptr;      //empfangene Daten vom reciever als Pointer (ist besser zum auswerten)


//Initialisierungsfunktion
void setup() {
  Serial.begin(9600);   //Serielle Kommunikation;
  lcd_display.Init();   //Display
  Drehschalter.Init();  //Drehschlater
  IR_System.Init();     //IR-Sender und Empfänger
  display_menu();       //Display aktualisieren
}

/**
 * # display_menu
 * @brief Aktualisiert das Display
 * @note ermittelt über aktuellen Menü-Titel und aktuellen Index den aktuellen und nachfolgenden Menüeintrag und übergibt beie bezeichnungendem Display 
*/
void display_menu(){     //Wenn DISPLAY_UP_e || DISPLAY_DOWN_e
  String entry_text[2];  //Anzeigetext für das Display

  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index);  
  entry_text[0] = "->"+curr_entry.name;
  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index+1);
  entry_text[1] = curr_entry.name;
  
  lcd_display.Update_Display_Text(entry_text[0],entry_text[1]);

  return;
}

/**
 * # check_menue_entry 
 * @brief Überprüft den Nachfolger (nächstes Menü anzeigen oder Funktion ausführen)
 * @note Menue_Entry_s.followed_by ... FUNKTION, MENÜ_TITlE_...
*/
int check_menue_entry(){
  curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index);

  if(curr_entry.followed_by==Funktion){  //Menüeintrag soll als Nachfolger eine Funktion ausführen 
    switch (curr_Title){
      case MENU_TITLE_SEND_e:{
        if(received_data_ptr == nullptr){    //es wurden keine neuen Daten empfangen -> normales Senden          
          return send_irremote(curr_entry);  //Senden Eines IR-Signals
        }  
        else{                                                                    //ich will neue Daten (kürzlich empfangen) abspeichern
          Menue.Manipulate_Entry(MENU_TITLE_SEND_e,curr_menu_index,curr_entry);  //Menüeintrag überschreiben    
          delete received_data_ptr;                                              //Speicherplatz wieder freigeben
          received_data_ptr = nullptr;                                           //Zeiger auf Empfangene Daten zurücksetzen (sonst undefiniertes verhalten)
          curr_Title = MENU_TITLE_START_e;                                       //dann ins Start-Menü übergehen
          return 33;                                                             
        }   
      }
      case (MENU_TITLE_RECEIVE_e):{
        curr_Title=MENU_TITLE_SEND_e;  //dann ins Sende-Menü übergehen
        return recive_irremote();      //empfang-Schleife aufrufen
      }
      default:{
        curr_Title = MENU_TITLE_START_e;  //dann ins Start-Menü übergehen
        return -69;                       //Wenn du hier raus kommst, dann hast du vergessen, ein Menü hinzuzufügen
      }
    }
  }
  else{                                 //es folgt der Wechsel in ein anderes Menü 
    curr_Title=curr_entry.followed_by;  //Menü-Titel Aktualisieren 
    return 0;
  }
}

//Diese Funktion wird als callback an den Drehschalter übergeben
void base_system(Display_Commands cmd){
  int checker = Menue.Check_Index(curr_Title,curr_menu_index);
  int err;

  switch (cmd) {
    case DISPLAY_UP_e:{
      //index Kontrolle(
      if(checker==1||checker==3)
        break;  
      curr_menu_index++; //Menü anzeigeindex erhöhen
      break;
    }
    case DISPLAY_DOWN_e:{
      //index Kontrolle
      if(checker==2||checker==3)
        break;  
      curr_menu_index--; //Menü anzeigeindex verringern
      break;
    }
    case DISPLAY_OK_e:{
        err = check_menue_entry();
          Serial.println("Fehler beim ausführen der Funktion");
        //index zurückstezten
        curr_menu_index = 0;
        break;
    }
    default:
      break;
  }

  if(err)
    Serial.println("Fehlerhaft beendet; err: " + err);

  display_menu();  //display aktualisieren
}

//IR-Sendefunktion ausführen
int send_irremote(Menu_Entry_s curr_entry){
  return IR_System.Send(0x00,curr_entry.data.command,5);
}

int recive_irremote(){

  lcd_display.Update_Display_Text("Empfangen",". . .");  //Ladeanzeige
  delay(500);                                            //TODO delay wieder entfernen, ist nur für Testzwecke da
  
  while (IR_System.Recive(received_data_ptr)) //Schleife zum Empfangen der Daten
  {
    if(Drehschalter.Checkup(nullptr))  //Unterbrechung durch Drehschalter möglich
      return 5;                        //Abbruch durch Eingabe am Drehknopf   
  }
}

void loop() {
  //Überprüft die Eingabe des Drehschalters -> führt bei Eingabe die übergebene Callbackfunktion aus
  Drehschalter.Checkup(base_system);
}
