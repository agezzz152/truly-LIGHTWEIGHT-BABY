  unsigned long previousMillis = 0;  // variable to store the previous time
  unsigned long eventStartTime = 0;  // variable to store the start time of the special event
  const int eventDuration = 10;      // duration of the special event (in milliseconds)
  const int interval = 1000;         // interval at which to do something (in milliseconds)
  int IRPin = 2;
  int VCCpin = 6;
  int lastSeenChange = 0;
  int lastVal = 1;


  void setup() {
    // initialize serial communication:
    Serial.begin(9600);
    pinMode(IRPin, INPUT);
    pinMode(VCCpin, OUTPUT);
  }

  void loop() {
    // get the current time
    unsigned long currentMillis = millis();



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
    digitalWrite(VCCpin, 1);

    // check if 1000 milliseconds have passed
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(VCCpin, 0);

      myDelay(10);
    }
  }



  void myDelay(int millDelay) {
    int startTime = millis();
    int currentT;
    while (true) {
      currentT = millis();
      if (currentT >= startTime + millDelay) {
        break;
      }
    }
  }