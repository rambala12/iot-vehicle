#ifndef MACROS_H
#define MACROS_H

//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson + Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);
__interrupt void Timer0_B1_ISR(void);

// Analog to Digital Converter

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);
void LEDs_Blink(void);

  // LCD
void line0_display(char *str);
void line1_display(char *str);
void line2_display(char *str);
void line3_display(char *str);
void clear_display(void);
void BIG_Display(char *str1, char *str2, char *str3);

void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(int mode);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Initialize ADC and ADC functions
void Init_ADC(void);
void HEXtoBCD(int hex_value);
void Display_Thumb(void);
void Display_L_Detector(void);
void Display_R_Detector(void);
void Display_Line_Position(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);
void Display_Clock(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Movement Functions
void Forward_On(unsigned int left, unsigned int right);
void Forward_Off(void);
void Reverse_On(unsigned int left, unsigned int right);
void Reverse_Off(void);
void rightWheelForOn(unsigned int speed);
void leftWheelForOn(unsigned int speed);
void rightWheelForOff(void);
void leftWheelForOff(void);
void rightWheelRevOn(unsigned int speed);
void leftWheelRevOn(unsigned int speed);
void rightWheelRevOff(void);
void leftWheelRevOff(void);
void Left_Turn(unsigned int speed);
void Right_Turn(unsigned int speed);

// Project 6 Routine
void Project_Five(void);

// Following black line
void Follow_Line_Circle(void);
void Line_Position(void);
void circle_routine(void);


// Serial Port Functions
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);
void out_character(char character);
void Get_Commands(void);

// IOT set up functions
void Display_IP(void);
void interpret_commands(void);
int string2dec(char str);
void initialize_iot(void);
void sendToIOT(char* str);
void clock_circle_routine(void);
void Display_Pads(void);


#endif


