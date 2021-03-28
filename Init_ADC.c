// ------------------------------------------------------------------------------
//
//  Description: This file initializes all ADC registers
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include "ports.h"
#include <string.h>

extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;
extern char adc_char[ADC_CHAR_SIZE] = "          ";

void Init_ADC(void) {
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) Pin 2 A2
// V_DETECT_R (0x08) Pin 3 A3
// V_THUMB (0x20) Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
  ADCCTL0 = ZERO;
  ADCCTL0 |= ADCSHT_2;
  ADCCTL0 |= ADCMSC;
  ADCCTL0 |= ADCON;

// ADCCTL1 Register
  ADCCTL2 = ZERO;
  ADCCTL1 |= ADCSHS_0;
  ADCCTL1 |= ADCSHP;
  ADCCTL1 &= ~ADCISSH;
  ADCCTL1 |= ADCDIV_0;
  ADCCTL1 |= ADCSSEL_0;
  ADCCTL1 |= ADCCONSEQ_0;
// ADCCTL1 & ADCBUSY  identifies a conversion is in process

// ADCCTL2 Register
  ADCCTL2 = ZERO;
  ADCCTL2 |= ADCPDIV0;
  ADCCTL2 |= ADCRES_2;
  ADCCTL2 &= ~ADCDF;
  ADCCTL2 &= ~ADCSR;

// ADCMCTL0 Register
  ADCMCTL0 |= ADCSREF_0;
  ADCMCTL0 |= ADCINCH_5;

  ADCIE |= ADCIE0;
  ADCCTL0 |= ADCENC;
  ADCCTL0 |= ADCSC;
}

//------------------------------------------------------------------------------ 
//****************************************************************************** 
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
// //------------------------------------------------------------------------------ 
void HEXtoBCD(int hex_value) {
  int value;
  value = ZERO;
  adc_char[INDEX_FIVE] = '0';
  while (hex_value > HIGH_HEX) {
    hex_value = hex_value - THOUSAND;
    value = value + ONE;
  }
  adc_char[INDEX_FIVE] = HEX_ADD + value;
  value = ZERO;
  while (hex_value > LOW_HEX) {
    hex_value = hex_value - HUNDRED;
    value = value + ONE;
  }
  adc_char[INDEX_SIX] = HEX_ADD + value;
  value = ZERO;
  while (hex_value > INDEX_NINE) {
    hex_value = hex_value - INDEX_TEN;
    value = value + ONE;
  }
  adc_char[INDEX_EIGHT] = '.';
  adc_char[INDEX_SEVEN] = HEX_ADD + value;
  adc_char[INDEX_NINE] = HEX_ADD + hex_value; 
  adc_char[INDEX_TEN] = '\0';
}
//****************************************************************************** 
//------------------------------------------------------------------------------




