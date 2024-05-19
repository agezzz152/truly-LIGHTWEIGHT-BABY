#include "IRSensor.h"



IRSensor::IRSensor(int pin, int index) { // Sets up the sensor according to the Pin, index, and angle
  Pin = pin;
  Index = index;
  Angle = ANGLE_FIX + Index * 45; // ANGLE_FIX is 30, uses the index of the sensor to determine it's value instead of manually writing each angle
}

void IRSensor::SetVal(int val){ 
  Value = Vals.updateData(val); // Sets the value of the sensor to the average of a selected number of last values.
}

void IRSensor::updateValue() {
  SetVal(analogRead(Pin)); // Adds a new value to the moving average and accoring to that the current value changes
}


float IRSensor::GetValue() {
  return Value;
}

float IRSensor::GetAngle() {
  return Angle;
}