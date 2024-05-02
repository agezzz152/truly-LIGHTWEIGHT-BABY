#ifndef __PIXYCAM__
#define __PIXYCAM__

#include <Arduino.h>
#include <Pixy2.h>
#include <math.h>

class PixyCam {
private:
  Pixy2 pixy;
  float BlockHeight[2];
  float Distance[2];
  float BlockXPos[2];
  float Angle[2];
  bool right[2];
  int detectedGoal; //If 0 it is blue. If 1 is Yellow.
  const int Center = 158; //(316 / 2) => pixel width 
  float CalculateDistance(float height);
  float CalculateAngle(float distance, float x);

public:
  PixyCam();
  void UpdateData();
  float GetDistance(int index);
  float GetAngle(int index);
};

#endif