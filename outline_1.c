  #include <Keyboard.h>
  const int SENSOR_RIGHT = 0;
  const int SENSOR_LEFT = 0;
  int previousSensorLeft = HIGH;
  int previousSensorRight = HIGH;
  int counterLeft = 0;
  int conterRight = 0;
  int counterLimit = 5;
void setup() {
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(SENSOR_LEFT, INPUT);
  Keyboard.begin;
}

void loop() {
  int sensorStateLeft = digitalRead(SENSOR_LEFT);
  int sensorStateRight = digitalRead(SENSOR_RIGHT);

  //Going forward 
  //itTODO: probably make this the final solution if none of the other conditions work out... might make handling turns easier
  if (((sensorStateLeft != previousSensorLeft) && sensorStateLeft = HIGH) && ((sensorStateRight != previousSensorRight) && sensorStateRight = HIGH)) {
    counterLeft++;
    counterRight++;
    if (counterLeft >= 5 && counterRight >= 5) {
      Keyboard.press(218);
      counterLeft = 0;
      counterRight = 0;
    }
  }
  //If counterRight is increasing at a faster "rate" (artificial) than counterLeft, just assume and force them to turn left. Same goes for turning right.
}
