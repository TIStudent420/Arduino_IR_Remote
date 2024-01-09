#include "Menue_Control_Layer.hpp"
#include "base_definitions.h"

Menue_Control_Layer::Menue_Control_Layer(/*FKT_Callback m_callback*/){
    Init_Menue_Arrays(/*m_callback*/);
}

void Menue_Control_Layer::Init_Menue_Arrays(/*FKT_Callback m_callback*/){
    //Startmenü anlegen:
    Start_Menue[0]={"Senden",0,true,Menue_Entry_Senden,nullptr};
    Start_Menue[1]={"Empfangen",0,true,Menue_Entry_Empfangen,nullptr};

    //TODO:: nullptr später ersetzten

    //SendenMenü anlegen:
    Send_Menue[0]={"cmd1",0x12,false,Funktion,nullptr};
    Send_Menue[1]={"cmd2",0x13,false,Funktion,nullptr};
    Send_Menue[2]={"cmd3",0x14,false,Funktion,nullptr};
    Send_Menue[3]={"cmd4",0x15,false,Funktion,nullptr};

    //EmpfangenMenü anlegen ->  leere liste, da noch nichts empfagen wurde??
    for (int i=0;i<(sizeof(Recive_Menue)/sizeof(Recive_Menue[0]));i++){
        Recive_Menue[i]={"null",0,false,Funktion,nullptr};
    }
}

Menue_Entry_s Menue_Control_Layer::Get_Entry(enum Menue_Titles title,int index){  
    switch (title){
        case Menue_Entry_Start:{
          if (index > (sizeof(Start_Menue)/sizeof(Start_Menue[0]))){//wenn der Index größer als die anzahl der elemente ist
          return Menue_Entry_s{"",0,false,Funktion,nullptr};
        } else if(index < (sizeof(Start_Menue)/sizeof(Start_Menue[0]))){//wenn der Index kleiner als die anzahl der elemente ist
            return Start_Menue[0];
        }
        return Start_Menue[index];
        }
        case Menue_Entry_Senden:{
          if (index > (sizeof(Send_Menue)/sizeof(Send_Menue[0]))){//wenn der Index größer als die anzahl der elemente ist
          return Menue_Entry_s{"",0,false,Funktion,nullptr};
        } else if(index < (sizeof(Send_Menue)/sizeof(Send_Menue[0]))){//wenn der Index kleiner als die anzahl der elemente ist
            return Send_Menue[0];
        }
        return Send_Menue[index];}
        case Menue_Entry_Empfangen:{
          if (index > (sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))){//wenn der Index größer als die anzahl der elemente ist
          return Menue_Entry_s{"",0,false,Funktion,nullptr};
        } else if(index < (sizeof(Recive_Menue)/sizeof(Recive_Menue[0]))){//wenn der Index kleiner als die anzahl der elemente ist
            return Recive_Menue[0];
        }
        return Recive_Menue[index];}
        case Funktion:
        default:
            return Menue_Entry_s{"",0,false,Funktion,nullptr};
    }
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