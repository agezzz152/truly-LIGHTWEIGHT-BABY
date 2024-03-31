/* dump.ino Example sketch for IRLib2
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
*/
//This includes everything. Not generally recommended.
//It's better to include only the parts of library you really need.
//But for this example it's quick and easy. See "comboDump" example
//for a more efficient way.
#include "IRLibAll.h"
int IRPin = 2;

int timeSinceChange = 0;
IRrecvPCI myReceiver(IRPin);  //create receiver and pass pin number
IRdecode myDecoder;           //create decoder
int IR1 = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);
  while (!Serial)
    ;                       //delay for Leonardo
  myReceiver.enableIRIn();  // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  int val = checkIR(IRPin);
  if (val == 1)
    timeSinceChange = 0;

  if (timeSinceChange < 25)
    IR1 = 1;

  timeSinceChange++;
  displayIR();
  myReceiver.enableIRIn();  //Restart receiver
}

void displayIR(){
  Serial.println(IR1);
}

bool checkIR(int PIN) {
  return myReceiver.getResults();
}
