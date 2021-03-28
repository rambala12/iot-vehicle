//------------------------------------------------------------------------------
//
//  Description: This file contains the timer interrupts
//
//
//  Ram Bala
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include  "msp430.h"

unsigned int blink_count = ZERO;
unsigned int display_count = ZERO;
unsigned int ping_count = ZERO;

extern int move_count = ZERO;
extern int serial_count;
unsigned int move_timer = ZERO;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int debounce_count = ZERO;
extern volatile int pause_activated = ZERO;
extern volatile int START_IOT = ZERO;
unsigned int iot_timer = ZERO;

unsigned int init_timer = ZERO;
unsigned int init_count = ZERO;

// globals for setting movement timer based on command
extern volatile int command_activated = ZERO;
unsigned int run_timer = ZERO;
extern volatile int run_count = ZERO;
extern volatile int initialize;

extern volatile int circle_activated = ZERO;
unsigned int circle_timer = ZERO;
extern volatile int circle_count = ZERO;
extern int disp_iot;


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
	//--------------------------------------------------------------------
	// TimerB0 0 Interrupt handler
	//--------------------------------------------------------------------
	// LCD Backlight
	// if(blink_count++ > FIFTY_MS_COUNT){
	// 	blink_count = ZERO; // Reset for next count
	//  	P6OUT ^= LCD_BACKLITE; // Flip State of LCD_BACKLITE
	// }
	if(display_count++ > DISPLAY_UPDATE) {
		display_count = ZERO;
		update_display = ONE;
	}
	if (disp_iot) {
		if (ping_count++ > DISPLAY_UPDATE) {
			ping_count = ZERO;
			move_count += INDEX_TWO; // if count increases, .2 second has passed
			sendToIOT("AT+Ping=google.com,1\r\n");
		}
	}
	// Time Sequence
	 one_time = ONE;
	 if(Time_Sequence++ > CASE1){
	 	Time_Sequence = ZERO;
	 }
	 TB0CCR0 += TB0CCR0_INTERVAL; // Add interval Offset to TACCR0
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void) {
	switch(__even_in_range(TB0IV, TIMER_INTER_FOURTEEN)) {
		case ZERO: break;
		case TIMER_INTER_TWO:
			// Timer debounce interrupt for switch 1
			if (debounce_count++ > DEBOUNCE_TIME) {
				debounce_count = ZERO;
				P4IE |= SW1;
				TB0CCTL1 &= ~CCIE;
				P4IFG &= ~SW1;
			}
			TB0CCR1 += TB0CCR1_INTERVAL;
			break;
		case TIMER_INTER_FOUR:
			if (debounce_count++ > DEBOUNCE_TIME) {
				debounce_count = ZERO;
				P2IE |= SW2;
				TB0CCTL2 &= ~CCIE;
				P2IFG &= ~SW2;
			}
			TB0CCR2 += TB0CCR2_INTERVAL;
			break;
		case TIMER_INTER_FOURTEEN:
			break;
		default: break;
	}
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void) {
	if (pause_activated) {
		if(move_timer++ > ONE_SEC_COUNT){
			move_timer = ZERO; // Reset for next count
			serial_count++; // if count increases, 1 second has passed
		}
		pause_activated = ZERO;
	}

	if (init_timer++ > HUNDRED_MS_COUNT) {
		init_timer = ZERO;
		init_count++;
		// if some time has passed, activate initialization
		if (init_count == SETUP_TIME) initialize = INDEX_ONE;
	}

	// timer for starting iot module initially
	if (iot_timer++ > HUNDRED_MS_COUNT) {
		iot_timer = ZERO;
		START_IOT = INDEX_ONE;
	}

	// if the command is ready to go, then the timer will activate for
	// allowing command to happen for that many seconds : use ms timer
	if (command_activated) {
		if (run_timer++ > DISPLAY_UPDATE) {
			run_timer = ZERO;
			run_count+= INDEX_TEN; // if run_count increases, .2 seconds has passed
		}
		//command_activated = ZERO;
	}
	// once command is done: RESET run_count back to 0

	// if (circle_activated) {
	// 	if (circle_timer++ > DISPLAY_UPDATE) {
	// 		circle_timer = ZERO;
	// 		circle_count+= INDEX_TWO; // if run_count increases, .2 seconds has passed
	// 	}
	// }


	TB1CCR0 += TB1CCR0_INTERVAL;
}




