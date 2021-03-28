// ------------------------------------------------------------------------------
//
//  Description: This file contains the macros used by the other files
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include "ports.h"

// main.c MACROS=================================================================
#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF    (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED)
#define ALWAYS                         (1)
#define RESET_STATE                    (0)
#define RED_LED                     (0x01) // RED LED 0
#define GRN_LED                     (0x40) // GREEN LED 1
#define R_WHEEL_FORWARD      (P6OUT |= R_FORWARD)
#define L_WHEEL_FORWARD      (P6OUT |= L_FORWARD)
#define R_WHEEL_OFF          (P6OUT &= ~R_FORWARD)
#define L_WHEEL_OFF          (P6OUT &= ~L_FORWARD)
// make a function to see if reverse is called when forward is 
// Magic Numbers
#define DISPLAY_LINE_SIZE1 (4)
#define DISP_VAL_2 (10)
#define PORT_HIGH (0xFF)
#define PORT_LOW (0x00)
#define DL_ZERO_INDEX (0)
#define DL_FIRST_INDEX (1)
#define DL_SEC_INDEX (2)
#define DL_THIRD_INDEX (3)
#define DISPLAY_LINE_SIZE2 (11)
#define DISPLAY_SIZE (4)
#define HIGH (1)
#define LOW (0)
#define CASE1 (250)
#define CASE2 (200)
#define CASE3 (150)
#define CASE4 (100)
#define CASE5 (50)
// Main while loop switch cases
#define Time_Sequence_Rate (50) // 50 millisecods
#define S1250 (1250/Time_Sequence_Rate) // 1.25 seconds
#define S1000 (1000/Time_Sequence_Rate) // 1 second
#define S750 (750/Time_Sequence_Rate) // 0.75 seconds
#define S500 (500/Time_Sequence_Rate) // 0.50 seconds
#define S250 (250/Time_Sequence_Rate) // 0.25 seconds
#define FIFTY_MS_COUNT (10)
#define ONE_SEC_COUNT (20)
#define HUNDRED_MS_COUNT (2)
#define TB0CCR0_INTERVAL (25000) // 8,000,000/2/8/[1/50msec]
#define TB0CCR1_INTERVAL (25000) // 8,000,000/2/8/[1/50msec] --> want 800msec
#define TB0CCR2_INTERVAL (25000) // 8,000,000/2/8/[1/50msec]
#define TB1CCR0_INTERVAL (25000)
#define RESET_REGISTER (0x0000)
#define DISPLAY_UPDATE (3)
#define TIMER_INTER_TWO (2)
#define TIMER_INTER_FOUR (4)
#define TIMER_INTER_FOURTEEN (14)
#define DEBOUNCE_TIME (15)

// Magic Numbers
#define INIT_VALUE (0)
#define ST_INIT (3)
#define TRI_INIT (6)
#define FIG_INIT (2)
#define INIT_ONE (1)
#define INIT_TWO (2)
#define SICKO_MODE (11)


// clocks.c MACROS=================================================================
#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)
// Magic Numbers
#define CSCTL2_ADDER 		(243)
#define DELAY_NUM 			(3)
#define HEX_HIGH 			(0xffff)
#define ZERO 				(0)
#define CSCTL0_INIT 		(0x100)
#define THREE_GRAND 		(3000)
#define NEW_DCO_VAL 		(0x01ff)
#define DCO_FREQ_VAL 		(0x0070)
#define FOUR 				(4)
#define ONE 				(1)
#define BIT_EIGHT 			(256)


// switches.c MACROS=================================================================
#define USE_GPIO		(0x00)
#define USE_SMCLK		(0x01)


 
// ADC MACROS=================================================================
#define ADC_CHAR_SIZE (11)
#define NEG_ONE (-1)
#define DETECT_WHITE (300)
#define DETECT_BLACK (800)
#define HEX_ADD (0x30)
#define HIGH_HEX (999)
#define THOUSAND (1000)
#define LOW_HEX (99)
#define HUNDRED (100)


// HEXtoBCD MACROS=================================================================
#define INDEX_ONE (1)
#define INDEX_TWO (2)
#define INDEX_THREE (3)
#define INDEX_FOUR (4)
#define INDEX_FIVE (5)
#define INDEX_SIX (6)
#define INDEX_SEVEN (7)
#define INDEX_EIGHT (8)
#define INDEX_NINE (9)
#define INDEX_TEN (10)


// Line Position MACROS=================================================================
#define LEFT (2)
#define RIGHT (1)
#define ON_WHITE (0)
#define ON_BLACK (3)


#define PAUSE_TIME (2500)
#define MAX_TIME (310)
#define RETURN_TIME (315)
#define BACK_IN_TIME (335)



// PWM movement MACROS=================================================================
#define RIGHT_FORWARD_SPEED (TB3CCR1) 
#define LEFT_FORWARD_SPEED (TB3CCR2) 
#define RIGHT_REVERSE_SPEED (TB3CCR3) 
#define LEFT_REVERSE_SPEED (TB3CCR4)
#define WHEEL_PERIOD (40000) // 12000 is 30%
#define WHEEL_OFF (0)
#define MAX_PWM (400)


// Serial Communications macros 
#define BEGINNING (0)
#define SMALL_RING_SIZE (64)
#define LARGE_RING_SIZE (12)
#define BAUD_RATE_ONE (0x5551)
#define BAUD_RATE_TWO (0x4A11)
#define INTERRUPT8    (0x08)
#define INTERRUPTD    (0x0D)
#define INTERRUPTA    (0x0A)

// states:
#define WAIT (0)
#define RECEIVE (1)
#define PAUSE (2)
#define TRANSMIT (3)
#define PAUSE2 (4)


// IOT macros:
#define IP_START (68)
#define IP_END (80)
#define IP_SIZE (30)
#define COMMAND_SIZE (20)
#define ASCII_TO_DEC (0x30)
#define INDEX_ELEVEN (11)
#define INDEX_TWELVE (12)
#define INDEX_THIRTEEN (13)
#define INDEX_FOURTEEN (14)
#define INDEX_FIFTEEN (15)
#define INDEX_SIXTEEN (16)
#define INDEX_SEVENTEEN (17)
#define INDEX_EIGHTEEN (18)
#define INDEX_NINETEEN (19)
#define HUNDRED_MULT (100)


//States for moving
// #define HOLD_UP (0)
#define SINGLE_COMMAND (0)
#define LINE_SECTION (1)

// states for getting ip:
#define IS_IT_A (0)
#define IS_IT_D1 (1)
#define IS_IT_D2 (2)
#define IS_IT_R (3)
#define IS_IT_EQ (4)

// states for fixing disassociation
#define IS_IT_DIS (0)
#define IS_IT_I (1)
#define IS_IT_S (2)

#define SETUP_TIME (25)


// UPDATED Speed macros for IOT movement control
#define LEFT_TURN_SPEED (12000)
#define RIGHT_TURN_SPEED (15000)

#define FORWARD_L (20000)
#define FORWARD_R (20000)
#define REVERSE_L (20000)
#define REVERSE_R (20000)

#define STRAIGHT_FORWARD_L (15000)
#define STRAIGHT_FORWARD_R (20000)

#define SLOW_STRAIGHT_L (12000)
#define SLOW_STRAIGHT_R (8000)

// line following state machine macros
#define START (1)
#define INIT_PAUSE (2)
#define INTERCEPT (3)
#define PAUSE_ONE (4)
#define TURN (5)
#define PAUSE_TWO (6)
#define LEADING_LINE (7)
#define PAUSE3 (8)
#define TURN2 (9)
#define CIRCLE (10)
#define RETURN (11)
#define END (12)
#define START2 (13)

#define LINE_TIME (300)














