// When we started to work on this code, only us and god understood it.
// Now, only god understands it.
// In order to warn others from this code, please update the counter accordingly:
// Hours watsted on stupid mistakes ( = aka this code): 10 

#include <Adafruit_NeoPixel.h>

#define PIN 5          // Define the pin you're using to control the Neopixels
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip

#define NUM_LDR 6

int const LDR[] = { 15, 2, 4, 13, 12, 14 };  //from the rightest LDR clockwise
float LDRval[NUM_LDR];

const int pwm[] = { 9, 12, 11, 10 };  //right up and clockwise
const int in_1[] = { 30, 37, 35, 32 };
const int in_2[] = { 31, 36, 34, 33 };
#define NUM_MOTORS 4

double motors[4] = { 0 };
double speedPart;
double speenPart;
double sixtyrad;
double fortfiverad;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(pwm[i], OUTPUT);   //we have to set PWM pin as output
    pinMode(in_1[i], OUTPUT);  //Logic pins are also set as output
    pinMode(in_2[i], OUTPUT);
  }
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(100);
}

void loop() {
  colorWipe(strip.Color(30, 0, 0), 50);
  for (int i = 0; i < NUM_LDR; i++) {
    LDRval[i] = LDRcheck(LDR[i]);
    Serial.print(LDRval[i]);
    Serial.print(" - ");
  }
  int z = whichLDR(LDRval, NUM_LDR);
  Serial.print("| ");
  Serial.print(z);
  Serial.println(" |");
  moov(180, 150, 0);
  delay(10);
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


int signOFx(int x) {
  return x / abs(x);
}



int LDRcheck(int conn) {
  int a = analogRead(conn);
  return a;
}

int whichLDR(float vals[], int n) {
  for (int i = 0; i < n; i++) {
    if (vals[i] > 500)
      return i;
  }

  return -1;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}


