#include "Menue_Control_Layer.hpp"
#include "base_definitions.h"

Menue_Control_Layer::Menue_Control_Layer(/*FKT_Callback m_callback*/){
    Init_Menue_Arrays(/*m_callback*/);
}

void Menue_Control_Layer::Init_Menue_Arrays(/*FKT_Callback m_callback*/){
    //Begrüßungs menuü anlegen
    Greetings_Menue[0]={"Hello Munke",0,Menue_Entry_Start,nullptr};
    Greetings_Menue[1]={"copyright <R>",0,Menue_Entry_Start,nullptr};
    
    //Startmenü anlegen:
    Start_Menue[0]={"Senden",0,Menue_Entry_Senden,nullptr};
    Start_Menue[1]={"Empfangen",0,Menue_Entry_Empfangen,nullptr};
    Start_Menue[2]={"back",0,Menue_Entry_Greetings,nullptr};

    //TODO:: nullptr später ersetzten

    //SendenMenü anlegen:
    Send_Menue[0]={"cmd1",0x12,Funktion,nullptr};
    Send_Menue[1]={"cmd2",0x13,Funktion,nullptr};
    Send_Menue[2]={"cmd3",0x14,Funktion,nullptr};
    Send_Menue[3]={"cmd4",0x15,Funktion,nullptr};
    Send_Menue[4]={"cmd5",0x16,Funktion,nullptr};
    Send_Menue[5]={"cmd6",0x17,Funktion,nullptr};
    Send_Menue[6]={"cmd7",0x18,Funktion,nullptr};
    Send_Menue[7]={"cmd8",0x19,Funktion,nullptr};
    Send_Menue[8]={"cmd9",0x1a,Funktion,nullptr};
    Send_Menue[9]={"back",0,Menue_Entry_Start,nullptr};

    //EmpfangenMenü anlegen ->  leere liste, da noch nichts empfagen wurde??
    for (int i=0;i<(sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))-1;i++){
        Recive_Menue[i]={"leer",0,Funktion,nullptr};
    }
    Recive_Menue[(sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))-1]={"back",0,Menue_Entry_Start,nullptr};
}

Menue_Entry_s Menue_Control_Layer::Get_Entry(enum Menue_Titles title,int index){  
    switch (title){
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
        case Menue_Entry_Greetings:{
          if (index > (sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))-1){//wenn der Index größer als die anzahl der elemente ist
            break;
          }
          return Greetings_Menue[index];
        }
        case Funktion:
        default:{
          break;
        }
    }

    return Menue_Entry_s{"",0,Funktion,nullptr};
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