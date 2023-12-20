#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

//Heraus finden, welcher Arduino verwendet wird
// -> gibt dann unterschiedliche Pinzuweisungen

#if defined(__AVR_ATmega328P__)  // Arduino Uno
  #define Pin_CLK_RSW 4   // Clock-Pin -> Generiert Interrupt
  #define Pin_DT_RSW 3    // Drehschalter
  #define Pin_SW_RSW 2   // Knopf (Drückschalter)
  #pragma message("Pins for Arduino UNO enabled")
#elif defined(__AVR_ATmega32U4__)  // Arduino Leonardo
  #define Pin_CLK_RSW 2  // Clock-Pin -> Generiert Interrupt
  #define Pin_DT_RSW 3    // Drehschalter
  #define Pin_SW_RSW 4    // Knopf (Drückschalter)
  #pragma message("Pins for Arduino Leonardo enabled")
#else
  #error "Unbekanntes Board"
#endif

enum Display_Commands{
  Display_UP =0,
  Display_DOWN=1,
  Display_OK=2
};

#endif //PIN_DEFINES_H
