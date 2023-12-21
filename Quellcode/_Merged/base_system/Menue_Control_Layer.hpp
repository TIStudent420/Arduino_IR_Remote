#ifndef MENUE_CONTROL_LAYER_HPP
#define MENUE_CONTROL_LAYER_HPP

#include "Menue_Entry.hpp"

class Menue_Control_Layer{

public:
    Menue_Control_Layer();

    void Get_Array_ptr(enum Menues);
    void Init_Menue_Arrays();
    void Manipulate_Menue_Arrays();

private:
  Menue_Entry Start_Menue[3];
  Menue_Entry Send_Menue[10];
  Menue_Entry Recive_Menue[10];

};

#endif //MENUE_CONTROL_LAYER_HPP