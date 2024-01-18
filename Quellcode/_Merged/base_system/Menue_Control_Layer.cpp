#include "Menue_Control_Layer.hpp"
#include "base_definitions.h"
#include <Arduino.h>

Menue_Control_Layer::Menue_Control_Layer(){
    Init_Menue_Arrays();
}

void Menue_Control_Layer::Init_Menue_Arrays(){
    IRData_s null_data = {NEC_T,0x00,0x00};
    
    //Begrüßungs menuü anlegen
    Greetings_Menue[0]={"Hello Munke",null_data,Menue_Entry_Start};
    Greetings_Menue[1]={"copyright <R>",null_data,Menue_Entry_Start};
    Serial.println(Greetings_Menue[0].name);
    
    //Startmenü anlegen:
    Start_Menue[0]={"Senden",null_data,Menue_Entry_Senden};
    Start_Menue[1]={"Empfangen",null_data,Menue_Entry_Empfangen};
    Start_Menue[2]={"Abrufen",null_data,Menue_Entry_Saved};
    Start_Menue[3]={"back",null_data,Menue_Entry_Greetings};

    //SendenMenü anlegen:
    Send_Menue[0]={"Ein/Aus",{NEC_T,0x00,0x45},Funktion};
    Send_Menue[1]={"Rot",{NEC_T,0x00,0x46},Funktion};
    Send_Menue[2]={"Blau",{NEC_T,0x00,0x15},Funktion};
    Send_Menue[3]={"Gruen",{NEC_T,0x00,0x47},Funktion};
    Send_Menue[4]={"was?",{NEC_T,0x00,0x44},Funktion};
    Send_Menue[5]={"Vor>>",{NEC_T,0x00,0x43},Funktion};
    Send_Menue[6]={"Play/Pause",{NEC_T,0x00,0x40},Funktion};
    Send_Menue[7]={"cmd8",{NEC_T,0x00,0x07},Funktion};
    Send_Menue[8]={"cmd9",{NEC_T,0x00,0x09},Funktion};

    Send_Menue[9]={"back",{NEC_T,0x00,0x00},Menue_Entry_Start};
    Serial.println(Send_Menue[0].name);

    //EmpfangenMenü anlegen ->  leere liste, da noch nichts empfagen wurde??

    Recive_Menue[0]={"Erfolg",null_data,Funktion};
    Recive_Menue[1]={"Fehler",null_data,Menue_Entry_Start};
    Serial.println(Recive_Menue[0].name);    
}

Menue_Entry_s Menue_Control_Layer::Get_Entry(enum Menue_Titles title,int index){  
    switch (title){
        case Menue_Entry_Greetings:{
          if (index > (sizeof(Greetings_Menue)/sizeof(Greetings_Menue[0]))-1){//wenn der Index größer als die anzahl der elemente ist
            break;
          }
          return Greetings_Menue[index];
        }
        case Menue_Entry_Start:{
          if (index > (sizeof(Start_Menue)/sizeof(Start_Menue[0]))-1){//wenn der Index größer als die anzahl der elemente ist
            break;
          } 
          return Start_Menue[index];
        }
        case Menue_Entry_Senden:{
          if (index > (sizeof(Send_Menue)/sizeof(Send_Menue[0]))-1){//wenn der Index größer als die anzahl der elemente ist
            break;
          } 
          return Send_Menue[index];
        }
        case Menue_Entry_Empfangen:{
          if (index > (sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))-1){//wenn der Index größer als die anzahl der elemente ist
            break;
          }
          return Recive_Menue[index];
        }
        case Funktion:
        default:{
          break;
        }
    }
    return Menue_Entry_s{"",{UNKNOWN_T,0,0},Funktion};
}
   
 void Menue_Control_Layer::Manipulate_Entry(enum Menue_Titles title,int index,Menue_Entry_s new_entry){
    switch (title){
        case Menue_Entry_Start:
            Start_Menue[index]=new_entry;
        case Menue_Entry_Senden:
            Send_Menue[index]=new_entry;
        case Menue_Entry_Empfangen:
            Recive_Menue[index]=new_entry;
        case Funktion:
        default:
          break;
    }    
    return;
}

//return 0, wenn kein Grenzfall erreicht ist (index in mitte des Arrays)
//return 1, wenn obere Grenze des Arrays erreicht
//return 2, unter Grenze des Arrays errreicht
//return 3, beides trifft zu
int Menue_Control_Layer::Check_Index(enum Menue_Titles title,int index){
  int i_check_ret = 0;
  int max;
  switch (title){
    case Menue_Entry_Start:{
      max = (sizeof(Start_Menue)/sizeof(Start_Menue[0]))-1;
      break;
    }
    case Menue_Entry_Senden:{
      max = (sizeof(Send_Menue)/sizeof(Send_Menue[0]))-1;
      break;
    }
    case Menue_Entry_Empfangen:{
      max = (sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))-1;
      break;
    }
    case Menue_Entry_Greetings:{
      max = (sizeof(Greetings_Menue)/sizeof(Greetings_Menue[0]))-1;
      break;
    }
    case Funktion:
    default:{
      max = 0;
      break;
    }
  }

  if (index >= max)
    i_check_ret=1;
  if(index <= 0)//index gleich vorletztes Element oder gleich null -> bleibt unverändert
    i_check_ret=2;


  return i_check_ret;
}
