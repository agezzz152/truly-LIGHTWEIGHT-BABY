#ifndef __IRARRAY__
#define __IRARRAY__

#include "IRSensor.h"
#include <Arduino.h>
#include "parameters.h"


class IRArray {
private:
  IRSensor sensors[NUM_IR];
  float ballAngle;

public:
  IRArray(int* pins);
  int LowestIR();
  void readVals();
  float findBallAngle();
  void display();
};

#endif