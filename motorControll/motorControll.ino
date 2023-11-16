const int pwm[] = {9, 12, 11, 10};   //right up and clockwise
const int in_1[] = {30, 37, 35, 32};
const int in_2[] = {31, 36, 34, 33};
#define NUM_MOTORS 4

void setup() {  

  Serial.begin(9600);
  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(pwm[i], OUTPUT);   //we have to set PWM pin as output
    pinMode(in_1[i], OUTPUT);  //Logic pins are also set as output
    pinMode(in_2[i], OUTPUT);
  }

  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}

int a = 0;
int b = NUM_MOTORS;

void loop() {
  //For Clock wise motion , in_1 = High , in_2 = Low
  Serial.println("YEs");
  for (int i=a; i < b; i++){
    digitalWrite(in_1[i], HIGH);
    digitalWrite(in_2[i], LOW);
    analogWrite(pwm[i], 100);    
  } 

  delay(1000);

  Serial.println("Neit!");
  for (int i=a; i < b; i++){
    digitalWrite(in_1[i], LOW);
    digitalWrite(in_2[i], HIGH);
  } 

  delay(1000);

  /*setting pwm of the motor to 100v7
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */
}