#ifndef __IRSENSOR__
#define __IRSENSOR__
#include <Arduino.h>
#include "parameters.h"

class IRSensor {
private:
  int Index;
  float Angle;
  int Pin;
  float Value;

public:
  IRSensor() {}
  IRSensor(int Pin, int index);
  void SetVal(int val);
  void updateValue();
  float GetValue();
  float GetAngle();
};

#endif