#include "IRSensor.h"



IRSensor::IRSensor(int pin, int index) {
  Pin = pin;
  Index = index;
  Angle = Index * 45;
}

void IRSensor::updateValue() {
  Value = analogRead(Pin);
}

float IRSensor::GetValue() {
  return Value;
}

float IRSensor::GetAngle() {
  return Angle;
}