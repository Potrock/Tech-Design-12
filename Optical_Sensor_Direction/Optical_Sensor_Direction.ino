#define SENSOR_1 A1
#define SENSOR_2 A2
int previousSensor1 = LOW;
int previousSensor2 = LOW;
int sensorCount;
int previousPos;
int threshold = 10;

void setup() {
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (sensorCount > threshold || sensorCount < -threshold) {
    sensorCount = 0;
  }
  //HIGH = NO LIGHT = BLACK PART
  //LOW = LIGHT = WHITE PART
  int sensorState1 = digitalRead(SENSOR_1);
  int sensorState2 = digitalRead(SENSOR_2);

  /*
   * Logic:
   * Only way that I could think of to tell the direction of movement is based on what happens after both sensors read the same value (both HIGH/LOW)
   * Downside to this is the counter can only actually increase every "other" tick, instead of each change in reading.
   * 
   * If both sensors are the same: previousPos = 1
   * This lets me use previousPos to check what happens next. Depending on what sensor changes first, the direction can be determined.
   */

  if (sensorState1 != previousSensor1 || sensorState2 != previousSensor2) {
    if (sensorState1 == sensorState2) {
      previousPos = 1;
      previousSensor1 = sensorState1;
      previousSensor2 = sensorState2;
    }
    if (sensorState1 != previousSensor1 && sensorState1 == HIGH && previousPos == 1) {
      sensorCount += 2;
      previousSensor1 = sensorState1;
      previousSensor2 = sensorState2;
      previousPos = 2;
    }
    if (sensorState2 != previousSensor2 && sensorState2 == HIGH && previousPos == 1) {
      previousPos = 2;
      previousSensor1 = sensorState1;
      previousSensor2 = sensorState2;
      sensorCount -= 2;
    }
    Serial.print("Sensor Count: ");
    Serial.println(sensorCount);
  }
}
