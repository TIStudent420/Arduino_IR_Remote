#include "Menue_Control_Layer.hpp"
#include "base_definitions.h"

Menue_Control_Layer::Menue_Control_Layer(FKT_Callback callback){
    Init_Menue_Arrays(callback);
}

void Menue_Control_Layer::Init_Menue_Arrays(FKT_Callback callback){
    //Startmenü anlegen:
    Start_Menue[0]={"Senden",0,true,Menue_Entry_Senden,nullptr};
    Start_Menue[1]={"Empfangen",0,true,Menue_Entry_Empfangen,nullptr};

    //SendenMenü anlegen:
    Send_Menue[0]={"cmd1",0x12,false,Funktion,callback};
    Send_Menue[1]={"cmd2",0x13,false,Funktion,callback};
    Send_Menue[2]={"cmd3",0x14,false,Funktion,callback};
    Send_Menue[3]={"cmd4",0x15,false,Funktion,callback};

    //EmpfangenMenü anlegen ->  leere liste, da noch nichts empfagen wurde??
    for (int i=0;i<(sizeof(Recive_Menue)/sizeof(Recive_Menue[0]));i++){
        Recive_Menue[i]={"null",0,false,Funktion,callback};
    }
}

Menue_Entry_s Menue_Control_Layer::Get_Entry(enum Menue_Titles title,int index){
    switch (title){
        case Menue_Entry_Start:
            return Start_Menue[index];
        case Menue_Entry_Senden:
            return Send_Menue[index];
        case Menue_Entry_Empfangen:
            return Recive_Menue[index];
        case Funktion:
        default:
            return Menue_Entry_s{nullptr,0,false,Funktion,nullptr};
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
    }    
    return;
}