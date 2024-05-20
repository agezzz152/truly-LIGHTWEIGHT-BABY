//*****PixyCam.cpp*****//
#include "Arduino.h"
#include "HardwareSerial.h"
#include "PixyCam.h"


PixyCam::PixyCam() {
  pixy.init();  // Starts up the camera.
}

void PixyCam::UpdateData() {

  BlockHeight[0] = -1000;  //resets the variables of every goal so that we would get -1000 if no block is detected.
  BlockHeight[1] = -1000;
  Distance[0] = -1000;
  Distance[1] = -1000;
  Angle[0] = -1000;
  Angle[1] = -1000;


  int i;
  pixy.ccc.getBlocks();             // A pixy function that updates the blocks that are detected by the pixy.
  int numBks = pixy.ccc.numBlocks;  // Save the number of blocks the were detected.
  if (numBks) {                     // If there are detected blocks
    for (i = 0; i < numBks; i++) {
      int n = pixy.ccc.blocks[i].m_signature - 1;               // Gets the signature num of the detected block, and converts it to an index (the first signature is 1 so we want it to be 0)
      detectedGoal = n;                                         // updates the detected goal as the index of the signature.
      BlockHeight[n] = pixy.ccc.blocks[i].m_height;             // Updates the height of the block in it's correct index
      Distance[n] = CalculateDistance(BlockHeight[n]);          // Calculates and Updates the distance of the block in it's correct index
      BlockXPos[n] = pixy.ccc.blocks[i].m_x;                    // Updates the Xpos of the block in it's correct index
      Angle[n] = CalculateAngle(Distance[n], BlockXPos[n], n);  // Calculates and Updates the angle of the block in it's correct index
    }
  }
}

float PixyCam::CalculateDistance(float height) {  // gets a height value
  float dist;
  float a = height;
  dist = 5589.7 * pow(a, -1.168);  // This function was created after measurring each distance and it's corresponding height.
  return dist;                     // Returns the distance
}

float PixyCam::CalculateAngle(float distance, float x, int n) {  // gets a distance value, an Xpos value, and the index of the goal.
  float delta = Center - x;                                      // calculates the differance between an Xpos of the block and the center of the camera
  if (delta < 0) {
    right[n] = true;     // If the delta is negative then it means that the goal is on the right of the robot
    delta = abs(delta);  // Gets the absolute value of the delta
  } else {
    right[n] = false;  // Else, the goal is on the left of the robot.
  }
  float ang = asin(delta / (distance * 5)) * 90;  // Uses a right triangle trigo. calculting the angle between the base of the triangle and the hypotenuse. The random numbers are there to help convert between the distance and delta, because they are in diferent mesurement units.
  return ang;                                     // Returns the angle
}

float PixyCam::GetDistance(int index) {
  return Distance[index];  // Returns the distance of the goal with the given index.
}

float PixyCam::GetAngle(int index) {
  return Angle[index];  // Returns the angle of the goal with the given index.
}

int PixyCam::getGoal() {
  return detectedGoal;  // Returns the index of the detected goal
}