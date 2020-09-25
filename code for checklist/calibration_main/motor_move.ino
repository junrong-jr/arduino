double speed_L = 280;
double speed_R = 301;
double tick_L = 0;
double tick_R = 0;
double Er_ticks = 0;
int ticks_to_move = 0;
double RPM_L = 0;                                // To Store RPM of Left Motor 
double RPM_R = 0;                                 // To Store RPM of Right Motor 
double PID_RPM_R = 0;
double PID_RPM_L = 0;
double setpoint_R = 100;
double setpoint_L = 98; //96
//const double Kp = 0.982, Ki = 0.5, Kd = 0.01; 
const double Kp_L = 0.12, Ki_L = 0.0, Kd_L = 0.0; //0.15
const double Kp_R = 0.05, Ki_R = 0.0, Kd_R = 0.0; //0.05
//PID myPID(&RPM_L, &PID_RPM_L, &RPM_R, Kp, Ki, Kd, DIRECT);
PID myPIDL(&RPM_L, &PID_RPM_L, &setpoint_L, Kp_L, Ki_L, Kd_L, DIRECT);
PID myPIDR(&RPM_R, &PID_RPM_R, &setpoint_R, Kp_R, Ki_R, Kd_R, DIRECT);

void setupPID(){
//  myPID.SetMode(AUTOMATIC);
//  myPID.SetOutputLimits(-350,350);
//  myPID.SetSampleTime(10);
  myPIDL.SetMode(AUTOMATIC);
  myPIDL.SetOutputLimits(-350,350);
  myPIDL.SetSampleTime(10);
  myPIDR.SetMode(AUTOMATIC);
  myPIDR.SetOutputLimits(-350,350);
  myPIDR.SetSampleTime(10);
}

void setupMotor(){
    motor.setSpeeds(speed_R,speed_L);
}

void seespeed(){
  initMove();
  motor.setSpeeds(270,270);
  for(int i=270; i<300; i++){
    getRPM();
    motor.setSpeeds(i,i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(RPM_L);
    delay(200);
  }
}
void moveBack(int grid){
  initMove();
  pidRPM();
  ticks_to_move = 270 * grid;
  speed_L = -270;
  speed_R = -300;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){ //tick_R < ticks_to_move || tick_L < ticks_to_move
    getRPM();
    myPIDL.Compute();
    myPIDR.Compute();
    speed_L -= PID_RPM_L;
    speed_R -= PID_RPM_R;
    motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}
void moveBack1(){
  initMove();
  pidRPM();
  ticks_to_move = 1;
  speed_L = -270;
  speed_R = -300;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){ //tick_R < ticks_to_move || tick_L < ticks_to_move
    getRPM();
    myPIDL.Compute();
    myPIDR.Compute();
    speed_L -= PID_RPM_L;
    speed_R -= PID_RPM_R;
    motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}
void calibration2(){
  initMove();
  pidRPM();
  ticks_to_move = 2000;
  speed_L = 273; //275
  speed_R = 301;
  double T_L;
  double T_R;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){ //tick_R < ticks_to_move || tick_L < ticks_to_move
    getRPM();
    myPIDL.Compute();
    myPIDR.Compute();
    speed_L += PID_RPM_L;
    speed_R += PID_RPM_R;
    Serial.print(RPM_L);
    Serial.print("\t");
    Serial.println(RPM_R);
//    Serial.print("speed ");
//    Serial.print(PID_RPM_L);
//    Serial.print("\t");
//    Serial.println(PID_RPM_R);
    motor.setSpeeds(speed_L, speed_R);
//    while(abs(Er_ticks = tick_R - tick_L)){
//      GetRPM();
//      Serial.print("In master/slave ");
//      Serial.print("\t");
//      Serial.print(RPM_L);
//      Serial.print("\t");
//      Serial.println(RPM_R);
//      myPID.Compute();
//      double adjust = (Er_ticks!=0) ? (Er_ticks>0 ? 1 : -1) : 0;
//      T_L = speed_L + adjust + PID_RPM_R;
//      T_R = speed_R - adjust;
//      motor.setSpeeds(T_L, T_R);
//    }
  }
  initEnd();
}

void calibration(){ // for align with wall
  initMove();
  ticks_to_move = 10;
  motor.setSpeeds(speed_L, speed_R);
    while(tick_R < ticks_to_move || tick_L < ticks_to_move){
      getRPM();
      myPIDL.Compute();
      myPIDR.Compute();
      speed_L += PID_RPM_L;
      speed_R += PID_RPM_R;
      motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void moveForward(int grid){
  initMove();
  pidRPM();
  ticks_to_move = 270 * grid;
  speed_L = 280; //275
  speed_R = 301;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){
    getRPM();
    myPIDL.Compute();
    myPIDR.Compute();
    speed_L += PID_RPM_L;
    speed_R += PID_RPM_R;
    motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void moveForward1(){
  initMove();
  pidRPM();
  ticks_to_move = 1;
  speed_L = 280; //275
  speed_R = 301;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){
    getRPM();
    myPIDL.Compute();
    myPIDR.Compute();
    speed_L += PID_RPM_L;
    speed_R += PID_RPM_R;
    motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void turnLeft1(){
  initMove();
  pidRPM();
  speed_L = -278;
  speed_R = 300;
  ticks_to_move = 1;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   getRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L -= PID_RPM_L;
   speed_R += PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}
void turnRight1(){
  initMove();
  pidRPM();
  speed_L = 278;
  speed_R = -300;
  ticks_to_move = 1;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   getRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L += PID_RPM_L;
   speed_R -= PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void turnRight(){
  initMove();
  pidRPM();
  speed_L = 278;
  speed_R = -300;
  ticks_to_move = 386;
  motor.setSpeeds(speed_L, speed_R);
  Serial.println("Turn Right");
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   getRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L += PID_RPM_L;
   speed_R -= PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}
void turnLeft(){
  initMove();
  pidRPM();
  speed_L = -278;
  speed_R = 300;
  ticks_to_move = 380;//388
  motor.setSpeeds(speed_L, speed_R);
  Serial.println("Turn Left");
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   getRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L -= PID_RPM_L;
   speed_R += PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void turnRight_D(float degree){
  initMove();
  pidRPM();
  speed_L = 278;
  speed_R = -300;
  ticks_to_move = (44* degree);
  motor.setSpeeds(speed_L, speed_R);
  Serial.println("Turn Right");
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   getRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L += PID_RPM_L;
   speed_R -= PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}
void turnLeft_D(float degree){
  initMove();
  pidRPM();
  speed_L = -278;
  speed_R = 300;
  ticks_to_move = (44* degree);
  motor.setSpeeds(speed_L, speed_R);
  Serial.println("Turn Left");
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   getRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L -= PID_RPM_L;
   speed_R += PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void pidRPM(){//clear pid offset
  PID_RPM_R=0;
  PID_RPM_L=0;
}

void getRPM(){                  
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
  //Er_ticks = 0;
}
void E1_ticks_increment()
{
  tick_L ++;
}

void E2_ticks_increment()
{
  tick_R ++;
}

void setupEncoder(){
  motor.init();
  enableInterrupt(encoder1A, E1_ticks_increment, RISING);
  enableInterrupt(encoder2A, E2_ticks_increment, RISING);
}
