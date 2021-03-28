//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupt 
//
//
//  Ram Bala
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include  "msp430.h"
#include "string.h"

// turn off port interrupt
// turn on debouncing
// when the switch is clicked turn off ccr0 (blinking)
// Turn CCR0 on
// Turn P4IE off (turn switch off)

// IN THE TIMER: ONCE TIMER (debounce_counter) COUNTS DOWN:
// turn switch back on 
extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;



#pragma vector = PORT4_VECTOR
__interrupt void switch_interrupt(void) {
	if (P4IFG & SW1) {
		strcpy(display_line[DL_THIRD_INDEX], "  115,200 ");
  		update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
  		display_changed = ONE;
    // iot
  	UCA0BRW = INDEX_FOUR;
		UCA0MCTLW = BAUD_RATE_ONE;

    // usb
    UCA1BRW = INDEX_FOUR;
    UCA1MCTLW = BAUD_RATE_ONE;

		TB0CCTL1 |= CCIE;
		P4IE &= ~SW1;
	}
}

#pragma vector = PORT2_VECTOR
__interrupt void switch_interrupt2(void) {
	if (P2IFG & SW2) {
		strcpy(display_line[DL_THIRD_INDEX], "  460,800 ");
  		update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
  		display_changed = ONE;
    // iot
		UCA0BRW = INDEX_ONE;
    UCA0MCTLW = BAUD_RATE_TWO;

    // usb
    UCA1BRW = INDEX_ONE;
    UCA1MCTLW = BAUD_RATE_TWO;

    	TB0CCTL2 |= CCIE;
		P2IE &= ~SW2;
	}
}

