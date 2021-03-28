// ------------------------------------------------------------------------------
//
//  Description: This file programs the switches to toggle GPIO and SMCLK modes
//
//  Ram Bala
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include  "msp430.h"
#include "string.h"

// Global Variables
extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Switches_Process(void) { // Right Switch
	// if (!(P4IN & SW1)) {
 //          Init_Port3(USE_GPIO); // If the right switch is selected, toggle GPIO
 //    // Display setting, what display shows
 //          strcpy(display_line[DL_ZERO_INDEX], "   NCSU   ");
 //          update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
 //          strcpy(display_line[DL_FIRST_INDEX], " WOLFPACK ");
 //          update_string(display_line[DL_FIRST_INDEX], DL_FIRST_INDEX);
 //          strcpy(display_line[DL_SEC_INDEX], "   GPIO  ");
 //          update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
 //          enable_display_update();
	// }
	// if (!(P2IN & SW2)) { // Left Swi tch
 //          Init_Port3(USE_SMCLK); // If the left switch is selected, toggle SMCLK
 //    // Display setting
 //          strcpy(display_line[DL_ZERO_INDEX], "   NCSU   ");
 //          update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
 //          strcpy(display_line[DL_FIRST_INDEX], " WOLFPACK ");
 //          update_string(display_line[DL_FIRST_INDEX], DL_FIRST_INDEX);
 //          strcpy(display_line[DL_SEC_INDEX], "   SMCLK  ");
 //          update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
 //          enable_display_update();
	// }
}