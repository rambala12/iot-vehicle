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
extern char adc_char[ADC_CHAR_SIZE];
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int left_detector;
extern volatile unsigned int right_detector;
extern volatile int EmitterValue;
extern int direction = NEG_ONE; // left (0) or right (1)
extern int line_pos = NEG_ONE;
extern int on_line = ZERO;
extern int move_count;
extern int mat_counter;


// Determines position of line ==========================================================


void Line_Position() {
  if (((right_detector < DETECT_WHITE) && (left_detector > DETECT_BLACK))) {
    line_pos = LEFT; // left on white
    //strcpy(display_line[DL_THIRD_INDEX], "OFF  RIGHT");
  } else if (((left_detector < DETECT_WHITE) && (right_detector > DETECT_BLACK))) {
    line_pos = RIGHT; // right on white
    //strcpy(display_line[DL_THIRD_INDEX], "OFF   LEFT");
  } else if (((right_detector < DETECT_WHITE) && (left_detector < DETECT_WHITE))) {
    line_pos = ON_WHITE; // both white
    //strcpy(display_line[DL_THIRD_INDEX], "OFF   NONE");
    on_line = 0;
  } else if (((right_detector > DETECT_BLACK) && (left_detector > DETECT_BLACK))) {
    line_pos = ON_BLACK; // both black
    on_line = 1;
  } 
}

// Display number of pads

void Display_Pads() {
  HEXtoBCD(mat_counter);
  line3_display(adc_char);
}

// Display for millisecond clock ==============================================

void Display_Clock() {
  HEXtoBCD(move_count);
  strcpy(display_line[DL_ZERO_INDEX], adc_char);
  update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
  display_changed = ONE;
}

// Display for ADC values and line position ==============================================

void Display_Thumb() {
  HEXtoBCD(ADC_Thumb);
  strcpy(display_line[DL_ZERO_INDEX], adc_char);
  update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
  display_changed = ONE;
}

void Display_L_Detector() {
  HEXtoBCD(left_detector);
  strcpy(display_line[DL_FIRST_INDEX], adc_char);
  update_string(display_line[DL_FIRST_INDEX], DL_FIRST_INDEX);
  display_changed = ONE;
}

void Display_R_Detector() {
  HEXtoBCD(right_detector);
  strcpy(display_line[DL_SEC_INDEX], adc_char);
  update_string(display_line[DL_SEC_INDEX], DL_SEC_INDEX);
  display_changed = ONE;
}

// Displaying any word to LCD
void line0_display(char *str) {
  strcpy(display_line[DL_ZERO_INDEX], str);
  update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
  display_changed = ONE;
}

void line1_display(char *str) {
  strcpy(display_line[DL_FIRST_INDEX], str);
  update_string(display_line[DL_FIRST_INDEX], DL_FIRST_INDEX);
  display_changed = ONE;
}

void line2_display(char *str) {
  strcpy(display_line[DL_SEC_INDEX], str);
  update_string(display_line[DL_SEC_INDEX], DL_SEC_INDEX);
  display_changed = ONE;
}

void line3_display(char *str) {
  strcpy(display_line[DL_THIRD_INDEX], str);
  update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
  display_changed = ONE;
}

void clear_display() {
  line0_display("          ");
  line1_display("          ");
  line2_display("          ");
  line3_display("          ");
}

void BIG_Display(char *str1, char *str2, char *str3) {
  strcpy(display_line[DL_ZERO_INDEX], str1);
  update_string(display_line[DL_ZERO_INDEX], DL_ZERO_INDEX);
  strcpy(display_line[DL_FIRST_INDEX], str2);
  update_string(display_line[DL_FIRST_INDEX], DL_FIRST_INDEX);
  strcpy(display_line[DL_SEC_INDEX], str3);
  update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
}

// void Display_Line_Position() {
//   if (((right_detector < DETECT_WHITE) && (left_detector > DETECT_BLACK))) {
//     if (line_pos == INDEX_THREE) { // right was on white before, now left on white
//       // strcpy(display_line[DL_THIRD_INDEX], "      LEFT");
//       // update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
//       // display_changed = ONE;
//       direction = ZERO;
//     }
//     if (line_pos == ZERO) {
//       // strcpy(display_line[DL_THIRD_INDEX], "     RIGHT");
//       // update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
//       // display_changed = ONE;
//       direction = INDEX_ONE;
//     }
//     line_pos = LEFT; // left on white
//     //strcpy(display_line[DL_THIRD_INDEX], "OFF  RIGHT");
//   } else if (((left_detector < DETECT_WHITE) && (right_detector > DETECT_BLACK))) {
//     if (line_pos == INDEX_THREE) { // right was on white before, now left on white
//       // strcpy(display_line[DL_THIRD_INDEX], "     RIGHT");
//       // update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
//       // display_changed = ONE;
//       direction = INDEX_ONE;
//     }
//     if (line_pos == ZERO) {
//       // strcpy(display_line[DL_THIRD_INDEX], "      LEFT");
//       // update_string(display_line[DL_THIRD_INDEX], DL_THIRD_INDEX);
//       // display_changed = ONE;
//       direction = ZERO;
//     }
//     line_pos = RIGHT; // right on white
//     //strcpy(display_line[DL_THIRD_INDEX], "OFF   LEFT");
//   } else if (((right_detector < DETECT_WHITE) && (left_detector < DETECT_WHITE))) {
//     line_pos = ON_WHITE; // both white
//     //strcpy(display_line[DL_THIRD_INDEX], "OFF   NONE");
//   } else if (((right_detector > DETECT_BLACK) && (left_detector > DETECT_BLACK))) {
//     line_pos = ON_BLACK; // both black
//   } 
// }



