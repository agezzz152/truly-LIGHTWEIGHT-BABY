int mystr; //Initialized variable to store recieved data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  mystr = Serial1.read(); //Read the serial data and store in var
  Serial.println(mystr); //Print data on Serial Monitor
  delay(20);
  digitalWrite(LED_BUILTIN, mystr);
}
