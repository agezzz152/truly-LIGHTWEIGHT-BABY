//*****MovingAverage.h*****//
/*
This class allows us to create a moving average value.
It calcs the average for the num_array (param) last values that were 
inputed into the moving average object.
uses a first in last out method of discarding new vals 
*/

#ifndef __MOVING_AVERAGE__
#define __MOVING_AVERAGE__
#include "parameters.h"

class MovingAverage {
private:
  int dataArray[num_array];         // Array to store the values for moving average
  int sizeOfDataArray = num_array;  // Size of the dataArray, initialized to num_array
  int count = 0;                    // Counter to keep track of the number of inputs
public:
  MovingAverage() {}              // Default Constructor
  float updateData(float value);  // Method to add a new value and compute the average
  void reset(void);               // Method to reset the moving average data
};

#endif
