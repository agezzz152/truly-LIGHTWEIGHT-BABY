#include "IRArray.h"


IRArray::IRArray(int* pins) {
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i] = IRSensor(pins[i], i);
  }
}

void IRArray::readVals() {
  for (int i = 0; i < NUM_IR; i++)
    sensors[i].updateValue();
}

int IRArray::LowestIR() {
  int minVal = 1000, minIndex = 0;
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i].updateValue();
    if (sensors[i].GetValue() < minVal) {
      minVal = sensors[i].GetValue();
      minIndex = i;
    }
  }
  return minIndex;
}


float IRArray::findBallAngle() {
  int IRIndex = LowestIR();
  int sides[2];
  ballAngle = sensors[IRIndex].GetAngle();
  return ballAngle;
}


void IRArray::display(){
  for (int i = 0; i < NUM_IR; i++){
    Serial.print(sensors[i].GetValue);
    Serial.print(" | ");
  }
  Serial.print("Angle: ");
  Serial.println(ballAngle);
}