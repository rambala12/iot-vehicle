// ------------------------------------------------------------------------------
//
//  Description: This file contains display information about what to place on LDC
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
extern int direction; // left (0) or right (1)
extern int line_pos; 
// 0: both on white // 1: right on white // 2: left on white // 3: both on black
extern int FOLLOW_STATE = INDEX_ONE;
int CIRC_STATE = ZERO;
int max_time; // time it takes to complete one circle
int wait = ZERO;
extern int direction; // left (0) or right (1)
extern int move_count;
extern volatile char command[COMMAND_SIZE];


extern volatile int circle_activated;
extern volatile int circle_count;

void Follow_Line_Circle() {
  switch (FOLLOW_STATE) {
    case START:
      line0_display(" BL START ");
      Forward_On((STRAIGHT_FORWARD_L + 12000), (STRAIGHT_FORWARD_R - 5000));
      if (wait > 2900) {
        Forward_Off();
        wait = ZERO;
        FOLLOW_STATE = START2;
      } else {
        wait++;
      }
      break;
    case START2:
      line0_display(" BL START ");
      Right_Turn(7000);
      if (wait > 930) {
        Forward_Off();
        wait = ZERO;
        FOLLOW_STATE = INIT_PAUSE;
      } else {
        wait++;
      }
      break;
    case INIT_PAUSE:
      // Pause using variable
      P5OUT |= IR_LED;
      if (wait > PAUSE_TIME) {
        wait = ZERO;
        FOLLOW_STATE = INTERCEPT;
      } else {
        wait++;
      }
      break;
    case INTERCEPT:
      line0_display("INTERCEPT ");
      Forward_On((STRAIGHT_FORWARD_L), (STRAIGHT_FORWARD_R)); // 20, 15 --> left, right
      if (line_pos == ON_BLACK) {
        Forward_Off();
        FOLLOW_STATE = PAUSE_ONE;
      }
      break;
    case PAUSE_ONE:
      line0_display("  PAUSE   ");
      // Pause using variable
      if (wait > (PAUSE_TIME + 200)) {
        wait = ZERO;
        FOLLOW_STATE = TURN;
      } else {
        wait++;
      }
      break;
    case TURN:
      line0_display("   TURN   ");
      // Turn car to the left until line_pos = 1
      if (line_pos == RIGHT) {
        Forward_Off();
        FOLLOW_STATE = PAUSE_TWO;
      } else {
        Left_Turn(8000); // 8000
      }
      break;
    case PAUSE_TWO:
      line0_display("  PAUSE2  ");
      // Pause using variable
      if (wait > PAUSE_TIME) { // 2500
        wait = ZERO;
        FOLLOW_STATE = LEADING_LINE;
      } else {
        wait++;
      }
      break;
    case LEADING_LINE:
      line0_display("BL TRAVEL ");
      circle_routine();
      // use timer to exit
      if (wait > (PAUSE_TIME - 200)) {
        wait = ZERO;
        Forward_Off();
        FOLLOW_STATE = PAUSE3;
      } else {
        wait++;
      }
      break;
    case PAUSE3:
      line0_display("  PAUSE3  ");
      // Pause using variable
      if (wait > PAUSE_TIME) {
        wait = ZERO;
        FOLLOW_STATE = TURN2;
      } else {
        wait++;
      }
      break;
    case TURN2: 
      line0_display("   TURN2   ");
      if (line_pos == LEFT) {
        Forward_Off();
        FOLLOW_STATE = CIRCLE;
      } else {
        Right_Turn(7500);
      }
      break;
    case CIRCLE:
      line0_display("BL CIRCLE ");
      // activate a timer once you enter this state
      //circle_activated = INDEX_ONE;
      clock_circle_routine();
      // if command is detected, exit circle
      if (command[INDEX_THIRTEEN] == 'S') { // A button on xbox
        FOLLOW_STATE = END;
      }
      break;
    case END:
      line0_display("BL STOP   ");
      Forward_On(STRAIGHT_FORWARD_L, STRAIGHT_FORWARD_R);
      if (wait > PAUSE_TIME) {
        wait = ZERO;
        FOLLOW_STATE = RETURN;
      } else {
        wait++;
      }
      P5OUT &= ~IR_LED;
      break;
    case RETURN:
      line0_display("WE MADE IT");
      Forward_Off();
      break;
    default: 
      break;
  }
}

void circle_routine() {
  if (line_pos == RIGHT || line_pos == ON_BLACK) {
    Forward_On(SLOW_STRAIGHT_L, SLOW_STRAIGHT_R);
  } else if (line_pos == ON_WHITE) {
    Left_Turn(8000);
  }
}

void clock_circle_routine() {
  if (line_pos == LEFT || line_pos == ON_BLACK) {
    Forward_On((STRAIGHT_FORWARD_L + 3000), (STRAIGHT_FORWARD_R - 4000));
  } else if (line_pos == ON_WHITE) {
    Right_Turn(7000);
  }
}

