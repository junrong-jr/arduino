double speed_L = 300;
double speed_R = 300;
double tick_L = 0;
double tick_R = 0;
double Er_ticks = 0;
int ticks_to_move = 0;

const double Kp = 0.982, Ki = 0.5, Kd = 0.01; 
const double Kp_L = 0.12, Ki_L = 0.0, Kd_L = 0.0; //0.15
const double Kp_R = 0.05, Ki_R = 0.0, Kd_R = 0.0; //0.05
double RPM_L = 0;                                // To Store RPM of Left Motor 
double RPM_R = 0;                                 // To Store RPM of Right Motor 
double PID_RPM_R = 0;
double PID_RPM_L = 0;
double setpoint_R = 100;
double setpoint_L = 96;
PID myPID(&RPM_L, &PID_RPM_L, &RPM_R, Kp, Ki, Kd, DIRECT);
PID myPIDL(&RPM_L, &PID_RPM_L, &setpoint_L, Kp_L, Ki_L, Kd_L, DIRECT);
PID myPIDR(&RPM_R, &PID_RPM_R, &setpoint_R, Kp_R, Ki_R, Kd_R, DIRECT);
void setupPID(){
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-350,350);
  myPID.SetSampleTime(10);
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
    GetRPM();
    motor.setSpeeds(i,i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(RPM_L);
    delay(200);
  }
}
void back(){
  initMove();
  ticks_to_move = 2000;
  speed_L = -270;
  speed_R = -300;
  PID_RPM_R=0;
  PID_RPM_L=0;
  double T_L;
  double T_R;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){ //tick_R < ticks_to_move || tick_L < ticks_to_move
    GetRPM();
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
  ticks_to_move = 2000;
  speed_L = 273; //275
  speed_R = 301;
  PID_RPM_R=0;
  PID_RPM_L=0;
  double T_L;
  double T_R;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_R < ticks_to_move || tick_L < ticks_to_move){ //tick_R < ticks_to_move || tick_L < ticks_to_move
    GetRPM();
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

void forward(){
  speed_L = 250;
  speed_R = 250;
  ticks_to_move = 1200;
  motor.setSpeeds(speed_L, speed_R);
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   GetRPM();
   myPID.Compute();
   Er_ticks = tick_R - tick_L;
   double adjust = (Er_ticks!=0) ? (Er_ticks>0 ? 1 : -1) : 0;
   speed_L = speed_L + adjust + PID_RPM_R;
   speed_R = speed_R - adjust; 
  }
}

void turnright(){
  initMove();
  speed_L = 278;
  speed_R = -300;
  ticks_to_move = 386;
  motor.setSpeeds(speed_L, speed_R);
  Serial.println("Turn Right");
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   GetRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L += PID_RPM_L;
   speed_R -= PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}
void turnleft(){
  initMove();
  speed_L = -278;
  speed_R = 300;
  ticks_to_move = 388;
  motor.setSpeeds(speed_L, speed_R);
  Serial.println("Turn Left");
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   GetRPM();
   myPIDL.Compute();
   myPIDR.Compute();
   speed_L -= PID_RPM_L;
   speed_R += PID_RPM_R;
   motor.setSpeeds(speed_L, speed_R);
  }
  initEnd();
}

void calibration(){
  speed_L = 250;
  speed_R = 250;
  double T_L;
  double T_R;
  PID_RPM_R=0;
  motor.setSpeeds(speed_L, speed_R);
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
    Serial.println(PID_RPM_R);
  }
  motor.setSpeeds(0,0);
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

void setupEncoder(){
  motor.init();
  enableInterrupt(encoder1A, E1_ticks_increment, RISING);
  enableInterrupt(encoder2A, E2_ticks_increment, RISING);
}
