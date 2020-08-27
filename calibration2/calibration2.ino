/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

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
//Define Variables we'll be connecting to
const double Kp = 0.158, Ki = 0.00, Kd = 0.00; 
double RPM_L = 0;                                 // To Store RPM of Left Motor 
double RPM_R = 0;                                 // To Store RPM of Right Motor 
double PID_RPM_L = 0;
double tick_L = 0;
double tick_R = 0;
double Er_ticks = 0;
double speed_L = 300;
double speed_R = 288;
int ticks_to_move = 2000;
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
  myPID.SetSampleTime(10);
  enableInterrupt(encoder1A, E1_ticks_increment, RISING);
  enableInterrupt(encoder2A, E2_ticks_increment, RISING);
}

void loop()
{
  double T_L;
  double T_R;
  PID_RPM_L=0;
  initMove();
  motor.setSpeeds(speed_R,speed_L);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){
    GetRPM();
    myPID.Compute();
    Serial.print(RPM_L);
    Serial.print("\t");
    Serial.println(RPM_R);
    Er_ticks = tick_R - tick_L;
    double adjust = (Er_ticks!=0) ? (Er_ticks>0 ? 1 : -1) : 0;
    T_L = speed_L + adjust + PID_RPM_L;
    T_R = speed_R - adjust;
    motor.setSpeeds(T_L, T_R);
    Serial.print("THIS IS CALIBRATION \t");
    Serial.print(T_L);
    Serial.print("\t");
    Serial.print(T_R);
    Serial.print("\t");
    Serial.println(PID_RPM_L);
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
void initStart() {                  
  motor.setSpeeds(0, 0);
  motor.setBrakes(0, 0);
}

void initEnd() {                     
  motor.setSpeeds(0, 0);
  motor.setBrakes(400, 400);
  delay(20);
}
void initMove() {                             
  tick_R = 0;                                    
  tick_L = 0;  
  Er_ticks = 0;
}
void E1_ticks_increment()
{
  tick_L ++;
}

void E2_ticks_increment()
{
  tick_R ++;
}
