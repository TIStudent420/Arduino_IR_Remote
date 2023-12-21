#include <Arduino.h>

#include "IRremote_IR_Reciver.hpp"
#include "base_definitions.h"
#include <IRremote.h>

IRrecv IRrecv_OS_1838B;

IR_Revicer::IR_Revicer(){}

void IR_Revicer::Init(){
  IRrecv_OS_1838B.enableIRIn();
  IRrecv_OS_1838B.begin(Pin_IR_RECV,true,Pin_IR_RECV_FEEDBACK); 
  printActiveIRProtocols(&Serial);
}

void IR_Revicer::Recive(){
  if (IRrecv_OS_1838B.decode()) {
    Serial.println("Munke");
    IRrecv_OS_1838B.printIRResultShort(&Serial);
    IRrecv_OS_1838B.printIRSendUsage(&Serial);
    IRrecv_OS_1838B.resume();
  }
}


