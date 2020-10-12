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
//    if(arguments >= '1' && arguments <= '9'){ //for fastest path
//      moveForward(arguments);
//      Serial.print("in if loop");
//      Serial.flush();
//    }
  switch (arguments) {
    case 'F': {
        moveFForward(1);
        cali();
        Serial.println("PC,AR,A");
        break;
      }
    case 'L': {
        turnLeft();
        cali();
        Serial.println("PC,AR,A");
        break;
      }
    case 'R': {
        turnRight();
        cali();
        Serial.println("PC,AR,A");
        break;
      }
    case '1': {
        moveForward(1);
//        cali();
        Serial.println("AN,AR,F");
        break;
      }
          case '2': {
        moveForward(2);
//        cali();
        Serial.println("AN,AR,FF");
        break;
      }
          case '3': {
        moveForward(3);
//        cali();
        Serial.println("AN,AR,FFF");
        break;
      }
          case '4': {
        moveForward(4);
//        cali();
        Serial.println("AN,AR,FFFF");
        break;
      }
          case '5': {
        moveForward(5);
//        cali();
        Serial.println("AN,AR,FFFFF");
        break;
      }
          case '6': {
        moveForward(6);
//        cali();
        Serial.println("AN,AR,FFFFFF");
        break;
      }
          case '7': {
        moveForward(7);
//        cali();
        Serial.println("AN,AR,FFFFFFF");
        break;
      }
          case '8': {
        moveForward(8);
//        cali();
        Serial.println("AN,AR,FFFFFFFF");
        break;
      }
          case '9': {
        moveForward(9);
//        cali  ();
        Serial.println("AN,AR,FFFFFFFFF");
        break;
      }
    case 'G':{
        Serial.println("AN,AR,G");
    }
    case 'C': { // calibrate front and side
        cali();
        break;
      }
    case 'S': {
        getReading();
        getReading2();
        break;
      }
    case 'Z':{ // start zone calibration
      cali_s();
      getReading();
      break;
    }
  }
}
void front_d() { // calibrate robot till 5cm away from the wall
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  boolean T = false; // if got error change this to true and comment the if else condition
  if(dist1 <= 12 && dist2 <= 12 && dist3 <= 12){ // check whether is robot close to wall if more than 1 grid away dont calibrate
    T = true;
  }
  else{
    T = false;
  }
  while (T) { // check for evasion of cube
    dist1 = SF1();
    dist3 = SF3();

    while (dist1 > 8.8 && dist3 > 8.8) {
      //Serial.println("In too far");
      moveForward1();
      dist1 = SF1();
      dist3 = SF3();
      T = false;
    }
    while (dist1 <= 8.8 && dist3 <= 8.8) {
      //Serial.println("In too close");
      moveBack1();
      dist1 = SF1();
      dist3 = SF3();
      T = false;
    }
    delay(10);
  }
}
void front_p() { //calibrate robot to make sure robot is aligned with the wall
  double dist1 = SF1();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);
  while ((error >= 0.3) && (dist1 <= 12 && dist3 <= 12)){ //only calibrate when 1 grid away from wall
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
    delay(10);
  }
}
void side_p() { //calibrate robot to make sure robot side is aligned with the wall
  initMove();
  double dist4 = SR4();
  double dist5 = SR5();
  double error = abs(dist4 - dist5);
  while ((error >= 0.3) && (dist4 < 15 && dist5 < 15)) {
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
  front_d1();
  front_p1();
  side_p1();
  turnLeft();
  front_d1();
  front_p1();
  side_p1();
  turnLeft(); 
  side_p(); 
  cali();
  initEnd();
}
// methods after this is in beta for new movement
void front_d1() { //testing out new methods
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = (SF3());//-0.4
  if(dist1 <= 15 && dist2 <= 13.5 && dist3 <= 15){ // check for evasion of cube
    dist1 = SF1();
    dist3 = (SF3());//-0.4
    while (dist1 > 10 && dist3 > 10 && dist2 > 10.3) {
      slowForward();
      dist1 = SF1();
      dist3 = (SF3());//-0.4
    }
    while (dist1 <= 10 && dist3 <= 10) {
      slowBackward();
      dist1 = SF1();
      dist3 = (SF3());//-0.4
    }
  }
  initEnd();
}
void front_p1() { //calibrate robot to make sure robot is aligned with the wall
  double dist1 = SF1();
  double dist3 = (SF3());//-0.4
  double error = abs(dist1 - dist3);
  while (error >= 0.3 && (dist1 <= 13 && dist3 <= 13)) {
    if (dist3 > dist1) {
      slowRight();
    }
    else if (dist1 > dist3) {
      slowLeft();
    }
    else {
      error = 0;
      break;
    }
    dist1 = SF1();
    dist3 = (SF3());//-0.4
    error = abs(dist1 - dist3);
    delay(10);
  }
  initEnd();
}
void side_p1() { //calibrate robot to make sure robot side is aligned with the wall
  initMove();
  double dist4 = (SR4()+0.4);
  double dist5 = SR5();
  double error = abs(dist4 - dist5);
  while ((error >= 0.3) && (dist4 < 11 && dist5 < 11)) {
    if (dist4 > dist5) {
      slowRight();
    }
    else if (dist5 > dist4) {
      slowLeft();
    }
    else {
      error = 0;
    }
    dist4 = (SR4()+0.4);
    dist5 = SR5();
    error = abs(dist4 - dist5);
    delay(10);
  }
  initEnd();
}
void cali(){
        side_p1();
        front_d1();
        front_p1();
        front_d1();
        front_p1();
        side_p1();
}
