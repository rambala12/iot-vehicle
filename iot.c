//------------------------------------------------------------------------------
//
//  Description: This file contains the functions needed for getting commands from iot module 
//
//
//  Ram Bala
//  Feb 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"


extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
//char message[SMALL_RING_SIZE];
extern unsigned int UCA1_index;
extern unsigned int UCA0_index;
// extern int start_copy_iot = ZERO;
// extern int start_copy_usb = ZERO;
// extern unsigned int temp2;
// extern unsigned int temp;

// arrays for information
extern volatile char command[COMMAND_SIZE];
extern volatile char ip_address[IP_SIZE];
extern volatile int get_command;
extern volatile int command_start;
extern volatile int ip_reached = ZERO;
//char ssid[];
extern volatile int run_count;
extern volatile int command_activated;
extern volatile int transcribe_done;
int COMMAND_STATE = ZERO;
int command_time = ZERO;
char ip_copy[IP_SIZE] = {ZERO};
char ip_copy2[IP_SIZE] = {ZERO};
int left_pwm_value = ZERO;
int right_pwm_value = ZERO;
extern volatile int initialize;
extern int mat_counter = ZERO;
int toggle_led = ZERO;




void Display_IP() {
	lcd_4line();
	int i; int j; j = ZERO;
	// display IP address and ssid
	for (i = INDEX_ONE; i <= INDEX_SIX; i++) { //10.154
		ip_copy[j] = ip_address[i];
		j++;
	}
	ip_copy[INDEX_SIX] = ' ';
	ip_copy[INDEX_SEVEN] = ' ';
	ip_copy[INDEX_EIGHT] = ' ';
	ip_copy[INDEX_NINE] = ' ';
	ip_copy[INDEX_TEN] = ' ';

	j = ZERO;
	for (i = INDEX_SEVEN; i < INDEX_FOURTEEN; i++) {
		ip_copy2[j] = ip_address[i];
		j++;
	}
	ip_copy2[INDEX_SEVEN] = ' ';
	ip_copy2[INDEX_EIGHT] = ' ';
	ip_copy2[INDEX_NINE] = ' ';
	ip_copy2[INDEX_TEN] = ' ';

	line1_display(ip_copy);
	line2_display(ip_copy2);

	// Display clock
	// Display_Clock();
}


void interpret_commands() {
	lcd_BIG_mid();
	// command for mat: $[4 digit pin][command][time]
	// run_count is timer
	// command_activated

	// get the time command indicates for movement
	switch (COMMAND_STATE) {
		// case HOLD_UP:
		// 	// set state:
		// 	if (transcribe_done == INDEX_ONE) {
		// 		COMMAND_STATE = SINGLE_COMMAND;
		// 	}
		// 	break;
		case SINGLE_COMMAND:
			// reset transcribe_done
			transcribe_done = ZERO;
			// this way, when it returns to HOLD_UP, it will wait until another command is received
			//$1212F200
			// get time that command indicates
			command_time = ((string2dec(command[INDEX_SIX]) * HUNDRED_MULT) 
					+ (string2dec(command[INDEX_SEVEN]) * INDEX_TEN) 
					+ (string2dec(command[INDEX_EIGHT]) * INDEX_ONE));

			if ((command[INDEX_ONE] == '1') && (command[INDEX_TWO] == '2') 
					&& (command[INDEX_THREE] == '1') && (command[INDEX_FOUR] == '2')) {
			// Forward
				if (command[INDEX_FIVE] == 'F') {
					BIG_Display("          ", " FORWARD  ", "          ");
					command_activated = INDEX_ONE;
					while (command_time > run_count) { // as long as this is true, time has not passed
						// run command
						Forward_On(FORWARD_L, FORWARD_R); // left, right speed
					}
					Forward_Off();
					// reset run count and command_activated
					command_activated = ZERO;
					run_count = ZERO;
				}
				// Backward
				if (command[INDEX_FIVE] == 'B') {
					BIG_Display("          ", " REVERSE  ", "          ");
					command_activated = INDEX_ONE;
					while (command_time > run_count) { // as long as this is true, time has not passed
						// run command
						Reverse_On(REVERSE_L, REVERSE_R); // left, right
					}
					Reverse_Off();
					// reset run count and command_activated
					command_activated = ZERO;
					run_count = ZERO;

				}
				// Right
				if (command[INDEX_FIVE] == 'R') {
					BIG_Display("          ", "  RIGHT   ", "          ");
					command_activated = INDEX_ONE;
					while (command_time > run_count) { // as long as this is true, time has not passed
						// run command
						leftWheelForOn(LEFT_TURN_SPEED);
					}
					Forward_Off();
					// reset run count and command_activated
					command_activated = ZERO;
					run_count = ZERO;

				}
				// Left
				if (command[INDEX_FIVE] == 'L') {
					BIG_Display("          ", "   LEFT   ", "          ");
					command_activated = INDEX_ONE;
					while (command_time > run_count) { // as long as this is true, time has not passed
						// run command
						rightWheelForOn(RIGHT_TURN_SPEED);
					}
					Forward_Off();
					// reset run count and command_activated
					command_activated = ZERO;
					run_count = ZERO;
				}
			}

			// COMMAND_STATE = HOLD_UP;
			if (command[INDEX_THIRTEEN] == 'I') { // Y button
				mat_counter++;
				if (mat_counter > INDEX_EIGHT) mat_counter = ZERO;
			}

			// if button on controller is hit, start following line
			if (command[INDEX_THIRTEEN] == 'E') { // A button
				COMMAND_STATE = LINE_SECTION;
			}

			break;
		case LINE_SECTION:
			Follow_Line_Circle();
			break;
		default: break;
	}
}


int string2dec(char str) {
	return (str - ASCII_TO_DEC);
}


void initialize_iot() {
	sendToIOT("AT+NSTAT=?\r\n");
	sendToIOT("AT+Ping=google.com,1\r\n");
	sendToIOT("AT+NSTCP=1236,1\r\n");

	initialize = ZERO;
}

void sendToIOT(char* array) {
	int i = ZERO;
	while (INDEX_ONE) {
		while ((UCA0STATW & UCBUSY)); // block until A0 isnt transmitting or receiving
		UCA0TXBUF = array[i];
		if(array[i] == '\n') break;
		i++;
	}
}



