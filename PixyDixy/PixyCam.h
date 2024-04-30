#ifndef __PIXYCAM__
#define __PIXYCAM__

#include <Arduino.h>
#include <Pixy2.h>
#include <math.h>

class PixyCam {
private:
  Pixy2 pixy;
  float BlockHeight;
  float Distance;
  float BlockXPos;
  float Angle;
  bool right;
  const int Center = 158; //(316 / 2) => pixel width 
  float CalculateDistance(float height);
  float CalculateAngle(float distance, float x);

public:
  PixyCam();
  void UpdateData();
  float GetDistance();
  float GetAngle();
};

#endif