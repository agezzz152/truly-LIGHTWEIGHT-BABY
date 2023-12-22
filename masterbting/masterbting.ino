// When we started to work on this code, only us and god understood it.
// Now, only god understands it.
// In order to warn others from this code, please update the counter accordingly:
// Hours watsted on stupid mistakes ( = aka this code): 13

#include <Adafruit_NeoPixel.h>

#define PIN 5          // Define the pin you're using to control the Neopixels
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip
#define ANGLE_BETWEEN_LDR
#define NUM_LDR 6

// int const LDR[] = { 15, 2, 4, 13, 12, 14 };  //from the rightest LDR clockwise, with esp
int const LDR[NUM_LDR] = { A7, A6, A5, A4, A3, A2 };  //from the leftest LDR Counter-Clockwise, with arduino ldr Pinections
int LDRval[NUM_LDR];
int onWhiteLine;

const int pwm[] = { 9, 12, 11, 10 };  //right up and clockwise
const int in_1[] = { 30, 37, 35, 32 };
const int in_2[] = { 31, 36, 34, 33 };
#define NUM_MOTORS 4

double motors[4] = { 0 };
double speedPart;
double speenPart;
double sixtyrad;
double fortfiverad;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + onWhiteLine800);


void setup() {
  Serial.begin(9600);

  //motors:
  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(pwm[i], OUTPUT);   //we have to set PWM pin as output
    pinMode(in_1[i], OUTPUT);  //Logic pins are also set as output
    pinMode(in_2[i], OUTPUT);
  }
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  //neoPixel:
  strip.begin();
  strip.show();  // onWhiteLinee all pixels to 'off'
  strip.setBrightness(100);

  //Led for control
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  //turning the ldr off most of the time
  digitalWrite(LED_BUILTIN, 0);



  colorWipe(strip.Color(30, 0, 0));

  onWhiteLine = ldrRutine();

  if (onWhiteLine != -1) {
    if (onWhiteLine > 2) {
      moov(LdrAngle(onWhiteLine) - 90, 50, 0);
    } else{
      moov(LdrAngle(onWhiteLine) + 90, 50, 0);
    }

    strip.setPixelColor(onWhiteLine * 8, 100, 0, 50);
    strip.setPixelColor(onWhiteLine * 8 + 7, 100, 0, 50);
    // for (int i = onWhiteLine*8; i < 8*onWhiteLine + 8; i++){
    //   strip.setPixelColor(i, 100, 0, 0);
    // }
  } else {
    moov(0, 50, 0);
  }

  strip.show();


  delay(5);
}


//MOVE FUNCTIONS:
/* function moves the robot in a certien angle. 
angle = angle between dribler and chosen angle of movement,
sped = linear speed,
speen = circular speed. */
void moov(double angle, double sped, double speen) {
  //angle in a number betwin 0 and 2pi, sped in a number betwin 0 and 255, and speen is a number betwin 0 and 255
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


//returns whether x is positive or negative. returns 1 when positive and -1 when negative
int signOFx(int x) {
  return x / abs(x);
}

//LDR FUNCTIONS:
/*ex:  printing the ldr values, and also Prints the index of the ldr on white line. if none detected prints -1.
  out: returns the index of the ldr that's detecting a white line */
int ldrRutine() {
  for (int i = 0; i < NUM_LDR; i++) {
    LDRval[i] = LDRcheck(LDR[i]);
    Serial.print(LDRval[i]);
    Serial.print(" - ");
  }
  int onWhiteLine = whichLDR(LDRval, NUM_LDR);
  Serial.print("| ");
  Serial.print(onWhiteLine);
  Serial.println(" |");

  return onWhiteLine;
}

//gets an ldr pin, and returns the value the ldr is measuring
int LDRcheck(int ldrPin) {
  int a = analogRead(ldrPin);
  return a;
}

//returns which angle the inputed ldr is at (when zero degrees are set to the dribler)
float LdrAngle(int iLDR) {
  return 70 + iLDR * ANGLE_BETWEEN_LDR;
}


/*explanation: finds which ldr on a white line.
  inputs: vals = array all the ldr measured values, n = number of LDRs.
  outputs: returns the first ldr which returns a higher than 250 val */
int whichLDR(int vals[], int n) {
  for (int i = 0; i < n; i++) {
    if (vals[i] > 250)
      return i;
  }

  return -1;
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
}
