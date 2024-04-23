#include "IRSensor.h"



IRSensor::IRSensor(int pin, int index) {
  Pin = pin;
  Index = index;
  Angle = Index * 45;
}

void IRSensor::updateValue() {
  Value = analogRead(Pin);
}

int IRSensor::GetValue() {
  return Value;
}

float IRSensor::GetAngle() {
  return Angle;
}