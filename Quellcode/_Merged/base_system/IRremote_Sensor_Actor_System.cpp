//#include <memory>

#include "IRremote_Sensor_Actor_System.hpp"
#include <IRremote.h>
#include "base_definitions.h"

IRrecv IRrecv_OS_1838B;
IRsend irsend;

Sensor_Actor_System::Sensor_Actor_System(int recv_pin, int recv_feedback_pin, int send_pin, int send_feedback_pin){
  //Pinzuweisung für membervariablen dieser Klasse
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
  //pinMode(LED_BUILTIN, OUTPUT);  //FeedbackLED auf OUtput schalten?? 
  irsend.begin(Pin_IR_LED,true,Pin_IR_LED_FEEDBACK);
}

/**
 * # Recive
 * @note überprüft den Sensor
 * @return true: wenn daten erkannt wurden; 
 * @return false: wenn keine Daten empfangen werden konnten
*/
bool Sensor_Actor_System::Recive(IRData_s* recived_data){
    struct IRData_s recv_data; //Empfangene Daten (speicherplatz reservien)
    if (IRrecv_OS_1838B.decode()) {
      //recived_data=IRrecv_OS_1838B.decodedIRData;//??
      //Ausgabe der Empfangenen Daten
      IRrecv_OS_1838B.printIRResultShort(&Serial);
      IRrecv_OS_1838B.printIRSendUsage(&Serial);
      IRrecv_OS_1838B.resume();

      recived_data = new IRData_s();//Zeiger auf empfanene daten; neuen Speicherplatz allocieren, wird nach abspeichern wieder gelöscht

      //Daten übertragen 
      //TODO: Dummy-Daten entfernen
      recived_data->protocol=NEC_e;
      recived_data->command=0x14;

      return true; //Rückgabewert mit Informationen zum Senden
    }
    else
    {
    recived_data = nullptr;
    return false;
    }
}

//TODO: Implementierung für Weiter Protokolle

/**
 * # Send
 * @note sendet das angegebene Commando 
 * @param protokoll Art des Protokolls
 * @param adr addressse ict irgendwie immer 0
 * @param cmd der Command ist das entscheidende
 * @param repeats häufigkeit der Wiederhohlungen
 * 
 * @return 12 gesendet per NEC protokoll
 * @return -77, wenn Protokoll nicht erkannt oder Unbekannt
*/
int Sensor_Actor_System::Send(protokoll_type_t protokoll, int adr, int cmd, int repeats){
  switch (protokoll){
    case NEC_e:{
      irsend.sendNEC(adr, cmd, repeats);
      return 12;
    }
    case UNKNOWN_e:
    default:
      return -77;
  }
}
