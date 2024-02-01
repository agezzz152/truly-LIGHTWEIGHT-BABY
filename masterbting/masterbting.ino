// When we started to work on this code, only us and god understood it.
// Now, only god understands it.
// In order to warn others from this code, please update the counter accordingly:
// Hours watsted on stupid mistakes ( = aka this code): 13

#include <Adafruit_NeoPixel.h>
long int t1;
long int currentT;

#define PIN 5          // Define the pin you're using to control the Neopixels
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip
#define ANGLE_BETWEEN_LDR 45
#define NUM_LDR 6
#define RETREAT_DELAY 50

// int const LDR[] = { 15, 2, 4, 13, 12, 14 };  //from the rightest LDR clockwise, with esp
int const LDR[NUM_LDR] = { A2, A3, A4, A5, A6, A7 };  //from the rightest LDR clockwise, with arduino connections
float LDRval[NUM_LDR];
float LDRavg[NUM_LDR];
bool LDRActive[6] = { 0 };
bool isRetreating = 0;
double lAng = 0;

const int pwm[] = { 9, 12, 11, 10 };  //right up and clockwise
const int in_1[] = { 30, 37, 35, 32 };
const int in_2[] = { 31, 36, 34, 33 };
#define NUM_MOTORS 4

double ang, liniarSped, spinSped;

double motors[4] = { 0 };
double speedPart;
double speenPart;
double sixtyrad;
double fortfiverad;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

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
  ang = 0;
  liniarSped = 75;
  spinSped = 0;

  colorWipe(strip.Color(30, 0, 0), 50);
  // if not during the proccess of retreating from a white line
  if (!isRetreating) {
    //finds out which ldrs are active
    whichLDR(LDRval);
    //calc the angle of the ldrs detected and store in global variable
    LdrAngle();
    moov(ang, liniarSped, spinSped);
  }

  //function for checking 
  handleRetreat();

  displayVals();
  strip.show();
}



//MOVE FUNCTIONS:
/* function moves the robot in a certien angle. 
angle = angle between dribler and chosen angle of movement,
sped = linear speed,
speen = circular speed. */
void moov(double angle, const double& sped, const double& speen) {
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



void handleRetreat() {
  currentT = millis();

  // Check if it's time to stop retreating
  if (isRetreating && (currentT > t1 + RETREAT_DELAY)) {
    isRetreating = false;
  }

  // Check if retreat mode is active
  if (isRetreating) {
    moov(ang + 180, 2 * liniarSped, spinSped);
  }
}


//returns whether x is positive or negative. returns 1 when positive and -1 when negative
int signOFx(const int& x) {
  return x / abs(x);
}

//LDR FUNCTIONS:
/*ex:  printing the ldr values, and also Prints the index of the ldr on white line. if none detected prints -1.
  out: returns the index of the ldr that's detecting a white line */

//gets an ldr pin, and returns the value the ldr is measuring
int LDRcheck(const int& ldrPin) {
  int a = analogRead(ldrPin);
  return a;
}



/*explanation: finds which ldr on a white line.
  inputs: vals = array all the ldr measured values, n = number of LDRs.
  outputs: returns the first ldr which returns a higher than 250 val */
void whichLDR(float* vals) {

  for (int i = 0; i < NUM_LDR; i++) {
    if (vals[i] < 800) {
      LDRActive[i] = 1;
    } else {
      LDRActive[i] = 0;
    }
  }
}

//returns which angle the inputed ldr is at (when zero degrees are set to the dribler)
void LdrAngle() {
  int sumAng = 0;
  int NActiveLDR = 0;
  for (int i = 0; i < NUM_LDR; i++) {
    if (LDRActive[i]) {
      sumAng += 70 + i * 45;
      NActiveLDR++;
    }
  }
  if (NActiveLDR > 0) {
    t1 = millis();
    isRetreating = 1;
    lAng = (sumAng / NActiveLDR);
  } else {
    lAng = -1;
  }
}


void displayVals() {
  int i;
  for (i = 0; i < NUM_LDR; i++) {
    LDRval[i] = LDRcheck(LDR[i]);
    Serial.print(LDRval[i]);
    Serial.print(" - ");
  }
  Serial.print("| ");
  for (i = 0; i < NUM_LDR; i++) {
    if (LDRActive[i]) {
      Serial.print(i);
      Serial.print(", ");
    }
  }
  Serial.print(", ");
  Serial.print(lAng);
  Serial.println(" |");



  for (i = 0; i < NUM_LDR; i++) {
    if (LDRActive[i]) {
      strip.setPixelColor(i * 8, 100, 0, 50);
      strip.setPixelColor(i * 8 + 7, 100, 0, 50);
    }
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
}
