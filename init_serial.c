// ------------------------------------------------------------------------------
//
//  Description: This file initializes the serial communication registers    
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern char display_line[DISPLAY_LINE_SIZE1][DISPLAY_LINE_SIZE2];
extern char *display[DISPLAY_SIZE];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile int usb_rx_ring_wr = ZERO;
volatile unsigned int usb_rx_ring_rd = ZERO;
volatile unsigned int usb_tx_ring_wr = ZERO;
volatile unsigned int usb_tx_ring_rd = ZERO;

volatile unsigned int iot_rx_ring_rd = ZERO;
volatile unsigned int iot_tx_ring_wr = ZERO;
volatile unsigned int iot_tx_ring_rd = ZERO;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE] = {ZERO};
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE] = {ZERO};
volatile char USB_Char_Tx[SMALL_RING_SIZE] = {ZERO};
volatile char IOT_Char_Tx[SMALL_RING_SIZE] = {ZERO};

// IOT
void Init_Serial_UCA0() { // machine --> project 8
  int i;
  for(i = ZERO; i < SMALL_RING_SIZE; i++){
    IOT_Char_Rx[i] = PORT_LOW; // USB Rx Buffer
  }

  iot_tx_ring_wr = BEGINNING;
  iot_rx_ring_rd = BEGINNING;

  for(i = ZERO; i < LARGE_RING_SIZE; i++){ // May not use this
    USB_Char_Tx[i] = PORT_LOW; // USB Tx Buffer
  }

  iot_tx_ring_wr = BEGINNING;
  iot_tx_ring_rd = BEGINNING;

  // set baud rate
  UCA0BRW = INDEX_FOUR;
  UCA0MCTLW = BAUD_RATE_ONE;


  // Configure UART 0
  UCA0CTLW0 = ZERO; // Use word register
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK

  UCA0CTLW0 &= ~ UCSWRST; // Set Software reset enable
  UCA0IE |= UCRXIE; // Enable RX interrupt
}


// USB
void Init_Serial_UCA1() { // usb
  int i;
  for(i = ZERO; i < SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = PORT_LOW; // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;

  for(i=ZERO; i<LARGE_RING_SIZE; i++){ // May not use this
    USB_Char_Tx[i] = PORT_LOW; // USB Tx Buffer
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;

  UCA1BRW = INDEX_FOUR;
  UCA1MCTLW = BAUD_RATE_ONE;
  
  // Configure UART 0
  UCA1CTLW0 = ZERO; // Use word register
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK

  UCA1CTLW0 &= ~ UCSWRST; // Set Software reset enable
  UCA1IE |= UCRXIE; // Enable RX interrupt
}




