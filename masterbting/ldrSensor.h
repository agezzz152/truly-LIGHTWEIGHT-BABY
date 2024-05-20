//*****ldrSensor.h*****//
/*
This class is used for creating a single LDR object. 
it allows us to give each ldr its value, index and pin instead of creating 4 annoying arrays
It is useful only for the ldrArray file
*/

#ifndef __LDRSENSOR__
#define __LDRSENSOR__
#include <Arduino.h>
#include "parameters.h"

class ldrSensor {
private:
  int _pin;             // The pin that the LDR is connected to
  int _index;           // The index of this specific LDR. 0 is the front right, goes CW.
  bool _activated = 0;  // Determines if an LDR is considered on or of
  float _LDRVal;        // The value of that sensor.

public:
  ldrSensor() {}

  ldrSensor(int p, int i) {  // Recieves a pin and index and sets up the sensor accordingly
    _pin = p;
    _index = i;
  }

  bool getStatus() const {
    return _activated;  // Returns wethear the sensor is on or of. (if it detects a white line it is cosidered on)
  }

  float getVal() const {
    return _LDRVal;  // Returns the value of the sensor
  }

  int getIndex() const {
    return _index;  // Returns the value of the sensor
  }

  int getAngle() const {
    return 70 + _index * 45;  // Uses the index to determine the angle of the sensor. The first is 70 deg, and there are 45 deg jump between each sensor.
  }

  bool read() {  // Reads the value of a sensor. Then updates the status of the sensor if needed
    _LDRVal = analogRead(_pin);
    if (_LDRVal > CAP_VALUE)  // CAP_VALUE is 800. If the value of the sensor is above that number, then it means that the sensor detects a white line and is considered on.
      _activated = 1;         // In that case, we change the status to 1.
    else
      _activated = 0;  // If the value doesn't exceed CAP_VALUE, then it is not on a white line and it is considered off.

    return _activated;  // Returns the status of the sensor
  }
};





#endif