#include <Adafruit_NeoPixel.h>

//neopixel7
#define PIN 5          // Define the pin you're using to control the Neopixels
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int pwm[] = { 9, 12, 11, 10 };  //right up and clockwise
const int in_1[] = { 30, 37, 35, 32 };
const int in_2[] = { 31, 36, 34, 33 };
#define NUM_MOTORS 4

double motors[4] = { 0 };
double speedPart;
double speenPart;
double sixtyrad;
double fortfiverad;

//For providing logic to L298 IC to choose the direction of the DC motor

void setup() {

  Serial.begin(9600);
  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(pwm[i], OUTPUT);   //we have to set PWM pin as output
    pinMode(in_1[i], OUTPUT);  //Logic pins are also set as output
    pinMode(in_2[i], OUTPUT);
  }

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(100);


  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}



void moov(double angle, double sped, double speen) {  //angle in a number betwin 0 and 2pi, sped in a number betwin 0 and 255, and speen is a number betwin 0 and 255
  int i;
  //turning the angle from degrees to rad
  angle = angle / (180) * (3.141592653589793);

  //if inputed for the robot to stop
  if (!(sped == 0) || !(speen == 0)) {

    for (i = 0; i < 4; i++) {
      motors[i] = 0;
    }

    speedPart = (abs(sped)) / (abs(sped) + abs(speen));
    speenPart = 1 - speedPart;

    /* adding the reguler forward, beckward, left, right movment
    the first one is equal to 60 degrees in rads
    the second is 45 degrees in rads */

    speedPart = (abs(sped)) / (abs(sped) + abs(speen));
    speenPart = 1 - speedPart;


    sixtyrad = 1.0472;
    fortfiverad = 0.785398;
    motors[0] = -sin(fortfiverad - angle) * sped * speedPart;  //right front
    motors[1] = -sin(fortfiverad + angle) * sped * speedPart;  //right back
    motors[2] = sin(fortfiverad - angle) * sped * speedPart;   //left back
    motors[3] = sin(fortfiverad + angle) * sped * speedPart;   //left front


    // adding the circular motion for the motors
    for (i = 0; i < 4; i++) {
      motors[i] = motors[i] + (speen * speenPart);

      if (motors[i] > 250) {
        motors[i] = 250;
      }
      if (motors[i] < -250) {

        motors[i] = -250;
      }
      analogWrite(pwm[i], abs(motors[i]));

      digitalWrite(in_1[i], (signOFx(motors[i]) + 1) / 2);
      digitalWrite(in_2[i], 1 - ((signOFx(motors[i]) + 1) / 2));
    }
  }
}

double signOFx(double x) {
  return x / abs(x);
}

void colorWipe(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}

void myDelay(int millDelay) {
  int startTime = millis();
  //Serial.print("StartTime: ");
  //Serial.println(startTime);
  int currentT;
  while (true) {
    currentT = millis();
    //Serial.print("CurrentT: ");
    //Serial.println(currentT);
    if (currentT >= startTime + millDelay) {
      break;
    }
  }

}


void loop() {
  //turnes the entire neopixel strip to the color red
  // colorWipe(strip.Color(40, 0, 0));
  // double ang = 315;
  // double linSPed = 175;
  // double Spin;
  // // Spin = (180 - abs(ang - 180)) / 180 * linSPed;
  // Spin = linSPed/(180*180) * ang * (360 - ang);
  // // Spin = linSPed / 3;
  // if (ang >= 180) {
  //   Spin = -Spin;
  // }

  

  moov(0, 0 , 100);
  // myDelay(500);
  // moov(180,100,0);
  // myDelay(500);
  // moov(90, 100, 0);
  // myDelay(500);
  // moov(270,100,0);
  // myDelay(500);
  delay(10);
  // int n = 3;
  // digitalWrite(in_1[n], 1);
  // digitalWrite(in_2[n], 0);
  // analogWrite(pwm[n], 150);
}