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
    case 'F': {
        parallel();
        moveForward(15);
        //moveBack(15);
        break;
      }
    case 'L': {
        turnLeft();
        parallel();
        break;
      }
    case 'R': {
        turnRight();
        parallel();
        break;
      }
    case 'f': {
        front_P();
        break;
      }
    case 'r': {//a5
        turnRight_D(72);
        break;
      }
    case 'l': {//a5
        turnLeft_D(108);
        break;
      }
    case 'P': {
        parallel();
        break;
      }
    case 'E': { //a7
        evasion();
        break;
      }
    case 'e':{ //a6
        evasion2();
        break;
    }
    case 'S':{
        getReading();
        break;
    }
  }
}

void testrun() {
  Serial.print("sensor 1 ");
  Serial.println(SF1());
  Serial.print("sensor 3 ");
  Serial.println(SF3());
  if (((SF1() > 15) && (SF3() > 15)) ) {
    moveForward(1);
  }
  else if ((SF1() > 20) && (SF3() < 20)) {
    turnRight();
  }
  else if ((SF1() < 20) && (SF3() > 20)) {
    turnLeft();
  }
  else {
    turnRight();
  }
  parallel();
}
void front_P() {
  double dist1 = SF1();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);
  Serial.println(SF1());
  Serial.println(SF3());
  while ((error >= 1) && (dist1 < 25 && dist3 < 25)) {
    dist1 = SF1();
    dist3 = SF3();
    while (dist1 > 10  && dist3 > 10) {
      moveForward1();
      dist1 = SF1();
      dist3 = SF3();
    }
    while (dist1 < 9 && dist3 < 9) {
      moveBack1();
      dist1 = SF1();
      dist3 = SF3();
    }
    if (dist3 > dist1) {
      turnRight1();
    }
    else if (dist1 > dist3) {
      turnLeft1();
    }
    else {
      error = 0;
    }
    error = abs(dist1 - dist3);
    delay(10);
  }
}
void front_Pfull() {
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  double error = abs(dist1 - dist3);
  double error2 = abs(dist1 - dist2);
  double error3 = abs(dist2 - dist3);
  Serial.println(SF1());
  Serial.println(SF1());
  Serial.println(SF3());
  if ((error >= 7) && (error2 >= 7) && (error3 >= 7) && (dist1 < 30 && dist3 < 30)) {
    turnLeft_D(4.5);
    moveForward(3);
    turnRight();
    parallel();
    moveForward(3);
  }
}
void evasion2(){
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  for (int i = 0; i < 4; i++) {
    dist1 = SF1();
    dist2 = SF2();
    dist3 = SF3();
    if ((dist1 >= 20) && (dist2 >= 20) && (dist3 >= 20)) {
      moveForward(1);
      parallel();
      delay(300);
    }
    else {
      turnLeft();
      moveForward(3);
      delay(300);
      turnRight();
      delay(300);
      moveForward(6);
      delay(300);
      turnRight();
      delay(300);
      moveForward(3);
      turnLeft();
      moveForward(1);
      delay(300);
      parallel();
      moveForward(1);
      break;
    }
  }
  initEnd();
}
void evasion() {
  double dist1 = SF1();
  double dist2 = SF2();
  double dist3 = SF3();
  for (int i = 0; i < 4; i++) {
    dist1 = SF1();
    dist2 = SF2();
    dist3 = SF3();
    if ((dist1 >= 20) && (dist2 >= 20) && (dist3 >= 20)) {
      moveForward(1);
      parallel();
      delay(300);
    }
    else {
      turnLeft_D(4.5/);
      moveForward(3);
      delay(300);
      turnRight_D(4.5);
      delay(300);
      moveForward(2);
      delay(300);
      turnRight_D(4.5);
      delay(300);
      moveForward(3);
      turnLeft_D(4.5);
      moveForward(1);
      delay(300);
      parallel();
      moveForward(1);
      break;
    }
  }
  initEnd();

}
void parallel() {
  initMove();
  double dist4 = SR4();
  double dist5 = SR5();
  double error = abs((dist4 - 0.5) - dist5);
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
