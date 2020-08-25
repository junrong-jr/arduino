// define 2 large sensors
#define SENSOR_1 8
#define SENSOR_2 10

// define 5 small sensors
#define SENSOR_3 12
#define SENSOR_4 
#define SENSOR_5 
#define SENSOR_6 
#define SENSOR_7 

IRrecv receiver(SENSOR_1)//, receiver1(SENSOR_2), receiver1(SENSOR_3), receiver1(SENSOR_4)
	   //receiver1(SENSOR_5), receiver1(SENSOR_6), receiver1(SENSOR_7);
decode_results output1, output2, output3;

void setup() {
	Serial.begin(9600);
	pinMode(SENSOR_1, INPUT);
	pinMode(SENSOR_2, INPUT);
	pinMode(SENSOR_3, INPUT);
	pinMode(SENSOR_4, INPUT);
	pinMode(SENSOR_5, INPUT);
	pinMode(SENSOR_6, INPUT);
	pinMode(SENSOR_7, INPUT);
}

void loop() {
	detection = digitalRead(SENSOR_1);
	
	//if (receiver.decode(&results))
	if (detection == LOW)
		digitalWrite(13, HIGH);
	digitalWrite(13, LOW);
}