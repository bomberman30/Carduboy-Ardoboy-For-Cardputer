/**
 * @file Arduboy2Beep.cpp
 * \brief
 * Classes to generate simple square wave tones on the Arduboy speaker pins.
 */

#include <Arduino.h>
#include "Arduboy2Beep.h"
#include "Arduboy2Core.h"
#include <M5Cardputer.h>
uint8_t BeepPin1::duration = 0;

void BeepPin1::begin() {}

void BeepPin1::tone(uint16_t count){

}

void BeepPin1::tone(uint16_t hz, uint8_t dur)
{
    // תיקון תדר לטווח בטוח
    if (hz < 20)      hz = 20;
    if (hz > 20000)   hz = 20000;

    // תיקון משך מינימלי
    if (dur == 0) dur = 1;

    // הגבלת משך מקסימלי (הגנה פנימית)
    if (dur > 255) dur = 255;

    M5Cardputer.Speaker.tone(hz, dur);
}

void BeepPin1::timer(){}

void BeepPin1::noTone(){
#ifdef ADAFRUIT
  ::noTone(PIN_SPEAKER_1);
#endif
}

uint8_t BeepPin2::duration = 0;

void BeepPin2::begin(){}

void BeepPin2::tone(uint16_t count){
#ifdef ADAFRUIT
  ::tone(PIN_SPEAKER_2, count);
#endif
}

void BeepPin2::tone(uint16_t count, uint8_t dur){
#ifdef ADAFRUIT
  ::tone(PIN_SPEAKER_2, count, dur);
#endif
}

void BeepPin2::timer(){}

void BeepPin2::noTone(){
#ifdef ADAFRUIT
  ::noTone(PIN_SPEAKER_2);
#endif
}