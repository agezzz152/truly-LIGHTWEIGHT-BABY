#include "Arduino.h"
#include "HardwareSerial.h"
#include "PixyCam.h"


PixyCam::PixyCam() {
  pixy.init();
}

void PixyCam::UpdateData() {

  BlockHeight[2] = {-1000.00};
  Distance[2] = {-1000.00};
  BlockXPos[2] = {-1000.00};
  Angle[2] = {-1000.00};


  
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

    int n = pixy.ccc.blocks[i].m_signature - 1;
    detectedGoal = n;
    BlockHeight[n] = pixy.ccc.blocks[i].m_height;
    Distance[n] = CalculateDistance(BlockHeight[n]);
    BlockXPos[n] = pixy.ccc.blocks[i].m_x;
    Angle[n] = CalculateAngle(Distance[n], BlockXPos[n], n);

  //   if (pixy.ccc.blocks[i].m_signature == 1) {
  //     detectedGoal = 0;
  //     BlockHeight[0] = pixy.ccc.blocks[i].m_height;
  //     Distance[0] = CalculateDistance(BlockHeight[0]);
  //     BlockXPos[0] = pixy.ccc.blocks[i].m_x;
  //     Angle[0] = CalculateAngle(Distance[0], BlockXPos[0]);
  //   }

  //   else if (pixy.ccc.blocks[i].m_signature == 2) {
  //     detectedGoal = 1;
  //     BlockHeight[1] = pixy.ccc.blocks[i].m_height;
  //     Distance[1] = CalculateDistance(BlockHeight[1]);
  //     BlockXPos[1] = pixy.ccc.blocks[i].m_x;
  //     Angle[1] = CalculateAngle(Distance[1], BlockXPos[1]);
      }
   }
}

float PixyCam::CalculateDistance(float height) {
  float dist;
  float a = height;
  dist = 173.6 * pow(2.71, (-0.023 * a)); // ==> 1856.6 * pow(a, -0.88) old nums
  return dist;
}

float PixyCam::CalculateAngle(float distance, float x, int n) {
  float delta = Center - x;
  if (delta < 0) {
    right[n] = true;
    abs(delta);
  }
  else {
    right[n] = false;
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

int PixyCam::getGoal() {
  return detectedGoal;
}