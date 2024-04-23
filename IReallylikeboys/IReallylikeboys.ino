
#include "MovingAverage.h"
#include "IRArray.h"

MovingAverage IR[NUM_IR];

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue1 = analogRead(A1);
  // print out the value you read:
  int Right = IR[0].updateData(sensorValue1);

  float sensorValue2 = analogRead(A2);
  int Middle = IR[1].updateData(sensorValue2);

  float sensorValue3 = analogRead(A3);
  int Left = IR[2].updateData(sensorValue3);

  float sensorValue4 = analogRead(A4);
  int extra = IR[3].updateData(sensorValue4);

  Serial.print(Left); Serial.print(" | "); Serial.print(Middle); Serial.print(" | "); Serial.print(Right); Serial.print(" | "); Serial.println(extra);
}