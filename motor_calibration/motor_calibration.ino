/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <EnableInterrupt.h>
#include <PID_v1.h> 
#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield motor;

//Define Variables we'll be connecting to
const double Kp = 0.158, Ki = 0.001, Kd = 0.001; 
double RPM_L = 0;                                 // To Store RPM of Left Motor 
double RPM_R = 0;                                 // To Store RPM of Right Motor 
double PID_RPM_L = 0;
double speed_L = 300;
//Specify the links and initial tuning parameters

PID myPID(&RPM_L, &PID_RPM_L, &RPM_R, Kp, Ki, Kd, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  Serial.begin(9600);
  motor.init();

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-350,350);
  myPID.SetSampleTime(20);
}

void loop()
{
  PID_RPM_L=0;
  motor.setSpeeds(320,speed_L);
  GetRPM();
  while(RPM_L < (RPM_R)|| RPM_L > (RPM_R)){
    Serial.print(RPM_L);
    Serial.print("\t");
    Serial.println(RPM_R);
    GetRPM();
    myPID.Compute();
    speed_L += PID_RPM_L;
    Serial.print("THIS IS CALIBRATION \t");
    Serial.print(speed_L);
    Serial.print("\t");
    Serial.println(PID_RPM_L);
    motor.setSpeeds(320,speed_L);

  }
  

}
void GetRPM(){                  
   float duration_L = pulseIn(3, HIGH); // pulseIn returns length of pulse in microseconds
   float duration_R = pulseIn(11, HIGH);
   duration_L = duration_L * 2 ;            
   duration_L = duration_L/1000000; //converts length of pulse to seconds                   
   duration_R = duration_R * 2 ;            
   duration_R = duration_R/1000000;       
                
   RPM_L = ((1/duration_L)/(562/60));  //converts length of pulse to mins
   RPM_R = ((1/duration_R)/(562/60)); // formula for rpm = (counts/min) / (counts/rev)

} 
