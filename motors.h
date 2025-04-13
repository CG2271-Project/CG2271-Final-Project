#ifndef MOTORS_H
#define MOTORS_H

#include "MKL25Z4.h"

// Pin Definitions
#define PTB0_Pin 0
#define PTB1_Pin 1
#define PTB2_Pin 2
#define PTB3_Pin 3
#define GAIN 2.5
#define BRAKE 500
#define LOW 3000
#define MED 6500
#define HIGH 7500

double absolute(double speed);
double min(double speed);
void speed(double h_offset, double speed, int crab);
void initPWM(void);

#endif // MOTOR_CONTROL_H
