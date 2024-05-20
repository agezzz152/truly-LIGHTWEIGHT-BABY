//*****IRSensor.h*****//
/*
This class allows us to have a single IR object
and store all it's properties in a neat object. 
Also helps us keep track of the angles and such while using the IRArray
*/
#ifndef __IRSENSOR__
#define __IRSENSOR__
#include <Arduino.h>
#include "parameters.h"
#include "MovingAverage.h"

class IRSensor {
private:
  int Index;           //The index of the sensor. 0 is the front right, and it goes CW.
  float Angle;         //Every senspr has an angle in relation to the robot. the sensor in index 0 is 22.5 degrees (45 / 2)
  int Pin;             // The pin that the sensor is connected to
  float Value;         // The latest value of the sensor.
  MovingAverage Vals;  // an object that contains a selected number of the newest values. Used to calculate the moving average of the sensor's value and it is more accurate than a specific, single value.

public:
  IRSensor() {}
  IRSensor(int Pin, int index);  // To set up the sensor, it requiers the connected pin and it's index.
  int getIndex() {
    return Index;
  }                      // Returns the sensor's index
  void SetVal(int val);  // Sets the argument as the value of this sensor
  void updateValue();    // Reads the analog value of the sensor
  float GetValue();      // Returns the value of the sensor
  float GetAngle();      // Returns the angle of the sensor
};

#endif