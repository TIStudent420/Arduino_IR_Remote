#ifndef IRREMOTE_SENSOR_ACTOR_SYSTEM_HPP
#define IRREMOTE_SENSOR_ACTOR_SYSTEM_HPP


#include "base_definitions.h"

class Sensor_Actor_System {
public:
  Sensor_Actor_System(int recv_pin, int recv_feedback_pin, int send_pin, int send_feedback_pin);  //Konstruktor

  void Init();


  bool Recive(IRData_s* recived_data);
  int Send(int adr, int cmd, int repeats);
  
private:
  int Pin_Recv;
  int Pin_Recv_Feedback;
  int Pin_Send;
  int Pin_Send_Feedback;
};

#endif  //IRREMOTE_SENSOR_ACTOR_SYSTEM_HPP
