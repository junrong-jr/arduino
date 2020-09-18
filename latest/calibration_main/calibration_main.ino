/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <EnableInterrupt.h>
#include <PID_v1.h> 
#include "DualVNH5019MotorShield.h"
//Motor Left
#define encoder1A 3
#define encoder1B 5

//Motor Right
#define encoder2A 11
#define encoder2B 13
DualVNH5019MotorShield motor;
char arguments;

void setup()
{
  //initialize the variables we're linked to
  Serial.begin(9600);
  setupSensor();
  setupPID();
  setupEncoder();
  initMove();
}

void loop()
{ 
  
  arguments = Serial.read(); // read from rpi character
//  if(arguments >= '0' && arguments <= '9'){
//    moveForward(arguments);
//  }
switch(arguments){
  case 'W': {
              parallel();
              moveForward(1);
              break;
    }         
  case 'L': {
              parallel();
              turnLeft();
              break;
  }
  case 'R': {
              parallel();
              turnRight();
              break;
  }
  case 'F':{
              front_P();
              break;
  }
  case 'r': {
              turnRight_D(4.5);
              break;
  }
  case 'l': {
              turnLeft_D(4.5);
              break;
  }
  case 'P': {
              parallel();
              break;
  }    
  case 'E':{
              evasion();          
  }
}
//      testrun();
  //moveForward(1);
//  parallel(); 
//    delay(2500);
//  seespeed();
//  calibration2();
//  delay(500);
//  moveBack();
//  delay(500);
//  turnLeft();
//  delay(500);
//  turnRight();
}

void testrun(){
  Serial.print("sensor 1 "); 
  Serial.println(SF1()); 
  Serial.print("sensor 3 "); 
  Serial.println(SF3());
  if(((SF1() > 15)&& (SF3() > 15)) ){
    moveForward(1);
  }
  else if((SF1()> 20)&& (SF3()< 20)){
    turnRight();
  }
  else if ((SF1()< 20)&& (SF3()> 20)){
    turnLeft();
  }
  else{
    turnRight();
  }
  parallel();
}
void front_P(){
  double dist1 = SF1();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);
  Serial.println(SF1()); 
  Serial.println(SF3());
 while((error >= 1) && (dist1 < 30 && dist3 < 30)){
  dist1 = SF1();
  dist3 = SF3();
  if (dist3 > dist1){
    turnRight1();
  }
  else if(dist1 > dist3){
    turnLeft1();
  }
  else{
    error = 0;
  }
  error = abs(dist1 - dist3);
  delay(10);
 }
}
void front_Pfull(){
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);
  double error2 = abs(dist1 - dist2);
  double error3 = abs(dist2 - dist3);
  Serial.println(SF1());
  Serial.println(SF1()); 
  Serial.println(SF3());
 if((error >= 7) && (error2 >= 7)&&(error3 >= 7)&&(dist1 < 30 && dist3 < 30)){
    turnLeft_D(4.5);
    moveForward(3);
    turnRight();
    parallel();
    moveForward(3);
    }
}
void evasion(){
  moveForward(10);
  front_Pfull();
  initEnd();
  
}
void parallel(){
  double dist4 = SR4();
  double dist5 = SR5();
  double error = abs(dist4 - dist5);
  Serial.println(SR4()); 
  Serial.println(SR5());
 while((error >= 0.5) && (dist4 < 17 && dist5 < 17)){
  dist4 = SR4();
  dist5 = SR5();
  if (dist4 > dist5){
    turnRight1();
  }
  else if(dist5 > dist4){
    turnLeft1();
  }
  else{
    error = 0;
  }
  error = abs(dist4 - dist5);
  delay(10);
 }
}
 
