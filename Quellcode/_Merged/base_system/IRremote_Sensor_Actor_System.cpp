#include "IRremote_Sensor_Actor_System.hpp"

#include <IRremote.h>
#include "base_definitions.h"

IRrecv IRrecv_OS_1838B;
IRsend irsend;

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
  //Sender init:
  //pinMode(LED_BUILTIN, OUTPUT);
  irsend.begin(Pin_IR_LED,true,Pin_IR_LED_FEEDBACK);
}

//TODO: welchen Rückgabewert könnte es geben?
bool Sensor_Actor_System::Recive(IRData_s *recived_data){
    struct IRData_s recv_data; //Empfangene Daten (speicherplatz reservien)
    if (IRrecv_OS_1838B.decode()) {
      //recived_data=IRrecv_OS_1838B.decodedIRData;
      IRrecv_OS_1838B.printIRResultShort(&Serial);
      IRrecv_OS_1838B.printIRSendUsage(&Serial);
      IRrecv_OS_1838B.resume();

      //Daten übertragen
      recv_data={NEC_T,0x00,0x12};

      recived_data = &recv_data; //Zeiger auf empfanene daten

      return true; //Rückgabewert mit Informationen zum Senden
    }
    return false;
}

//TODO: welche Informationen brauche ich zum Senden?
//Protokoll
//Command
//
//-> ist der Rüchgabewert des Recivers und ebenfalls sollte dies der Wert/Strucktur sein, welche im Menü gespeichert ist.
void Sensor_Actor_System::Send(int adr, int cmd, int repeats){
  irsend.sendNEC(adr, cmd, repeats);
}
