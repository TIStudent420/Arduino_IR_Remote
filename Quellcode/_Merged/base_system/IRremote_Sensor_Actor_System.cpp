#include "IRremote_Sensor_Actor_System.hpp"

#include <IRremote.h>

IRrecv IRrecv_OS_1838B;

Sensor_Actor_System::Sensor_Actor_System(int recv_pin, int recv_feedback_pin, int send_pin, int send_feedback_pin){
  Pin_Recv=recv_pin;
  Pin_Recv_Feedback=recv_feedback_pin;
  Pin_Send=send_pin;
  Pin_Send_Feedback=send_feedback_pin;
}

void Sensor_Actor_System::Init(){
  //Empfänger init:
  IRrecv_OS_1838B.enableIRIn();
  IRrecv_OS_1838B.begin(Pin_Recv,true,Pin_Recv_Feedback); 
  printActiveIRProtocols(&Serial);
}

void Sensor_Actor_System::Recive(){
  if (IRrecv_OS_1838B.decode()) {
    IRrecv_OS_1838B.printIRResultShort(&Serial);
    IRrecv_OS_1838B.printIRSendUsage(&Serial);
    IRrecv_OS_1838B.resume();
  }
}
