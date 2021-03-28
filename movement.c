// ------------------------------------------------------------------------------
//
//  Description: This file programs the motors to move in certain shapes
//
//  Ram Bala
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include "ports.h"

void Forward_On(unsigned int left, unsigned int right) {
	Reverse_Off();
  rightWheelForOn(right); // given speed must be less than 20000
  leftWheelForOn(left);
}

void Forward_Off() {
  rightWheelForOff();
  leftWheelForOff();
}

void Reverse_On(unsigned int left, unsigned int right) {
	Forward_Off();
	rightWheelRevOn(right);
	leftWheelRevOn(left); // make sure speed * 2 is < 40000
}

void Reverse_Off() {
	rightWheelRevOff();
	leftWheelRevOff();
}

void rightWheelForOn(unsigned int speed) {
	RIGHT_FORWARD_SPEED = speed; // 20000
}

void leftWheelForOn(unsigned int speed) {
  LEFT_FORWARD_SPEED = speed; // 40000
}

void rightWheelForOff() {
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

void leftWheelForOff() {
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}

void rightWheelRevOn(unsigned int speed) {
	RIGHT_REVERSE_SPEED = speed;
}

void leftWheelRevOn(unsigned int speed) {
	LEFT_REVERSE_SPEED = speed;
}

void rightWheelRevOff() {
	RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void leftWheelRevOff() {
	LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Left_Turn(unsigned int speed) {
	RIGHT_FORWARD_SPEED = speed;
	leftWheelForOff();
}

void Right_Turn(unsigned int speed) {
	LEFT_FORWARD_SPEED = speed;
	rightWheelForOff();
}

