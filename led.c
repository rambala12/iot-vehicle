// ------------------------------------------------------------------------------
//
//  Description: This file contains the LED Initialization
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern volatile unsigned char display_changed;
extern volatile char one_time = ONE;
extern volatile unsigned int Time_Sequence = ZERO;


void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  GREEN_LED_OFF;
  RED_LED_OFF;
//------------------------------------------------------------------------------
}

void LEDs_Blink(void) {
	switch(Time_Sequence){
     case S1250:                        //
      if(one_time){
        Init_LEDs();
        //lcd_BIG_mid();
        display_changed = HIGH;
        one_time = LOW;
      }
      Time_Sequence = LOW;             //
      break;
    case S1000:                        //
      if(one_time){
        GREEN_LED_ON;            // Change State of LED 5
        one_time = LOW;
      }
      R_WHEEL_OFF;
      L_WHEEL_OFF;
      break;
    case S750:                         //
      if(one_time){
        RED_LED_ON;            // Change State of LED 4
        GREEN_LED_OFF;           // Change State of LED 5
        one_time = LOW;
      }
      break;
    case S500:                         //
      if(one_time){
        lcd_4line();
        GREEN_LED_ON;            // Change State of LED 5
        display_changed = HIGH;
        one_time = LOW;
      }
      break;
    case S250:                        //
      if(one_time){
        RED_LED_OFF;           // Change State of LED 4
        GREEN_LED_OFF;           // Change State of LED 5
        one_time = LOW;
      }
      break;                         //
    default: break;
  }
}


