#ifndef __WHEEL__
#define __WHEEL__
#include <Arduino.h>
#include "parameters.h"

//returns whether x is positive or negative. returns 1 when positive and -1 when negative


class wheel {
private:
  int _pwm, _in1, _in2;
  int _index;  //0 = RF, 1 = RB, 2 = LB, 3 = LF


public:
  wheel() {}

  wheel(int& pwm, int& in1, int& in2, int& idx) {
    _pwm = pwm;
    _in1 = in1;
    _in2 = in2;
    _index = idx;
  }

  void wheelSetup() {
    pinMode(_pwm, OUTPUT);  //we have to set PWM pin as output
    pinMode(_in1, OUTPUT);  //Logic pins are also set as output
    pinMode(_in2, OUTPUT);
  }

  void writePWM(int pwmVal) {
    analogWrite(_pwm, pwmVal);
  }

  void writeIN1(bool in1Val) {
    digitalWrite(_in1, in1Val);
  }

  void writeIN2(bool in2Val) {
    digitalWrite(_in2, in2Val);
  }
};




#endif