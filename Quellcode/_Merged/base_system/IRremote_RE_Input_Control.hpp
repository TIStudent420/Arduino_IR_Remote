#ifndef  IRREMOTE_RE_INPUT_CONTROL_HPP
#define  IRREMOTE_RE_INPUT_CONTROL_HPP

#import <Encoder.h> //Encoder-Bibliothek im Quellcode-Ordner

//RE = Rotary Encoder (Bauteilbezeichnung)
class RE_Input_Control{
public:
  //Callback für Displaysteuerung
  using Controls_Callback = void (*)(int);
  
  RE_Input_Control(int clk_pin, int dt_pin, int sw_pin); //Konstruktor
  void Init(); //Initilisierungs funktion

  void Checkup(Controls_Callback callback);
  
private:
  int Pin_SW;
  Encoder Rotary_Encoder_PC1;
};

#endif //IRREMOTE_RE_INPUT_CONTROL_HPP
