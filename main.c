//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Init_LEDs(void);

 // Global Variables
volatile char slow_input_down;
extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
// ADC display array

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
extern volatile unsigned int ADC_Thumb = ZERO;
extern unsigned int UCA1_index;
extern unsigned int UCA0_index;
extern char test_command[INDEX_TEN];
extern volatile int START_IOT;
extern volatile int initialize = ZERO;
extern volatile int START_MOVE = ZERO;
extern volatile int transcribe_done;
extern int disp_iot = ZERO;


void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Serial_UCA0();
  Init_Serial_UCA1();
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC
//  __delay_cycles(1000000);
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[DL_ZERO_INDEX], "WAITING   ");
  update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
  strcpy(display_line[DL_FIRST_INDEX], "FOR INPUT ");
  update_string(display_line[DL_FIRST_INDEX], DL_FIRST_INDEX);
  strcpy(display_line[DL_SEC_INDEX], "          ");
  update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
 Display_Update(INDEX_THREE,INDEX_ONE,ZERO,ZERO);

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    if (START_IOT) {
      P5OUT |= IOT_RESET;
      START_IOT = ZERO;
    }

    LEDs_Blink();
    Line_Position();

    if (initialize) {
      // use first couple of seconds to initialize everything needed for IOT
      initialize_iot();
      disp_iot = INDEX_ONE;
      initialize = ZERO; // will never enter this if statement again
    }
    
    if (disp_iot) {
      // Display_Clock();
      Display_IP(); // display IP
      // Display_Pads();
    }

    if (transcribe_done) {
      interpret_commands(); // if new command is detected, run it
    }   



    Switches_Process();                // Check for switch state change
    Display_Process();


//    Wheels();  
  }
//------------------------------------------------------------------------------
}
