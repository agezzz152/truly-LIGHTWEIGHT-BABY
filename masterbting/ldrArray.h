//*****ldrArray.h*****//
/*
This class is used for the whole LDR detection system.
It allows us to create an LDRsensor array;
calc different parameters of the whole system;
to detect if on a white line, and if so then at which angle (ang = 0 is at the dribler and goes CW);
and at last to retreat if stepped on a white line
*/

#ifndef __LDRARRAY__
#define __LDRARRAY__
#include <Arduino.h>
#include "parameters.h"
#include "ldrSensor.h"
#include "motors.h"


class ldrArray {
private:
  //An array of ldrSensor type, each index keeps the info for that ldr's index (pin, val, ...)
  ldrSensor LDR[NUM_LDR];
  double angle;    // Angle of the white line
  int NActiveLDR;  // Counter for how many

  //retreating variables
  bool isRetreating = 0;                // Flag for if robot is retreating
  long int timeSinceStartedRetreating;  // Timestamp when retreat started
  long int currentT;                    // Keeps the current time


public:

  ldrArray() {}         // Default constructor
  ldrArray(int *pins);  // Constructor for initiating the LDR array with correct pins and indexes


  // Getter methods
  bool getIsRetreating() { return isRetreating; }
  int getVal_i(int index);
  bool getStatus_i(int index);
  double Angle() const { return angle; }


  // Methods to interact with LDR sensors and handle retreating
  // greater explanation in cpp file
  void ReadAllLDR();
  double CalcLineAngle();
  void handleRetreat(motors &drivingSystem, const double &ang, const double &sped, const double &spin);
};



#endif