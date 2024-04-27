#include "motors.h"

int signOfX(const int& x) {
  return x / abs(x);
}

motors::motors(int *pwm, int *in1, int *in2) {
  for (int i = 0; i < NUM_MOTORS; i++) {
    wheels[i] = wheel(pwm[i], in1[i], in2[i], i);
  }

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}


void motors::motorSetup() {
  for (int i = 0; i < NUM_MOTORS; i++) {
    wheels[i].wheelSetup();
  }
}


/* function moves the robot in a certien angle. 
angle = angle between dribler and chosen angle of movement,
sped = linear speed,
speen = circular speed. */
void motors::moov(double dirAngle, const double &sped, const double &speen) {
  //angle in a number betwin 0 and 2pi, sped in a number betwin 0 and 255, and speen is a number betwin 0 and 255
  int i;
  //turning the angle from degrees to rad
  dirAngle = dirAngle / (180) * (3.141592653589793);

  //if not inputed for the robot to stop
  if (!(sped == 0) || !(speen == 0)) {


    speedPart = (abs(sped)) / (abs(sped) + abs(speen));
    speenPart = 1 - speedPart;

    /* adding the reguler forward, beckward, left, right movment
    rad45 = 45 degrees in rads */

    pwmVal[0] = -sin(rad45 - dirAngle) * sped * speedPart;  //right front
    pwmVal[1] = -sin(rad45 + dirAngle) * sped * speedPart;  //right back
    pwmVal[2] = sin(rad45 - dirAngle) * sped * speedPart;   //left back
    pwmVal[3] = sin(rad45 + dirAngle) * sped * speedPart;   //left front


    // adding the circular motion for the motors
    for (i = 0; i < 4; i++) {
      pwmVal[i] = pwmVal[i] + (speen * speenPart);

      if (pwmVal[i] > 250) {
        pwmVal[i] = 250;
      }
      if (pwmVal[i] < -250) {

        pwmVal[i] = -250;
      }
      wheels[i].writePWM(abs(pwmVal[i]));

      wheels[i].writeIN1((signOfX(pwmVal[i]) + 1) / 2);
      wheels[i].writeIN2(1 - ((signOfX(pwmVal[i]) + 1) / 2));
    }
  }
}