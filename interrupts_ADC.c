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

int STATE = ZERO;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int right_detector = ZERO;
extern volatile unsigned int left_detector = ZERO;

#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void) {
	switch(__even_in_range(ADCIV, ADCIV_ADCIFG)) {
		case ADCIV_NONE:
			break;
		case ADCIV_ADCOVIFG:
			break;
		case ADCIV_ADCTOVIFG:
			break;
		case ADCIV_ADCHIIFG:
			break;
		case ADCIV_ADCLOIFG:
			break;
		case ADCIV_ADCINIFG:
			break;
		case ADCIV_ADCIFG:
			ADCCTL0 &= ~ADCENC; // disable interrupt
			switch (++STATE) {
	        case INDEX_ONE:
	          ADC_Thumb = ADCMEM0;
	          ADCMCTL0 &= ~ADCINCH_5;
	          ADCMCTL0 |= ADCINCH_2;
	          break;
	        case INDEX_TWO:
	          left_detector = ADCMEM0;
	          ADCMCTL0 &= ~ADCINCH_2;
	          ADCMCTL0 |= ADCINCH_3;
	          break;
	        case INDEX_THREE:
	          right_detector = ADCMEM0;
	          ADCMCTL0 &= ~ADCINCH_3;
	          ADCMCTL0 |= ADCINCH_5;
	          break;
	        default:
	          STATE = ZERO;
			}	
			ADCCTL0 |= ADCENC;
			ADCCTL0 |= ADCSC;	    
			break;
		default:
			break;
	}
}



