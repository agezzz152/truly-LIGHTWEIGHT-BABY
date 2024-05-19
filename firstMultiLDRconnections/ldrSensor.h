#ifndef __LDRSENSOR__
#define __LDRSENSOR__
#include <Arduino.h>
#include "parameters.h"
#include "MovingAverage.h"


class ldrSensor {
private:
  int _pin;
  int _index;
  bool _activated = 0;
  MovingAverage _LDRValss;
  float _LDRVal;

public:
  ldrSensor() {}

  ldrSensor(int p, int i){
    _pin = p; 
    _index = i;
  }

  bool getStatus() const {
    return _activated;
  }

  float getVal() const {
    return _LDRVal;
  }

  int getIndex() const {
    return _index;
  }

  int getAngle() const {
    return 70 + _index * 45;
  }

  bool read() {
    _LDRVal = _LDRValss.updateData(analogRead(_pin)); 
    if (_LDRVal < CAP_VALUE)
      _activated = 1;
    else
      _activated = 0;

    return _activated;
  }
};





#endif