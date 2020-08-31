#include <ZSharpIR.h>
#include <RunningMedian.h>

#define NumOfRuns 20

// define 2 long range sensors
#define SENSOR_1 A0
#define SENSOR_2 A1

// define 5 short range sensors
#define SENSOR_3 A2
#define SENSOR_4 A3
#define SENSOR_5 A4
#define SENSOR_6 A5
#define SENSOR_7 A6

//long range sensors
SharpIR sensor1(SENSOR_1, 20150);
SharpIR sensor2(SENSOR_2, 20150);

//short range sensors
SharpIR sensor3(SENSOR_3, 1080);
SharpIR sensor4(SENSOR_4, 1080);
SharpIR sensor5(SENSOR_5, 1080);
SharpIR sensor6(SENSOR_6, 1080);
SharpIR sensor7(SENSOR_7, 1080);

RunningMedian sensor1Values(NumOfRuns);
RunningMedian sensor2Values(NumOfRuns);
RunningMedian sensor3Values(NumOfRuns);
RunningMedian sensor4Values(NumOfRuns);
RunningMedian sensor5Values(NumOfRuns);
RunningMedian sensor6Values(NumOfRuns);
RunningMedian sensor7Values(NumOfRuns);

void setup() {
  //initialize the variables we're linked to
  Serial.begin(9600);
}

void loop() {
  getReading();
}

void getReading(){
  Serial.println('Short range sensor 3 reading: ', sensor3.distance());
  Serial.println('Short range sensor 4 reading: ', sensor4.distance());
  Serial.println('Short range sensor 5 reading: ', sensor5.distance());
  Serial.println('Short range sensor 6 reading: ', sensor6.distance());
  Serial.println('Short range sensor 7 reading: ', sensor7.distance());

  Serial.println('Long range sensor 1 reading: ', sensor1.distance());
  Serial.println('Long range sensor 2 reading: ', sensor2.distance());  
}

void getMedianReading(){
  sensor1.clear();
  sensor2.clear();
  sensor3.clear();
  sensor4.clear();
  sensor5.clear();
  sensor6.clear();
  sensor7.clear();
  
  for (i=0; i<NumOfRuns; i++){
    sensor1Values.add(sensor1.distance());
    sensor2Values.add(sensor2.distance());
    sensor3Values.add(sensor3.distance());
    sensor4Values.add(sensor4.distance());
    sensor5Values.add(sensor5.distance());
    sensor6Values.add(sensor6.distance());
    sensor7Values.add(sensor7.distance());
  }

  Serial.println('Long range sensor 1 median reading: ', sensor1Values.getMedian());
  Serial.println('Long range sensor 2 median reading: ', sensor2Values.getMedian());  
  Serial.println('Short range sensor 3 median reading: ', sensor3Values.getMedian());
  Serial.println('Short range sensor 4 median reading: ', sensor4Values.getMedian());
  Serial.println('Short range sensor 5 median reading: ', sensor5Values.getMedian());
  Serial.println('Short range sensor 6 median reading: ', sensor6Values.getMedian());
  Serial.println('Short range sensor 7 median reading: ', sensor7Values.getMedian());

}
