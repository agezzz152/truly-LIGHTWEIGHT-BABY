#ifndef __IRSENSOR__
#define __IRSENSOR__
#include <Arduino.h>
#include "parameters.h"

class IRSensor {
private:
  int Index;
  float Angle;
  int Pin;
  int Value;

public:
  IRSensor() {}
  IRSensor(int Pin, int index);
  void updateValue();
  int GetValue();
  float GetAngle();
};

#endif