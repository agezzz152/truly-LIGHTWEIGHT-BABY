#ifndef __MOTORS__
#define __MOTORS__
#include <Arduino.h>
#include "parameters.h"
#include "wheel.h"




class motors {
private:
  wheel wheels[NUM_MOTORS];
  double pwmVal[4] = { 0 };
  double speedPart;
  double speenPart;
  double rad45 = 0.785398;


public:
  motors(int *pwm, int *in1, int *in2);

  void motorSetup();

  void moov(double angle, const double &sped, const double &speen);
};


#endif