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
int sensorState1, sensorState2, sensorState3, sensorState4;
int sensorCount, sensorCount2;
int previousPos1, previousPos2;
int threshold = 15;
int velLeft;
int velRight;
int quartRotLeft;
int quartRotRight;
unsigned long prevTime = millis();
unsigned long currTime = millis();;

void setup() {
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  //HIGH = NO LIGHT = BLACK PART
  //LOW = LIGHT = WHITE PART
  sensorState1 = digitalRead(SENSOR_1);
  sensorState2 = digitalRead(SENSOR_2);
  sensorState3 = digitalRead(SENSOR_3);
  sensorState4 = digitalRead(SENSOR_4);

  if (sensorState1 != previousSensor1 || sensorState2 != previousSensor2) {
    if (previousPos1 == 2 && sensorState2 == HIGH) {
      sensorCount++;
      quartRotLeft++;
      updateSensors();
    }
    if (previousPos1 == 2 && sensorState1 == LOW) {
      sensorCount--;
      quartRotLeft--;
      updateSensors();
    }
    if (previousPos1 == 3 && sensorState2 == LOW) {
      sensorCount++;
      quartRotLeft++;
      updateSensors();
    }
    if (previousPos1 == 3 && sensorState1 == HIGH) {
      sensorCount--;
      quartRotLeft--;
      updateSensors();
    }
    if (sensorState1 == sensorState2) {
      previousPos1 = 1;
      Serial.println("\nPos1");
      updateSensors();
    }
    if (sensorState1 != previousSensor1 && sensorState1 == HIGH && previousPos1 == 1) {
      sensorCount++;
      quartRotLeft++;
      updateSensors();
      previousPos1 = 2;
      Serial.println("\nPos2");
    }
    if (sensorState2 != previousSensor2 && sensorState2 == LOW && previousPos1 == 1) {
      sensorCount--;
      quartRotLeft--;
      updateSensors();
      previousPos1 = 2;
      Serial.println("\nPos2");
    }
    if (sensorState2 != previousSensor2 && sensorState2 == HIGH && previousPos1 == 1) {
      previousPos1 = 3;
      updateSensors();
      sensorCount--;
      quartRotLeft--;
      Serial.println("\nPos3");
    }
    if (sensorState1 != previousSensor1 && sensorState1 == LOW && previousPos1 == 1) {
      previousPos1 = 3;
      updateSensors();
      sensorCount++;
      quartRotLeft++;
      Serial.println("\nPos3");
    }
  }


  //Start second prototype
  if (sensorState3 != previousSensor3 || sensorState4 != previousSensor4) {
    if (previousPos2 == 2 && sensorState4 == HIGH) {
      sensorCount2++;
      updateSensors();
      quartRotRight++;
    }
    if (previousPos2 == 2 && sensorState3 == LOW) {
      sensorCount2--;
      updateSensors();
      quartRotRight--;
    }
    if (previousPos2 == 3 && sensorState4 == LOW) {
      sensorCount2++;
      updateSensors();
      quartRotRight++;
    }
    if (previousPos2 == 3 && sensorState3 == HIGH) {
      sensorCount2--;
      updateSensors();
      quartRotRight--;
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
      quartRotRight++;
      Serial.println("\nPos2");
    }
    if (sensorState4 != previousSensor4 && sensorState4 == LOW && previousPos2 == 1) {
      sensorCount2--;
      updateSensors();
      previousPos2 = 2;
      quartRotRight--;
      Serial.println("\nPos2");
    }
    if (sensorState4 != previousSensor4 && sensorState4 == HIGH && previousPos2 == 1) {
      previousPos2 = 3;
      updateSensors();
      sensorCount2--;
      quartRotRight--;
      Serial.println("\nPos3");
    }
    if (sensorState3 != previousSensor3 && sensorState3 == LOW && previousPos2 == 1) {
      previousPos2 = 3;
      updateSensors();
      sensorCount2++;
      quartRotRight++;
      Serial.println("\nPos3");
    }
  }
  updateSensors();
  //  Serial.print("Sensor Count: ");
  //  Serial.print(sensorCount);
  //  Serial.print(" ");
  //  Serial.println(sensorCount2);

  currTime = millis();
  if ((currTime - prevTime) / 1000 > 1) {
    velLeft = quartRotLeft / ((currTime - prevTime) / 1000);
    velRight = quartRotRight / ((currTime - prevTime) / 1000);
    quartRotLeft = quartRotRight = 0;
    prevTime = currTime;
    Serial.print(velLeft);
    Serial.print(" : ");
    Serial.println(velRight);
  }

  //Keyboard logic
  //Forward left turn
  if (velLeft > 0 && velRight > (leftLeft + 7)) {
    Keyboard.write(218);
    Keyboard.write(216);
    delay(500);
    //Forward straight
  } else if (velLeft > 0 && velRight > 0) {
    Keyboard.write(218);
    delay(500);
    //Forward right turn
  } else if (velLeft > (velRight + 7)) && velRight > 0) {
    Keyboard.write(218);
    Keyboard.write(215);
    delay(500);
    //Left turn on spot
  } else if (velLeft < 0 && velRight > 0) {
    Keyboard.write(216);
    delay(500);
    //Right turn on spot
  } else if (velLeft > 0 && velRight < 0) {
    Keyboard.write(215);
    delay(500);
  }
}

void updateSensors() {
  previousSensor1 = sensorState1;
  previousSensor2 = sensorState2;
  previousSensor3 = sensorState3;
  previousSensor4 = sensorState4;
}
