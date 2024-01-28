int in1 = 28;
int in2 = 29;
int pwm = 4;
const int dribblerPower = 50;
void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pwm, OUTPUT);
  analogWrite(pwm, 0);
  digitalWrite(22, HIGH);
}


void Drip(bool direc, bool state = HIGH) {
  digitalWrite(in1, direc);
  digitalWrite(in2, !direc);
  if (state) {
    analogWrite(pwm, dribblerPower);
  } else {
    analogWrite(pwm, 0);
  }
}



void loop() {
  Drip(HIGH);
  delay(10);
}
