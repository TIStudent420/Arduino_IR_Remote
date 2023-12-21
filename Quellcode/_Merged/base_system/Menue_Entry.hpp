#ifndef MENUE_ENTRY_HPP
#define MENUE_ENTRY_HPP

#include "base_definitions.h"
class Menue_Entry{
    //jedes Objekt dieser Klasse stllt einen Menue-Eintrag dar
public:
    //Callback für Funktionsaufruf
    using FKT_Callback = void (*)(int);

    Menue_Entry(String name, int value, bool nv_entry, enum Menues m_entry,FKT_Callback fkt_callback):
    Name(name),Value(value),NV_Entry(nv_entry),M_Entry(m_entry),FKT_Callback_m(fkt_callback){

    }

    String Name;
    int Value;
    bool NV_Entry;
    enum Menues M_Entry;
    FKT_Callback FKT_Callback_m;
};

#endif //MENUE_ENTRY_HPP