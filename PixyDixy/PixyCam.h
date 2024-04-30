#ifndef __PIXYCAM__
#define __PIXYCAM__

#include <Arduino.h>
#include <Pixy2.h>

class PixyCam {
private:
  float BlockHeight;
  float Distance;
  float BlockXPos;
  float Angle;
  const int Center = 158; //(316 / 2) => pixel width 

public:
  PixyCam();
  UpdateData();
  CalculateDistance();
  CalculateAngle();
}

#endif