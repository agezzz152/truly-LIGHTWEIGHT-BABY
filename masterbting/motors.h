#ifndef __MOTORS__
#define __MOTORS__
#include <Arduino.h>
#include "parameters.h"
#include "wheel.h"
  
int signOfX(const int &x);
void myDelay(int millDelay);

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

  void moov(double dirAngle, const double &sped, const double &speen);

  void moovMultiDirSimple();

  void simpleMotorTest(int a = 0, int b = NUM_MOTORS);

  void BasicAngleMooving(const double &ang, const double &liniarSped, const double &spinSped);
};


#endif