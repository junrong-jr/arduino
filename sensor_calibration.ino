#include <ZSharpIR.h>
#include <RunningMedian.h>

#define NumOfRuns 20

// define 5 short range sensors
#define SENSOR_1 A0
#define SENSOR_2 A1
#define SENSOR_3 A2
#define SENSOR_4 A3
#define SENSOR_5 A4
// define 1 long range sensors
#define SENSOR_6 A5

//long range sensors
ZSharpIR sensor1(SENSOR_1, 1080);
ZSharpIR sensor2(SENSOR_2, 1080);
ZSharpIR sensor3(SENSOR_3, 1080);
ZSharpIR sensor4(SENSOR_4, 1080);
ZSharpIR sensor5(SENSOR_5, 1080);
//short range sensors
ZSharpIR sensor6(SENSOR_6, 20150);

//RunningMedian class to calculate the median values from the sensor
RunningMedian sensor1Values(NumOfRuns);
RunningMedian sensor2Values(NumOfRuns);
RunningMedian sensor3Values(NumOfRuns);
RunningMedian sensor4Values(NumOfRuns);
RunningMedian sensor5Values(NumOfRuns);
RunningMedian sensor6Values(NumOfRuns);

void setup() {
  //initialize the variables we're linked to
  Serial.begin(9600);
}

void loop() {
  getReading();
  getMedianReading();
  delay(5000);
}

void getReading(){
//  Serial.print("Front Right sensor 1 reading: ");
//  Serial.println(sensor1.distance());
//  Serial.print("Front Mid sensor 2 reading: ");
//  Serial.println(sensor2.distance());
//  Serial.print("Front Left sensor 3 reading: ");
//  Serial.println(sensor3.distance());
//  Serial.print("Left Front sensor 4 reading: ");
//  Serial.println(sensor4.distance());
//  Serial.print("Left Back sensor 5 reading: ");
//  Serial.println(sensor5.distance());
//  Serial.print("Right Long sensor 6 reading: ");
//  Serial.println(sensor6.distance());

}

void getMedianReading(){
  
  for (int i=0; i<NumOfRuns; i++){
    sensor1Values.add(sensor1.distance());
    sensor2Values.add(sensor2.distance());
    sensor3Values.add(sensor3.distance());
    sensor4Values.add(sensor4.distance());
    sensor5Values.add(sensor5.distance());
    sensor6Values.add(sensor6.distance());
  }

  Serial.print("Front Right sensor 1 median reading: ");
  Serial.println(sensor1Values.getMedian()); 
  Serial.print("Front Mid sensor 2 median reading: "); 
  Serial.println(sensor2Values.getMedian());  
  Serial.print("Front Left sensor 3 median reading: ");
  Serial.println(sensor3Values.getMedian()); 
  Serial.print("Left Front sensor 4 median reading: ");
  Serial.println(sensor4Values.getMedian()); 
  Serial.print("Left Back sensor 5 median reading: ");
  Serial.println(sensor5Values.getMedian()); 
//  Serial.print("Right Long sensor 6 median reading: ");
//  Serial.println(sensor6Values.getMedian()); 
}
