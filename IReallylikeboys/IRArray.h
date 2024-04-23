#ifndef __IRARRAY__
#define __IRARRAY__

#include "IRSensor.h"
#include <Arduino.h>
#define NUM_IR 5

class IRArray {
private:
  IRSensor[NUM_IR] sensors;

public:
  IRArray(int* pins);
};

#endif