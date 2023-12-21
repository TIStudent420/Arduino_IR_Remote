#ifndef IRREMOTE_SENSOR_ACTOR_SYSTEM_HPP
#define IRREMOTE_SENSOR_ACTOR_SYSTEM_HPP

class Sensor_Actor_System {
public:
  Sensor_Actor_System(int recv_pin, int recv_feedback_pin, int send_pin, int send_feedback_pin);  //Konstruktor

  void Init();


  void Recive();
  void Send();
  
private:
  int Pin_Recv;
  int Pin_Recv_Feedback;
  int Pin_Send;
  int Pin_Send_Feedback;
};

#endif  //IRREMOTE_SENSOR_ACTOR_SYSTEM_HPP