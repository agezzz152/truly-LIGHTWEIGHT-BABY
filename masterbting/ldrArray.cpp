//*****ldrArray.cpp*****//
#include "ldrArray.h"

// Constructor that initializes the LDR sensors with given pins
ldrArray::ldrArray(int *pins) {
  // Loop through the number of LDRs and initialize each one
  for (int i = 0; i < NUM_LDR; i++) {
    LDR[i] = ldrSensor(pins[i], i);
  }
}

// Method to get the value from the LDR sensor at the specified index
int ldrArray::getVal_i(int index) {
  return LDR[index].getVal();
}

// Method to get the status (active or not) of the LDR sensor at the specified index
bool ldrArray::getStatus_i(int index) {
  return LDR[index].getStatus();
}

// Method to read values from all LDR sensors
void ldrArray::ReadAllLDR() {
  // Loop through each LDR sensor and call its read method
  for (int i = 0; i < NUM_LDR; i++) {
    LDR[i].read();
  }
}

// Method to calculate the angle of the detected white line
double ldrArray::CalcLineAngle() {
  int sumAng = 0;  // Sum of angles of active LDR sensors
  NActiveLDR = 0;  // Counter for active LDR sensors

  // Loop through each LDR sensor
  for (int i = 0; i < NUM_LDR; i++) {
    // If the LDR sensor is active (detects a white line)
    if (LDR[i].read()) {
      // Add the angle of the active LDR sensor to the sum
      sumAng += LDR[i].getAngle();
      NActiveLDR++;  // Increment the count of active LDR sensors
    }
  }

  // If there are active LDR sensors
  if (NActiveLDR > 0) {
    timeSinceStartedRetreating = millis();  // Record the current time
    isRetreating = true;                    // Set the retreating flag
    // Calculate the average angle of all active LDR sensors
    angle = (sumAng / NActiveLDR);
  } else {
    // If no LDR sensor detects a white line, set angle to -1
    angle = -1;
  }
  return angle;  // Return the calculated angle
}

/* Method to handle the retreating process
   Recives a motors object (so it can control the robot's motors)
   Also recives an desired ang, sped and spin that indicate 
   where will the motors go when on white line */
void ldrArray::handleRetreat(motors &drivingSystem, const double &ang, const double &sped, const double &spin) {
  currentT = millis();  // Get the current time

  // Check if it's time to stop retreating
  if (isRetreating && (currentT > timeSinceStartedRetreating + RETREAT_DELAY)) {
    isRetreating = false;  // Reset the retreating flag
  }

  // If retreat mode is active
  if (isRetreating) {
    // Command the driving system to move with specified angle, speed, and spin
    drivingSystem.moov(ang, sped, spin);
  }
}
