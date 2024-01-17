#ifndef MENUE_CONTROL_LAYER_HPP
#define MENUE_CONTROL_LAYER_HPP

#include "base_definitions.h"

/**
 * # Diese Klasse verwaltete Menü-Einträge
 * Funktionen:
 *  - Init_Menue_Arrays -> initialisert die Menü-listen (im konstruktor aufgerufen)
 *  - Get_Entry -> hat als Rückgabe wert die Struktur eines Eintrages 
 *  - Manipulate_Entry -> kann einen Eintrag überschreiben
*/
class Menue_Control_Layer{

public:
  Menue_Control_Layer(/*FKT_Callback m_callback*/); //Konstruktor

  Menue_Entry_s Get_Entry(enum Menue_Titles title,int index);
  void Manipulate_Entry(enum Menue_Titles title,int index,Menue_Entry_s new_entry);
  int Check_Index(enum Menue_Titles title,int index);

private:
  void Init_Menue_Arrays(/*FKT_Callback m_callback*/); //Initialisert die Menü-arraysd mit werten

  Menue_Entry_s Start_Menue[4];
  Menue_Entry_s Send_Menue[10];
  Menue_Entry_s Recive_Menue[10];
  Menue_Entry_s Greetings_Menue[2];

};

#endif //MENUE_CONTROL_LAYER_HPP
