#include "Arduino.h"
#include "HardwareSerial.h"
#include "PixyCam.h"


PixyCam::PixyCam() {
  pixy.init();
}

void PixyCam::UpdateData() {

  BlockHeight = -1000;
  Distance = -1000;
  BlockXPos = -1000;
  Angle = -1000;


  
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

    if (pixy.ccc.blocks[i].m_signature == 1) {
      detectedGoal = 0;
      BlockHeight[0] = pixy.ccc.blocks[i].m_height;
      Distance[0] = CalculateDistance(BlockHeight);
      BlockXPos[0] = pixy.ccc.blocks[i].m_x;
      Angle[0] = CalculateAngle(Distance, BlockXPos);
    }

    else if (pixy.ccc.blocks[i].m_signature == 2) {
      detectedGoal = 1;
      BlockHeight[1] = pixy.ccc.blocks[i].m_height;
      Distance[1] = CalculateDistance(BlockHeight);
      BlockXPos[1] = pixy.ccc.blocks[i].m_x;
      Angle[1] = CalculateAngle(Distance, BlockXPos);
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

float PixyCam::GetDistance(int index) {
  return Distance[index];
}

float PixyCam::GetAngle(int index) {
  return Angle[index];
}

int getGoal() {
  return detectedGoal;
}