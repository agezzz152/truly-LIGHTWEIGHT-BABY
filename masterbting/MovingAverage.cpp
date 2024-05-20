//*****MovingAverage.cpp*****//
#include "MovingAverage.h"


//recives a new float value, adds it to the array, while replacing the oldest value.
//then calcs and returns the new average of all the vals in dataArray
float MovingAverage::updateData(float value) {
  count++;                                  // Increment the counter
  if (count >= sizeOfDataArray) count = 0;  // Wrap around if count exceeds array size
  dataArray[count] = value;                 // Insert the new value into the array

  float rslt = 0;                              // Initialize sum of all vals in dataArray to 0
  for (int i = 0; i < sizeOfDataArray; ++i) {  // Iterate over the array
    rslt += dataArray[i];                      // Sum the values
  }

  return rslt / sizeOfDataArray;  // Return the average
}

//resets dataArray to {0,0,...,0}
void MovingAverage::reset(void) {
  for (int i = 0; i < sizeOfDataArray; ++i) {  // Iterate over the array
    dataArray[i] = 0;                          // Reset each element to 0
  }
}
