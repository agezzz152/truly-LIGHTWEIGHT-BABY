#include <Adafruit_NeoPixel.h>

#define PIN 5          // Define the pin you're using to control the Neopixels
#define NUM_PIXELS 8*7  // Define the number of Neopixels in your strip
#define NUM_LDR 6

// int const LDR[] = { 15, 2, 4, 13, 12, 14 };  //from the rightest LDR clockwise, with esp connections
int const LDR[] = { A2, A3, A4, A5, A6, A7};  //from the rightest LDR clockwise, with arduino connections
float LDRval[NUM_LDR];
float LDRavg[NUM_LDR];
bool LDRActive[6] = {0};
int LDRLastVal[NUM_LDR][3] = {{0}};


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(100);
}

void loop() {
  colorWipe(strip.Color(30, 0, 0), 50);
  whichLDR(LDRval);
  displayVals();
  
}

int signOFx(int x) {
  return x / abs(x);
}



int LDRcheck(int conn) {
  int a = analogRead(conn);
  return a;
}


void whichLDR(float* vals) {

  for (int i = 0; i < NUM_LDR; i++) {
    if (vals[i] < 800) {
      LDRActive[i] = 1;
    }
    else {
      LDRActive[i] = 0;
    }
  }
}


double LdrAngle() {
  int sumAng = 0;
  int NActiveLDR = 0;
  for (int i = 0; i <  NUM_LDR; i++) {
    if (LDRActive[i]) {
      sumAng += 70 + i * 45;
      NActiveLDR++;
    }
  }
  if (NActiveLDR > 0) {
    return (sumAng / NActiveLDR);
  }
  else {
    return -1;
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
  Serial.print(LdrAngle());
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
    strip.show();
  }
}


