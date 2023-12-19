int in1 = 30;
int in2 = 31;
int pwm = 9;
const int dribblerPower = 100;
void setup() {
 Serial.begin(9600);
 pinMode(in1 , OUTPUT);
 pinMode(in2 , OUTPUT);
 pinMode(pwm, OUTPUT);
 analogWrite(pwm, 0);
 digitalWrite(40 , HIGH);
}


void Drip(bool direc, bool state = HIGH) {
  digitalWrite(in1, direc);
  digitalWrite(in2, !direc);
  if (state) {
    analogWrite(pwm, dribblerPower);
  }
  else {
    analogWrite(pwm, 0);
  }
}



void loop() {
  Drip(HIGH);
  delay(2000);
}
