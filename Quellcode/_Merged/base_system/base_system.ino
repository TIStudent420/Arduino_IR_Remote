#include <stdint.h>

#include "base_definitions.h" //Pin-definitionen, Enum für Displayschnittstelle, Enum und Strucktur für Menüeinträge
#include "IRremote_RE_Input_Control.hpp"
#include "IRremote_Display_Control_System.hpp"
#include "Menue_Control_Layer.hpp"

//IR Sensor und Empfänger
#include "IRremote_Sensor_Actor_System.hpp"

//Drehschalter-Klasse Initialisieren -> zum Steuern der Ein-/Ausgabe
RE_Input_Control Drehschalter(Pin_RE_CLK, Pin_RE_DT, Pin_RE_SW);
//Display-Klasse Initialisieren
Display_Control_System lcd_display(Pin_LCD_RS,Pin_LCD_E,Pin_LCD_D4,Pin_LCD_D5,Pin_LCD_D6,Pin_LCD_D7);
//Menü
Menue_Control_Layer Menue;
//Sender & Empfänger
Sensor_Actor_System IR_System(Pin_IR_RECV,Pin_IR_RECV_FEEDBACK,Pin_IR_LED,Pin_IR_LED_FEEDBACK);

void setup() {
  //Serielle Kommunikation initialisieren
  Serial.begin(9600);

  lcd_display.Init();
  //Initialisierungen/Setup des Drehschalters
  Drehschalter.Init();

  display_menu();
}

//globale Variablen
int curr_menu_index = 0;  //Zähler -> Aktueller Menüeintrag
enum Menue_Titles curr_Title = Menue_Entry_Greetings; //aktueller Menütitel (start mit Greetings)
struct IRData_s *recived_data_ptr = nullptr;  //empfangene Daten vom reciever als Pointer (ist besser zum auswerten)
bool write_flag = false; //später evtl durch überprüfung auf nullpointer von empfangenen Daten (recived_data)

//Wenn Display_UP || Display_DOWN
//neuen Menüeintrag auf display anzeigen (ermittelt über aktuellen Menü-Titel und aktuellen Index)
void display_menu(){
  //Lokale Variablen
  struct Menue_Entry_s curr_entry; //Speichervariable für aktuellen Menüeintrag
  String entry_text_1; //Bezeichnungen des Eintrages -> wird auf Display angezeigt
  String entry_text_2;

  //TODO  Testausgabe entfernen
  Serial.print(" titel: ");
  Serial.print(curr_Title);
  Serial.print(" index: ");
  Serial.print(curr_menu_index);
  Serial.println(" ");

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
  return;
}

//Wenn Display_OK:
int check_menue_entry(){
  int err;
  //Menü eintrag überprüfen:
  // -> Folgeschritt auswerden
  struct Menue_Entry_s curr_entry = Menue.Get_Entry(curr_Title,curr_menu_index);

  if(curr_entry.followed_by==Funktion){//es soll eine Funktion (senden oder empfangen ausgeführt werden)
    //callback oder andere Funktion ausführen
    if(curr_Title==Menue_Entry_Senden){
      //Sende-funktion aufrufen
      if(!write_flag){
        Serial.println("senden");
        err = send_irremote(curr_entry);
       }else{
        Serial.println("schreiben");
        //neuer Eintrag
        //TODO Pointer richtig auslesen!!!
        Menue_Entry_s new_entry={"get",{recived_data->protokoll},Menue_Entry_Start};
        //Eintrag Manipulieren
        Menue.Manipulate_Entry(Menue_Entry_Senden,curr_menu_index,new_entry);
        write_flag=false;
       }
    }
    else if(curr_Title==Menue_Entry_Empfangen){
      //empfang-Schleife aufrufen
      err = recive_irremote();
      curr_Title=Menue_Entry_Senden;
      write_flag=true;
  }
  }else{  
    curr_Title=curr_entry.followed_by;
    err =0;
  }
  Serial.println(curr_Title);
  return err;
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
        if(check_menue_entry())
          Serial.println("Fehler beim ausführen der Funktion");

        //index zurückstezten
        curr_menu_index = 0;
        
        //schreibe-flag zurücksetzten
        //write_flag = false;
        
        //Menü zurücksetzten
        //curr_Title = Menue_Entry_Greetings;
        break;
      }
    default:
      break;
  }
  //display aktualisieren
  display_menu();
}

int send_irremote(Menue_Entry_s curr_entry){
  
  Serial.println(curr_entry.data.protocol);
  Serial.println(curr_entry.data.command);

  IR_System.Send(0x00,curr_entry.data.command,5);
  return 0;
}

int recive_irremote(){

  //Ladeanzeige
  lcd_display.Update_Display_Text("Empfangen",". . .");
  //TODO delay wieder entfernen, ist nur für Testzwecke da
  delay(500); 
  //Schleife zum Empfangen der Daten
  while (true/*!(Drehschalter.Checkup(nullptr)==3)*/) //Unterbrechung durch Drehschalter möglich
  {
    if (IR_System.Recive(recived_data_ptr)) // bei empfagen, Pointer auf neue Daten, Funktion beenden
      return 0;
    
  }

  return 5;
}

void loop() {
  //Überprüft die Eingabe des Drehschalters
  //Übergabe einer Funktion, diese aktualisiert das Menü/Aufgabe und das Display 
  Drehschalter.Checkup(base_system);
}
