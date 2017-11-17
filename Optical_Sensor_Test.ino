#define SENSOR_1 A1
#define SENSOR_2 A2
int previousSensor1 = LOW;
int previousSensor2 = LOW;
int sensorCount1;
int sensorCount2;

void setup() {
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorState1 = digitalRead(SENSOR_1);
  int sensorState2 = digitalRead(SENSOR_2);
  
  if (sensorState1 != previousSensor1 || sensorState2 != previousSensor2) {
    if (sensorState1 != previousSensor1) {
      if (sensorState1 == HIGH) {
        previousSensor1 = HIGH;
      } else if (sensorState1 == LOW) {
        previousSensor1 = LOW;
        
      }
    }
    if (sensorState2 != previousSensor2) {
      if (sensorState2 == HIGH) {
        previousSensor2 = HIGH;
      } else if (sensorState2 == LOW) {
      previousSensor2 = LOW;
    }
  }
  Serial.print("Sensor 1: ");
    sensorState1 = HIGH;
    Serial.print(sensorState1);
    Serial.print(", Sensor 2: ");
    Serial.println(sensorState2);
  }
}
