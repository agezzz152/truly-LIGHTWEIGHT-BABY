#ifndef __PIXYCAM__
#define __PIXYCAM__

#include <Arduino.h>
#include <Pixy2.h>
#include <math.h>

class PixyCam {
private:
  Pixy2 pixy; // Create a pixt object, and we will use this as our base to our code
  float BlockHeight[2]; // An arry that saves the height of the block. [0] is blue goal and [1] is yellow goal.
  float Distance[2]; // An arry that saves the distance of the block. [0] is blue goal and [1] is yellow goal.
  float BlockXPos[2]; // An arry that saves the X position of the center of the block. [0] is blue goal and [1] is yellow goal.
  float Angle[2]; // An arry that saves the angle of  of the block. [0] is blue goal and [1] is yellow goal.
  bool right[2]; // An arry that saves the direction of the angle of the block, right or left. [0] is blue goal and [1] is yellow goal.
  int detectedGoal; //If 0 it is blue. If 1 is Yellow.
  const int Center = 158; //(316 / 2) => pixel width 
  float CalculateDistance(float height); //Using a function that we created based on the relation between the height of a block and it's distance. Based on the height, the function will calculate the dist
  float CalculateAngle(float distance, float x, int n); // This function gets a distance, the XPOS of the block, and it's index, and then calculates the angle, and saves it in the correct index of the angle variable.

public:
  PixyCam(); // Sets up the camera.
  void UpdateData(); // reads the data from the camera and updates the variables.
  float GetDistance(int index); // Return the distance of the given index
  float GetAngle(int index); // Return the angle of the given index.
  int getGoal(); // Returns the number of the goal. 0 is blue, 1 is yellow.
};

#endif