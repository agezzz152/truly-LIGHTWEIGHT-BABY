int mystr = 1;  //String data
int swtch = 11;
void setup() {
  // Begin the Serial at 9600 Baud
  pinMode(swtch, INPUT);
  Serial1.begin(9600);
}

void loop() {
  // mystr = 0;
  // for (int i = 0; i < 20; i++) {
  //   delay(10);
  // }
  mystr = checkSwitch(swtch);
  Serial1.write(mystr);  //Write the serial data
  // for (int i = 0; i < 20; i++) {
  //   Serial1.write(mystr);  //Write the serial data
  //   delay(10);
  // }
}

bool checkSwitch(int a) {
  bool bul = (bool) digitalRead(a);
  return bul;
}
