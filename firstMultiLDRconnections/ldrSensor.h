#ifndef __LDRSENSOR__
#define __LDRSENSOR__
#include <Arduino.h>

#define CAP_VALUE 800

class ldrSensor {
private:
  const int _pin;
  const int _index;
  bool _activated = 0;
  float _LDRVal;

public:

  ldrSensor() {}

  ldrSensor(int p, int i): _pin(p), _index(i){  }

  int getIndex() {
    return _index;
  }

  int getAngle() {
    return 70 + _index * 45;
  }

  bool read() {
    _LDRVal = analogRead(_pin);
    if (_LDRVal > CAP_VALUE)
      _activated = 1;
    return _activated;
  }

};





#endif