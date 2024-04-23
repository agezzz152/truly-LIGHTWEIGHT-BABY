#ifndef __DRIBLER__
#define __DRIBLER__
#include "parameters.h"
#include <Arduino.h>

class dribler {
private:
  int in1, in2, pwm, Hbridge;

public:

  //pins is an array of 4, with pins arranged like in1, in2, pwm, HBRIDGEMODE
  dribler(int* pins) {
    in1 = pins[0];
    in2 = pins[1];
    pwm = pins[2];
    Hbridge = pins[3];
  }

  void dribSetup(int Nmotors = 1) {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(pwm, OUTPUT);
    analogWrite(pwm, 0);
    switch (Nmotors) {
      case 1:
        digitalWrite(Hbridge, 1);
      case 2:
        digitalWrite(Hbridge, 0);
    }
  }

  void Drip(bool direc, bool state = HIGH) {
    digitalWrite(in1, direc);
    digitalWrite(in2, !direc);
    if (state) {
      analogWrite(pwm, DRIB_POWER);
    } else {
      analogWrite(pwm, 0);
    }
  }
};









#endif