/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int IRPin = 2;
int lastSeenChange = 0;
int lastVal = 1;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(IRPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int CurrentVal = digitalRead(IRPin);
  if (lastVal ^ CurrentVal)
    lastSeenChange = 0;
  else
    lastSeenChange++;
  // print out the state of the button:
  delay(1);  // delay in between reads for stability

  if (lastSeenChange < 5)
    Serial.print("1 ");
  else
    Serial.print("0 ");

  Serial.println(CurrentVal);

  lastVal = CurrentVal;
}



