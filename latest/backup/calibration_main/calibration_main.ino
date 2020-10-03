/********************************************************
   PID Basic Example
   Reading analog input 0 to control analog PWM output 3
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
  switch (arguments) {
    case 't':{
      moveForward100();
      break;
    }
    case 'F': {
        moveForward(1);
        side_p();
        Serial.print("PC,AR,A");
        //moveBack(15);
        break;
      }
    case 'L': {
        turnLeft();
        //side_p();
        Serial.print("PC,AR,A");
        break;
      }
    case 'R': {
        turnRight();
        Serial.print("PC,AR,A");
        //side_p();
        break;
      }
    case 'f': {
        moveForward(1);
        Serial.print("AN,AR,F");
        break;
      }
    case 'r': {//a5
        turnRight();
        Serial.print("AN,AR,R");
        break;
      }
    case 'l': {//a5
        turnLeft();
        Serial.print("AN,AR,L");
        break;
      }
    case 'g':{
        Serial.print("AN,AR,G");
    }
    case 'C': {
      Serial.println("start");
        front_d();
        Serial.println("front parallel");
        front_p();
        Serial.println("side parallel");
        side_p();
        Serial.println("end");
        break;
      }
    case 'S': {
        getReading();
        getReading2();
        break;
      }
//    case 'Z':{ // start zone calibration
//      cali_s();
//      break;
//    }
  }
}
void front_d() {
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  boolean T = true;
  while (T) { // check for evasion of cube
    dist1 = SF1();
    dist3 = SF3();

    while (dist1 > 8.8 && dist3 > 8.8) {
      Serial.println("In too far");
      moveForward1();
      dist1 = SF1();
      dist3 = SF3();
      T = false;
    }
    while (dist1 <= 8.8 && dist3 <= 8.8) {
      Serial.println("In too close");
      moveBack1();
      dist1 = SF1();
      dist3 = SF3();
      T = false;
    }
    delay(10);
  }
}
void front_p() {
  double dist1 = SF1();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);

  while (error >= 0.3) {
    if (dist3 > dist1) {
      turnRight1();
    }
    else if (dist1 > dist3) {
      turnLeft1();
    }
    else {
      error = 0;
      break;
    }
    dist1 = SF1();
    dist3 = SF3();
    error = abs(dist1 - dist3);
    Serial.println("In error");
    Serial.println(SF1());
    Serial.println(SF3());
    Serial.println(" ");
    delay(10);
  }
}
void side_p() {
  initMove();
  double dist4 = SR4();
  double dist5 = SR5();
  double error = abs(dist4 - dist5);
  Serial.println(SR4());
  Serial.println(SR5());
  while ((error >= 0.3) && (dist4 < 25 && dist5 < 25)) {
    dist4 = SR4();
    dist5 = SR5();
    if (dist4 > dist5) {
      turnRight1();
    }
    else if (dist5 > dist4) {
      turnLeft1();
    }
    else {
      error = 0;
    }
    error = abs(dist4 - dist5);
    delay(10);
  }
  initEnd();
}
void cali_s(){ // calibration at start zone
  initMove();
  front_d();
  front_p();
  side_p();
  turnLeft();
  front_d();
  front_p();
  side_p();
  turnLeft();
  side_p();
  initEnd();
}


//void evasion2() {
//  double dist1 = SF1();
//  double dist2 = SF2();
//  double dist3 = SF3();
//  for (int i = 0; i < 4; i++) {
//    dist1 = SF1();
//    dist2 = SF2();
//    dist3 = SF3();
//    if ((dist1 >= 20) && (dist2 >= 20) && (dist3 >= 20)) {
//      moveForward(1);
//      parallel();
//      delay(300);
//    }
//    else {
//      turnLeft();
//      moveForward(3);
//      delay(300);
//      turnRight();
//      delay(300);
//      moveForward(6);
//      delay(300);
//      turnRight();
//      delay(300);
//      moveForward(3);
//      turnLeft();
//      moveForward(1);
//      delay(300);
//      parallel();
//      moveForward(1);
//      break;
//    }
//  }
//  initEnd();
//}
//void evasion() {
//  double dist1 = SF1();
//  double dist2 = SF2();
//  double dist3 = SF3();
//  for (int i = 0; i < 4; i++) {
//    dist1 = SF1();
//    dist2 = SF2();
//    dist3 = SF3();
//    if ((dist1 >= 20) && (dist2 >= 20) && (dist3 >= 20)) {
//      moveForward(1);
//      parallel();
//      delay(300);
//    }
//    else {
//      turnLeft_D(4.5);
//      moveForward(3);
//      delay(300);
//      turnRight_D(4.5);
//      delay(300);
//      moveForward(2);
//      delay(300);
//      turnRight_D(4.5);
//      delay(300);
//      moveForward(3);
//      turnLeft_D(4.5);
//      moveForward(1);
//      delay(300);
//      parallel();
//      moveForward(1);
//      break;
//    }
//  }
//  initEnd();
//}
