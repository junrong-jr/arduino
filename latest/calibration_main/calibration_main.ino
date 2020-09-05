/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

// Import required libraries
#include <EnableInterrupt.h>
#include <PID_v1.h> 
#include "DualVNH5019MotorShield.h"

//Motor 1
#define encoder1A 3
#define encoder1B 5

//Motor 2
#define encoder2A 11
#define encoder2B 13
DualVNH5019MotorShield motor;


void setup()
{
  //initialize the variables we're linked to
  Serial.begin(9600);
  
  setupPID();
  setupEncoder();
  initMove();
}

void loop()
{  
  calibration();
}
 
