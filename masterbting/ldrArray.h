#ifndef __LDRARRAY__
#define __LDRARRAY__
#include <Arduino.h>
#include "parameters.h"
#include "ldrSensor.h"
#include "motors.h"


class ldrArray {
private:
  ldrSensor LDR[NUM_LDR];
  double angle;
  int NActiveLDR;
  bool isRetreating = 0;
  long int timeSinceStartedRetreating;
  long int currentT;


public:


  ldrArray() {}
  ldrArray(int *pins);

  bool getIsRetreating() {
    return isRetreating;
  }

  int getVal_i(int index);

  bool getStatus_i(int index);

  double Angle() const {
    return angle;
  }

  void ReadAllLDR();
  double CalcLineAngle();

void handleRetreat(motors &drivingSystem, const double &ang, const double &sped, const double &spin);
};



#endif