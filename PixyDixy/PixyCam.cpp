#include "Arduino.h"
#include "HardwareSerial.h"
#include "PixyCam.h"


PixyCam::PixyCam() {
  pixy.init();
}

void PixyCam::UpdateData() {

  BlockHeight = 0;
  Distance = 0;
  BlockXPos = 0;
  Angle = 0;


  
  int i;
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i = 0; i<pixy.ccc.numBlocks; i++) {
    Serial.print(" block ");
    Serial.print(i);
    Serial.print(": ");
    pixy.ccc.blocks[i].print();
    BlockHeight = pixy.ccc.blocks[i].m_height;
    Distance = CalculateDistance(BlockHeight);
    BlockXPos = pixy.ccc.blocks[i].m_x;
    Angle = CalculateAngle(Distance, BlockXPos);
    }
  }
}

float PixyCam::CalculateDistance(float height) {
  float dist;
  float a = height;
  dist = 173.6 * pow(2.71, (-0.023 * a)); // ==> 1856.6 * pow(a, -0.88) old nums
  return dist;
}

float PixyCam::CalculateAngle(float distance, float x) {
  float delta = Center - x;
  if (delta < 0) {
    right = true;
    abs(delta);
  }
  else {
    right = false;
  }
  float ang = asin(delta / (distance * 5)) * 90;
  return ang;
}

float PixyCam::GetDistance() {
  return Distance;
}

float PixyCam::GetAngle() {
  return Angle;
}