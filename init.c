// ------------------------------------------------------------------------------
//
//  Description: This file initializes the board    
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=INIT_VALUE;i<SICKO_MODE;i++){
    display_line[INIT_VALUE][i] = RESET_STATE;
    display_line[INIT_ONE][i] = RESET_STATE;
    display_line[INIT_TWO][i] = RESET_STATE;
    display_line[ST_INIT][i] = RESET_STATE;
  }
  display_line[INIT_VALUE][DISP_VAL_2] = INIT_VALUE;
  display_line[INIT_ONE][DISP_VAL_2] = INIT_VALUE;
  display_line[INIT_TWO][DISP_VAL_2] = INIT_VALUE;
  display_line[ST_INIT][DISP_VAL_2] = INIT_VALUE;

  display[INIT_VALUE] = &display_line[INIT_VALUE][INIT_VALUE];
  display[INIT_ONE] = &display_line[INIT_ONE][INIT_VALUE];
  display[INIT_TWO] = &display_line[INIT_TWO][INIT_VALUE];
  display[ST_INIT] = &display_line[ST_INIT][INIT_VALUE];
  update_display = INIT_VALUE;
  update_display_count = INIT_VALUE;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}