double speed_L = 250;
double speed_R = 250;
double tick_L = 0;
double tick_R = 0;
double Er_ticks = 0;
int ticks_to_move = 1500;

const double Kp = 0.982, Ki = 0.5, Kd = 0.01; 
double RPM_L = 0;                                // To Store RPM of Left Motor 
double RPM_R = 0;                                // To Store RPM of Right Motor 
double PID_RPM_R = 0;
PID myPID(&RPM_R, &PID_RPM_R, &RPM_L, Kp, Ki, Kd, DIRECT);

void setupPID(){
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-350,350);
  myPID.SetSampleTime(10);
}

void setupMotor(){
    motor.setSpeeds(speed_R,speed_L);
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
  speed_L = 250;
  speed_R = -250;
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

void turnleft(){
  speed_L = -250;
  speed_R = 250;
  ticks_to_move = 1200;
  motor.setSpeeds(speed_L, speed_R);
  
  while(tick_L < ticks_to_move || tick_R < ticks_to_move ){
   GetRPM();
   myPID.Compute();
   Er_ticks = tick_R - tick_L;
   double adjust = (Er_ticks!=0) ? (Er_ticks>0 ? 1 : -1) : 0;
   speed_L = speed_L + adjust + (-1)*PID_RPM_R;
   speed_R = speed_R - adjust; 
  }
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
    T_L = speed_L + adjust + PID_RPM_R;
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
