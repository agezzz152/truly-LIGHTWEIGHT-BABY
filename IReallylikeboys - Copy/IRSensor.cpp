#include "IRSensor.h"



IRSensor::IRSensor(int pin, int index) {
  Pin = pin;
  Index = index;
  Angle = Index * 45;
}

void IRSensor::SetVal(int val){ 
  Value = val;
}

void IRSensor::updateValue() {
  SetVal(analogRead(Pin));
}


float IRSensor::GetValue() {
  return Value;
}

float IRSensor::GetAngle() {
  return Angle;
}