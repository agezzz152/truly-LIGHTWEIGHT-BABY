//*****IRArray.cpp*****//



/*
a function so that shellSortKnuth will know what a assending order is, with IRSensor types
If we were sorting an array of ints, we wouldn't need this func
but cause we are sorting an array of IRSensors, the function doesn't know which one is bigger
*/
#include "IRArray.h"
bool lessThen(IRSensor &a, IRSensor &b) {
  return (a.GetValue() < b.GetValue());
}

/* Function to calculate the average of two angles (0 to 359 degrees)
 * This function ensures the result is also within 0 to 359 degrees
 */
float avgAngs(float &a, float &b) {
  float avg = (a + b) / 2;
  if (avg >= 360)
    avg = avg - 360;
  return avg;
}

// Constructor that initializes the IR sensors with given pins.
IRArray::IRArray(int *pins) {
  // Loop through each sensor and initialize with the provided pin and index.
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i] = IRSensor(pins[i], i);
  }
}

// Method to read values from all IR sensors.
void IRArray::readVals() {
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i].updateValue();           // Update the sensor's value.
    if (sensors[i].GetValue() > IRCAP)  // Cap the value if it exceeds IRCAP.
      sensors[i].SetVal(IRCAP);
  }
}

// Method to find the index of the IR sensor with the lowest value.
int IRArray::LowestIR() {
  int minVal = IRCAP, minIndex = 0;
  // Iterate through each sensor to find the minimum value.
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i].updateValue();              // Update the sensor's value.
    if (sensors[i].GetValue() < minVal) {  // Check if this is the new minimum value.
      minVal = sensors[i].GetValue();
      minIndex = i;
    }
  }
  return minIndex;  // Return the index of the sensor with the lowest value.
}


// Method to calculate the average value of all IR sensors.
float IRArray::avgIRVal() {
  int sum = 0;
  for (int i = 0; i < NUM_IR; i++) {
    sum += sensors[i].GetValue();  // Sum the values of all sensors.
  }
  return sum / NUM_IR;  // Return the average value.
}



//the main function that finds the ball angle using the date from IR sensors
float IRArray::findBallAngle() {
  readVals();  // Read values from all sensors.


  // Create a copy of the sensors array for manipulation.
  IRSensor sensorsManipulated[NUM_IR];
  for (int i = 0; i < NUM_IR; i++) {
    sensorsManipulated[i] = sensors[i];
  }

  // Sort the copied sensor array based on their values.
  shellSortKnuth(sensorsManipulated, NUM_IR, lessThen);

  // Initialize variables for the closest sensor's angle and value.
  // Get the angle and value of the closest sensor (the sensor with the smallest value after sorting).
  float closestAng = sensorsManipulated[0].GetAngle();  // The angle of the closest sensor.
  float closestVal = sensorsManipulated[0].GetValue();  // The value of the closest sensor.

  // Initialize variables for the second closest sensor.
  int i = 0;            // Loop counter to find the second closest sensor, that is also close (in index) to closestIR
                        // how close? at max NUM_SPACES_FROM_CLOSEST_IR spaces away.
  float secClosestAng;  // To store the angle of the second closest sensor.
  float secClosestVal;  // To store the value of the second closest sensor.
  int secIndex;         // To store the index of the second closest sensor.


  secIndex = sensorsManipulated[i].getIndex();

// Initially set secIndex to the index of the closest sensor (for starting the loop).
secIndex = sensorsManipulated[i].getIndex();

// Loop to find the second closest sensor based on the index proximity.
do {
    i++;  // Move to the next sensor in the sorted array.
    secIndex = sensorsManipulated[i].getIndex();  // Get the index of the current sensor.
} while (abs(secIndex - sensorsManipulated[0].getIndex()) > NUM_SPACES_FROM_CLOSEST_IR &&
         abs(secIndex - sensorsManipulated[0].getIndex()) != NUM_IR - 1);

// Store the angle and value of the found second closest sensor.
secClosestAng = sensorsManipulated[i].GetAngle();
secClosestVal = sensorsManipulated[i].GetValue();

  //if the two angles have a huge gap between them, they are 315 and 0 in that order and we
  if ((closestAng - secClosestAng) > 250)
    secClosestAng += 360;
  //if the two angles have a minus huge gap between them, they are 0 and 315 in that order
  else if ((closestAng - secClosestAng) < -250)
    secClosestAng -= 360;

  /*
  You want the ballAngle to be closestAng + corrections.
  corrections will be how the difference between closest angles, 
  times how different their values are squared so that if they are far, it'll matter less.
  If they both have the same val, then closestVal / secClosestVal = 1 and the whole angle is the average between the two.
  devision by 2 is neccecery so that when vals are equal, the ang will be the average
  desmos link to demonstrate with some vals: https://www.desmos.com/calculator/3jouqeacbo
  */
  ballAngle = closestAng + (secClosestAng - closestAng) / 2 * pow((closestVal / secClosestVal), 2);
  if (ballAngle > 360)
    ballAngle -= 360;
  if (ballAngle < 0)
    ballAngle += 360;

  // Update ball angle using moving average to smooth the result.
  ballAngle = ballAngs.updateData(ballAngle);
  return ballAngle;
}


// Method to display sensor values and the ball angle on the Serial Monitor.
void IRArray::display() {
  for (int i = 0; i < NUM_IR; i++) {
    Serial.print(sensors[i].GetValue());  // Print each sensor's value.
    Serial.print(" | ");
  }
  Serial.print("Angle: ");
  Serial.println(ballAngle);  // Print the calculated ball angle.
}


// A far more simple (and less accurate) method to calc ball angle
float IRArray::CalculateAngle() {
  readVals();  // Read values from all sensors.

  // Create a copy of the sensors array for manipulation.
  IRSensor sensorsManipulated[NUM_IR];
  for (int i = 0; i < NUM_IR; i++) {
    sensorsManipulated[i] = sensors[i];
  }

  // Sort the copied sensor array based on their values.
  shellSortKnuth(sensorsManipulated, NUM_IR, lessThen);

  // Set the ball angle to the angle of the sensor with the smallest value.
  ballAngle = sensorsManipulated[0].GetAngle();
  return ballAngle;  // Return the calculated ball angle.
}

float IRArray::getBallAngle() {
  return ballAngle;
}