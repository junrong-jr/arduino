#include "DualVNH5019MotorShield.h"
#include "EnableInterrupt.h"
#include <PID_v1.h>
DualVNH5019MotorShield md;
//Motor 1
#define encoder1A 3
#define encoder1B 5

//Motor 2
#define encoder2A 11
#define encoder2B 13
#define SAMPLETIME 1 //in seconds how often is read
/*-----Ticks Variable-----*/
double tick_L = 0;
double tick_R = 0;
double Er_ticks = 0;
const double Kp = 0.2, Ki = 0.0, Kd = 0; 
double speed_L = 300;
int ticks_to_move = 0;
PID myPID(&tick_L, &Er_ticks, &tick_R, Kp, Ki, Kd, DIRECT);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  md.init();

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-350,350);
  myPID.SetSampleTime(20);
  enableInterrupt(encoder1A, E1_ticks_increment, RISING);
  enableInterrupt(encoder2A, E2_ticks_increment, RISING);
}

void loop() {
  initMove();
  ticks_to_move = 2000;
  md.setSpeeds(305,speed_L);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){
    Serial.print(tick_L);
    Serial.print("\t");
    Serial.println(tick_R);

    myPID.Compute();
    Serial.print("THIS IS CALIBRATION \t");
    Serial.println(Er_ticks);
    speed_L += Er_ticks;
    Serial.println(speed_L);
    md.setSpeeds(305,speed_L);


  }
  initEnd();
  delay(3000);


}
void initStart() {                  
  md.setSpeeds(0, 0);
  md.setBrakes(0, 0);
}

void initEnd() {                     
  md.setSpeeds(0, 0);
  md.setBrakes(400, 400);
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
