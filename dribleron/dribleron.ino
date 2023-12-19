int in1 = 30;
int in2 = 31;
int pwm = 9;
const int dribblerPower = 100;
void setup() {
 Serial.begin(9600);
 pinMode(in1 , OUTPUT);
 pinMode(in2 , OUTPUT);
 pinMode(pwm, OUTPUT);
 digitalWrite(in1, 0);
 digitalWrite(in2, 0);
 analogWrite(pwm, 0);
 digitalWrite(40 , HIGH);
}

void loop() {
  Dribbleron(HIGH);
  delay(2000);
}

void Dribbleron(bool state) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  if (state) {
    analogWrite(pwm, dribblerPower);
  }
  else {
    analogWrite(pwm, 0);
  }
}
