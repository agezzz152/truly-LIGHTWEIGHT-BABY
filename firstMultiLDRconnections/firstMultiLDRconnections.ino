#include <Adafruit_NeoPixel.h>

#define PIN 5          // Define the pin you're using to control the Neopixels
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip

#define NUM_LDR 6

int const LDR[] = { 15, 2, 4, 13, 12, 14 };  //from the rightest LDR clockwise
float LDRval[NUM_LDR];


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(100);
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
}
