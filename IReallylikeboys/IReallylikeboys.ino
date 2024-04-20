
#include "MovingAverage.h"



MovingAverage a(20);
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
  int Right = a.updateData(sensorValue1);

  float sensorValue2 = analogRead(A2);
  int Middle = a.updateData(sensorValue2);

  float sensorValue3 = analogRead(A3);
  int Left = a.updateData(sensorValue3);



  Serial.print(Left); Serial.print(" | "); Serial.print(Middle); Serial.print(" | "); Serial.println(Right);
}