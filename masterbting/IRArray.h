#ifndef __IRARRAY__
#define __IRARRAY__

#include "IRSensor.h"
#include <Arduino.h>
#include "parameters.h"
#include <AceSorting.h>
// explanation on AceSorting library: https://github.com/bxparks/AceSorting
using ace_sorting::shellSortKnuth;

bool lessThen(IRSensor &a, IRSensor &b);
float avgAngs(float &a, float &b);

class IRArray {
private:
  IRSensor sensors[NUM_IR];
  MovingAverage ballAngs;
  float ballAngle;

public:
  IRArray(int *pins);
  void readVals();
  int LowestIR();
  float avgIRVal();
  float findBallAngle();
  void display();
  float CalculateAngle();
  float getBallAngle();
};

#endif