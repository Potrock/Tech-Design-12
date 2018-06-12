#include <Keyboard.h>
#include <math.h>
#define SENSOR_1 1
#define SENSOR_2 2
#define SENSOR_3 3
#define SENSOR_4 4
int previousSensor1 = LOW;
int previousSensor2 = LOW;
int previousSensor3 = LOW;
int previousSensor4 = LOW;
char inputBuffer[10];
int sensorState1, sensorState2, sensorState3, sensorState4;
int sensorCount, sensorCount2;
int previousPos1, previousPos2;
int threshold = 25;

void setup() {
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorState1 = digitalRead(SENSOR_1);
  sensorState2 = digitalRead(SENSOR_2);
  sensorState3 = digitalRead(SENSOR_3);
  sensorState4 = digitalRead(SENSOR_4);

  if (sensorState1 != previousSensor1 || sensorState2 != previousSensor2) {
    if (previousPos1 == 2 && sensorState2 == HIGH) {
      sensorCount++;
      updateSensors();
    }
    if (previousPos1 == 2 && sensorState1 == LOW) {
      sensorCount--;
      updateSensors();
    }
    if (previousPos1 == 3 && sensorState2 == LOW) {
      sensorCount++;
      updateSensors();
    }
    if (previousPos1 == 3 && sensorState1 == HIGH) {
      sensorCount--;
      updateSensors();
    }
    if (sensorState1 == sensorState2) {
      previousPos1 = 1;
      Serial.println("\nPos1");
      updateSensors();
    }
    if (sensorState1 != previousSensor1 && sensorState1 == HIGH && previousPos1 == 1) {
      sensorCount++;
      updateSensors();
      previousPos1 = 2;
      Serial.println("\nPos2");
    }
    if (sensorState2 != previousSensor2 && sensorState2 == LOW && previousPos1 == 1) {
      sensorCount--;
      updateSensors();
      previousPos1 = 2;
      Serial.println("\nPos2");
    }
    if (sensorState2 != previousSensor2 && sensorState2 == HIGH && previousPos1 == 1) {
      previousPos1 = 3;
      updateSensors();
      sensorCount--;
      Serial.println("\nPos3");
    }
    if (sensorState1 != previousSensor1 && sensorState1 == LOW && previousPos1 == 1) {
      previousPos1 = 3;
      updateSensors();
      sensorCount++;
      Serial.println("\nPos3");
    }
  }


  //Start second prototype
  if (sensorState3 != previousSensor3 || sensorState4 != previousSensor4) {
    if (previousPos2 == 2 && sensorState4 == HIGH) {
      sensorCount2++;
      updateSensors();
    }
    if (previousPos2 == 2 && sensorState3 == LOW) {
      sensorCount2--;
      updateSensors();
    }
    if (previousPos2 == 3 && sensorState4 == LOW) {
      sensorCount2++;
      updateSensors();
    }
    if (previousPos2 == 3 && sensorState3 == HIGH) {
      sensorCount2--;
      updateSensors();
    }
    if (sensorState3 == sensorState4) {
      previousPos2 = 1;
      Serial.println("\nPos1");
      updateSensors();
    }
    if (sensorState3 != previousSensor3 && sensorState3 == HIGH && previousPos2 == 1) {
      sensorCount2++;
      updateSensors();
      previousPos2 = 2;
      Serial.println("\nPos2");
    }
    if (sensorState4 != previousSensor4 && sensorState4 == LOW && previousPos2 == 1) {
      sensorCount2--;
      updateSensors();
      previousPos2 = 2;
      Serial.println("\nPos2");
    }
    if (sensorState4 != previousSensor4 && sensorState4 == HIGH && previousPos2 == 1) {
      previousPos2 = 3;
      updateSensors();
      sensorCount2--;
      Serial.println("\nPos3");
    }
    if (sensorState3 != previousSensor3 && sensorState3 == LOW && previousPos2 == 1) {
      previousPos2 = 3;
      updateSensors();
      sensorCount2++;
      Serial.println("\nPos3");
    }
  }
  updateSensors();
  Serial.print("Sensor Count: ");
  Serial.print(sensorCount);
  Serial.print(" ");
  Serial.println(sensorCount2);
  //Keyboard logic
  if (sensorCount - sensorCount2 >= threshold) {
    Keyboard.write(216);
    Serial.print("Left");
    sensorCount = 0;
    sensorCount2 = 0;
  } else if (sensorCount - sensorCount2 <= -threshold) {
    Keyboard.write(215);
    Serial.print("Right");
    sensorCount = 0;
    sensorCount2 = 0;
  } else if (fabs(sensorCount2 - sensorCount) <= 30 && (sensorCount >= threshold || sensorCount2 >= threshold)) {
    Keyboard.write(218);
    Serial.print("Up");
    sensorCount = 0;
    sensorCount2 = 0;
  } else if (fabs(sensorCount2 - sensorCount) <= 30 && (sensorCount <= -threshold || sensorCount2 <=  -threshold)) {
    Keyboard.write(217);
    Serial.print("Down");
    sensorCount = 0;
    sensorCount2 = 0;
  }
}

void updateSensors() {
  previousSensor1 = sensorState1;
  previousSensor2 = sensorState2;
  previousSensor3 = sensorState3;
  previousSensor4 = sensorState4;
}
