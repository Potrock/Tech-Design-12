#define SENSOR_1 A1
#define SENSOR_2 A2
int previousSensor1 = LOW;
int previousSensor2 = LOW;
int sensorCount;

void setup() {
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //HIGH = NO LIGHT = BLACK PART
  //LOW = LIGHT = WHITE PART
  int sensorState1 = digitalRead(SENSOR_1);
  int sensorState2 = digitalRead(SENSOR_2);

  if (sensorState1 != previousSensor1 || sensorState2 != previousSensor2) {
    if (sensorState1 == HIGH && sensorState2 == LOW) {
      sensorCount++;
      previousSensor1 == HIGH;
      previousSensor2 == LOW;
    } else if (sensorState1 == LOW && sensorState1 == HIGH) {
      sensorCount--;
      previousSensor1 == LOW;
      previousSensor2 == HIGH;
    }
  }
  Serial.print("Sensor Count: ");
  Serial.println(sensorCount);
}
