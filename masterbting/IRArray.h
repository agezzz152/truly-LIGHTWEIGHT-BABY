//*****IRArray.h*****//
/*
This class allows us to combine all 8 IR to a nice array.
Then, we calculate nicely the ball angle using a tidy class methos 
*/
#ifndef __IRARRAY__
#define __IRARRAY__

#include "IRSensor.h"
#include <Arduino.h>
#include "parameters.h"
#include <AceSorting.h>  // Include AceSorting library for sorting operations
// Explanation on AceSorting library: https://github.com/bxparks/AceSorting
using ace_sorting::shellSortKnuth;  // Use shellSortKnuth from AceSorting library

// Function to compare two IRSensor objects for sorting
bool lessThen(IRSensor &a, IRSensor &b);

// Function to calculate the average of two angles (0 to 359 degrees)
float avgAngs(float &a, float &b);

class IRArray {
private:
  IRSensor sensors[NUM_IR];  // Array of IRSensor objects
  MovingAverage ballAngs;    // MovingAverage object for smoothing ball angles
  float ballAngle;           // Calculated ball angle

public:
  IRArray(int *pins);      // Constructor to initialize IR sensors with pins
  void readVals();         // Method to read values from all IR sensors
  int LowestIR();          // Method to find the index of the IR sensor with the lowest value
  float avgIRVal();        // Method to calculate the average value of all IR sensors
  float findBallAngle();   // Method to find the ball's angle
  void display();          // Method to display sensor values and the ball angle
  float CalculateAngle();  // A far more simple (and less accurate) method to calc ball angle
  float getBallAngle();    // Getter method to return the ball angle
};

#endif