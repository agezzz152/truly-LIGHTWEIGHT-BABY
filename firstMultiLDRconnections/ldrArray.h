#ifndef __LDRARRAY__
#define __LDRARRAY__
#include <Arduino.h>
#include "parameters.h"
#include "ldrSensor.h"

class ldrArray {
private:
  ldrSensor LDR[NUM_LDR];
  double angle;
  int NActiveLDR;


public:

  ldrArray() {}
  ldrArray(int* pins);

  int getVal_i(int index);

  bool getStatus_i(int index);

  double Angle() const {return angle;}

  void ReadAllLDR();
  double CalcLineAngle();
};



#endif