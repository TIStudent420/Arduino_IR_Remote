#ifndef BASE_DEFINITIONS_H
#define BASE_DEFINITIONS_H

//Pinzuweisung basiert auf dem jeweiligen verwendeten Board (nicht so wichtig)
//   RE => Rotary Encoder
#if defined(__AVR_ATmega328P__)  // Arduino Uno
  #define Pin_RE_CLK  4   // Drehschalter (RE) Clock Pin 
  #define Pin_RE_DT   3   // Drehschalter (RE) Daten Pin
  #define Pin_RE_SW   2   // Drehschalter (RE) Knopf Pin
  #define Pin_LCD_RS  5   // Display (LCD) 
  #define Pin_LCD_E   6   // Display (LCD)
  #define Pin_LCD_D4  7   // Display (LCD)
  #define Pin_LCD_D5  8   // Display (LCD)
  #define Pin_LCD_D6  9   // Display (LCD)
  #define Pin_LCD_D7  10  // Display (LCD)
  #define Pin_IR_RECV 11  // IR Sensor (RECV)
  #define Pin_IR_RECV_FEEDBACK 0 // Signal-LED für das Empfangen von Daten
  #define Pin_IR_LED  12  // IR Sender (LED)
  #define Pin_IR_LED_FEEDBACK 1 // Signal-LED für das Senden von Daten
  #pragma message("Pins for Arduino UNO enabled") //Info in Kompielerausgabe, welches Board erkannt wurde
#elif defined(__AVR_ATmega32U4__)  // Arduino Leonardo
  //#error "Leonardo-Board: Pins noch nicht definiert"
  #define Pin_RE_CLK  0   // Drehschalter (RE) Clock Pin 
  #define Pin_RE_DT   0   // Drehschalter (RE) Daten Pin
  #define Pin_RE_SW   0   // Drehschalter (RE) Knopf Pin
  #define Pin_LCD_RS  0   // Display (LCD) 
  #define Pin_LCD_E   0   // Display (LCD)
  #define Pin_LCD_D4  0   // Display (LCD)
  #define Pin_LCD_D5  0   // Display (LCD)
  #define Pin_LCD_D6  0   // Display (LCD)
  #define Pin_LCD_D7  0  // Display (LCD)
  #define Pin_IR_RECV 3  // IR Sensor (RECV)
  #define Pin_IR_RECV_FEEDBACK 0 // Signal-LED für das Empfangen von Daten
  #define Pin_IR_LED  0  // IR Sender (LED)
  #define Pin_IR_LED_FEEDBACK 0 // Signal-LED für das Senden von Daten
  #pragma message("Pins for Arduino Leonardo enabled") //Info in Kompielerausgabe, welches Board erkannt wurde
#else
  #error "Unbekanntes Board"
#endif

enum Display_Commands{
  Display_UP =0,
  Display_DOWN=1,
  Display_OK=2
};
#endif //BASE_DEFINITIONS_H
