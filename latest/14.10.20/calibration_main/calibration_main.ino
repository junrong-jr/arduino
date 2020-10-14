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
  switch (arguments) {
    case 'F':{
        moveFForward(1);
        //front_d();
        cali();
        Serial.println("PC,AR,A");
        break;
    }
    case 'f':{
        fastForward(10);
        moveBack(10);
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
          case 'l': {
        turnLeft();
//        cali();
        Serial.println("PC,AR,A");
        Serial.println("AN,AR,L");
        break;
      }
    case 'r': {
        turnRight();
//        cali();
        Serial.println("PC,AR,A");
        Serial.println("AN,AR,R");
        break;
      }
    case '1': { //fastest path
        moveFForward(1);
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
//        fastForward(9);
        moveForward(9);
//        cali  ();
        Serial.println("AN,AR,FFFFFFFFF");
        break;
      }
    case 'G': {
      turnRight();
      cali_s();
      Serial.println("PC,AR,G");
      //Serial.println("AN,AR,L");
      //Serial.println("AN,AR,G");
      }
    case 'C': { // calibrate front and side
        cali();
//        front_d();
        break;
      }
    case 'S': {
        getReading();
        getReading2();
        break;
      }
    case 'Z': { // start zone calibration
        cali_s();
        getReading();
        break;
      }
    case 'X':{//for rpi to chaeck connection
      Serial.println("RP,AR,X");
      break;
    }
  }
}

// methods after this is in beta for new movement
void front_d() { //testing out new methods
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  if (dist1 <= 18 && dist2 <= 13.5 && dist3 <= 18) { //dist1 <= 15 && dist2 <= 13.5 && dist3 <= 15 dist1 <= 8.3 && dist2 <= 8 && dist3 <= 8.3
    dist1 = SF1();
    dist3 = SF3();
    dist2 = SF2();
    while (dist1 > 10 && dist3 > 10 && dist2 > 10) {
      slowForward();
      front_p1();
      dist1 = SF1();
      dist3 = SF3();
      dist2 = SF2();
    }
    while (dist1 <= 10 && dist3 <= 10) {
      slowBackward();
      dist1 = SF1();
      dist3 = SF3();
      dist2 = SF2();
    }
  }
  initEnd();
}
void front_d1() { //testing out new methods
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  if (dist1 <= 15 && dist2 <= 13 && dist3 <= 15) { //dist1 <= 15 && dist2 <= 13.5 && dist3 <= 15 dist1 <= 8.3 && dist2 <= 8 && dist3 <= 8.3
    dist1 = SF1();
    dist3 = SF3();
    dist2 = SF2();
    while (dist1 > 10 && dist3 > 10 && dist2 > 10) {
      slowForward();
      dist1 = SF1();
      dist3 = SF3();
      dist2 = SF2();
    }
    while (dist1 <= 10 && dist3 <= 10) {
      slowBackward();
      dist1 = SF1();
      dist3 = SF3();
      dist2 = SF2();
    }
  }
  initEnd();
}
void front_p1() { //calibrate robot to make sure robot is aligned with the wall
  double dist1 = SF1();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);
  while (error >= 0.3 && (dist1 <= 13 && dist3 <= 13)) { //dist1 <= 13 && dist3 <= 13 dist1 <= 7.5 && dist3 <= 7.5
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
    dist3 = SF3();
    error = abs(dist1 - dist3);
    delay(10);
  }
  initEnd();
}
void side_p1() { //calibrate robot to make sure robot side is aligned with the wall
  initMove();
  double dist4 = SR4(); //(SR4() + 0.4);
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
    dist4 = SR4();//(SR4() + 0.4);
    dist5 = SR5();
    error = abs(dist4 - dist5);
    delay(10);
  }
  initEnd();
}
void cali_s() { // calibration at start zone
  initMove();
  front_d1();
  front_p1();
  side_p1();
  turnLeft();
  front_d1();
  front_p1();
  side_p1();
  turnLeft();
  side_p1();
  cali();
  initEnd();
}
void cali() {
  side_p1();
  front_d1();
  front_p1();
  front_d1();
  front_p1();
  side_p1();
}
