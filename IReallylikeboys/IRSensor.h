#ifndef __IRSENSOR__
#define __IRSENSOR__
#include <Arduino.h>
#include "parameters.h"
#include "MovingAverage.h"

class IRSensor {
private:
  int Index;
  float Angle;
  int Pin;
  float Value;
  MovingAverage Vals; 

public:
  IRSensor() {}
  IRSensor(int Pin, int index);
  int getIndex() {return Index;}
  void SetVal(int val);
  void updateValue();
  float GetValue();
  float GetAngle();
};

#endif