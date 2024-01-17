
#ifndef BASE_DEFINITIONS_H
#define BASE_DEFINITIONS_H

#include <Arduino.h>

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

// jedes Enum staht für ein Menü
// jedes dieser Menüs hat Unterpunkte
// die anzahl, bezeichnung und funktion der Unterpunkte ist in der Menue_Control_Layer Implementiert
enum Menue_Titles{
  Menue_Entry_Greetings = 0,
  Funktion,
  Menue_Entry_Start,
  Menue_Entry_Senden,
  Menue_Entry_Empfangen,
  Menue_Entry_Saved,
};

enum protokoll_type_t {
    UNKNOWN_T = 0,
    PULSE_WIDTH_T,
    PULSE_DISTANCE_t,
    APPLE_t,
    DENON_t,
    JVC_t,
    LG_t,
    LG2_t,
    NEC_T,
    NEC2_T, /* NEC with full frame as repeat */
    ONKYO_T,
    PANASONIC_T,
    KASEIKYO_T,
    KASEIKYO_DENON_T,
    KASEIKYO_SHARP_T,
    KASEIKYO_JVC_T,
    KASEIKYO_MITSUBISHI_t,
    RC5_T,
    RC6_t,
    SAMSUNG_T,
    SAMSUNG48_T,
    SAMSUNG_LG_T,
    SHARP_T,
    SONY_T,
    /* Now the exotic protocols */
    BANG_OLUFSEN_t,
    BOSEWAVE_T,
    LEGO_PF_T,
    MAGIQUEST_T,
    WHYNTER_T,
    FAST_T
} ;

//Struckut zum senden und empfanegn von daten
struct IRData_s {
    protokoll_type_t protocol; ///< UNKNOWN, NEC, SONY, RC5, PULSE_DISTANCE, ...
    uint16_t address; ///< Decoded address, Distance protocol (tMarkTicksLong (if tMarkTicksLong == 0, then tMarkTicksShort) << 8) | tSpaceTicksLong
    uint16_t command;       ///< Decoded command, Distance protocol (tMarkTicksShort << 8) | tSpaceTicksShort
};

struct Menue_Entry_s{  //Struktur eines Menü-Eintrages
  String name;
  IRData_s data;
  enum Menue_Titles followed_by;
};

#endif //BASE_DEFINITIONS_H
