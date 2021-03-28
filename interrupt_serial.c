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


extern volatile int usb_rx_ring_wr;
extern volatile int iot_rx_ring_wr = ZERO;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern char carryVariables[INDEX_TEN];
extern char test_command[INDEX_TEN] = " NCSU  #1 ";
extern unsigned int UCA1_index = ZERO;
extern unsigned int UCA0_index = ZERO;
extern volatile int serial_state; // 0: wait, 1: received
extern int start_copy_iot = ZERO;
extern int start_copy_usb = ZERO;
extern unsigned int temp2 = ZERO;
extern unsigned int temp = ZERO;

// arrays for information
extern volatile int get_command = ZERO;
extern volatile int command_start = ZERO;
extern volatile int ip_reached;
volatile int dis_fix;
extern volatile char command[COMMAND_SIZE] = {ZERO};
extern volatile char ip_address[IP_SIZE] = {ZERO};
int input = ZERO;
int input2 = ZERO;
char temp_char = ZERO;

// states
int IP_READ_STATE = ZERO;
int DIS_READ_STATE = ZERO;
extern volatile int transcribe_done = ZERO;
extern volatile int START_MOVE;


// SERIAL PORT INTERRUPTS ===========================================================

// IOT ==============================================================================
// check if command starts with $
#pragma vector = EUSCI_A0_VECTOR // machine
__interrupt void eUSCI_A0_ISR(void) { // is activated when a command is received
//int i;
// once interrupt is received, change state to RECEIVE


switch(__even_in_range(UCA0IV,INTERRUPT8)) {
  case ZERO: // Vector 0 - no interrupt
    break;
  case INDEX_TWO: // Vector 2 - RXIFG
    temp2 = iot_rx_ring_wr++;
    temp_char = UCA0RXBUF;

    // getting the command
    // register index of when command starts
    if (temp_char == '$') {
      get_command = INDEX_ONE;
      START_MOVE = INDEX_ONE;
    }
    if (get_command) {
      if (temp_char != '\r') {
        command[input] = temp_char;
        input++;
      } else { // at this point the command is done being transcribed
        command[INDEX_NINETEEN] = ZERO;
        transcribe_done = INDEX_ONE;
        input = ZERO;
        get_command = ZERO;
      }
    }

    // getting the ip address
    // use switch case
    switch (IP_READ_STATE) {
      case IS_IT_A:
        if (temp_char == 'a') {
          IP_READ_STATE = IS_IT_D1;
        } else {
          IP_READ_STATE = IS_IT_A;
        }
        break;
      case IS_IT_D1:
        if (temp_char == 'd') {
          IP_READ_STATE = IS_IT_D2;
        } else {
          IP_READ_STATE = IS_IT_A;
        }
        break;
      case IS_IT_D2:
        if (temp_char == 'd') {
          IP_READ_STATE = IS_IT_R;
        } else {
          IP_READ_STATE = IS_IT_A;
        }
        break;
      case IS_IT_R:
        if (temp_char == 'r') {
          IP_READ_STATE = IS_IT_EQ;
        } else {
          IP_READ_STATE = IS_IT_A;
        }
        break;
      case IS_IT_EQ:
        if (temp_char == '=') {
          ip_reached = INDEX_ONE;
          IP_READ_STATE = IS_IT_A;
        } else {
          IP_READ_STATE = IS_IT_A;
        }
        break;
      default: break;
    }
    if (ip_reached) {
      if (temp_char == ' ') {
        ip_address[input2] = ZERO;
        input2 = ZERO;
        ip_reached = ZERO;
      } else {
        ip_address[input2++] = temp_char;
      }
    }

    // search for disassociation event and fix if occurs
    // switch (DIS_READ_STATE) {
    //   case IS_IT_DIS:
    //     if (temp_char == 'D') {
    //       DIS_READ_STATE = IS_IT_I;
    //     } else {
    //       DIS_READ_STATE = IS_IT_DIS;
    //     }
    //     break;
    //   case IS_IT_I:
    //     if (temp_char == 'i') {
    //       DIS_READ_STATE = IS_IT_S;
    //     } else {
    //       DIS_READ_STATE = IS_IT_DIS;
    //     }
    //     break;
    //   case IS_IT_S:
    //     if (temp_char == 's') {
    //       dis_fix = INDEX_ONE;
    //       DIS_READ_STATE = IS_IT_DIS;
    //     } else {
    //       DIS_READ_STATE = IS_IT_DIS;
    //     }
    //     break;
    //   default: break;
    // }
    // if (dis_fix) {
    //   sendToIOT("AT+WSYNCINTRL=65535\r\n");
    //   //sendToIOT("AT+Ping=google.com,1");
    //   sendToIOT("AT+NSTCP=1236,1\r\n");
    //   dis_fix = ZERO;
    // }

    IOT_Char_Rx[temp2] = UCA0RXBUF;
    
    if (iot_rx_ring_wr >= (sizeof(IOT_Char_Rx))) {
      iot_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }

    // send to UCA0TXBUF for setting command
    UCA1TXBUF = IOT_Char_Rx[temp2];

    break;
  case INDEX_FOUR: // Vector 4 – TXIFG
  default: break;
  }
}


// USB ===============================================================================
// check if command starts with A
#pragma vector = EUSCI_A1_VECTOR // usb
__interrupt void eUSCI_A1_ISR(void) {
unsigned int temp;
//int i;
switch(__even_in_range(UCA1IV,INTERRUPT8)) {
  case ZERO: // Vector 0 - no interrupt
    break;
  case INDEX_TWO: // Vector 2 - RXIFG
    temp = usb_rx_ring_wr++;

    
    USB_Char_Rx[temp] = UCA1RXBUF;

    if (USB_Char_Rx[temp] == '\r') {
      usb_rx_ring_wr = BEGINNING;
    }
    UCA0TXBUF = USB_Char_Rx[temp];

    //UCAxSTATW & UCBUSY --> to check if something is transmitting


    if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))) {
      usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }

    break;
  case INDEX_FOUR: // Vector 4 – TXIFG

  	break;
//------------------------------------------------------------------------------
  default: break;
  }
}



