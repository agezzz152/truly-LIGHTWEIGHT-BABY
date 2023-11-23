const int pwm[] = {9, 12, 11, 10};   //right up and clockwise
const int in_1[] = {30, 37, 35, 32};
const int in_2[] = {31, 36, 34, 33};
#define NUM_MOTORS 4

double motors[4] = {0};
double speedPart;
double speenPart;
double sixtyrad;
double fortfiverad;

//For providing logic to L298 IC to choose the direction of the DC motor

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

void loop() {
  //For Clock wise motion , in_1 = High , in_2 = Low
  moov(0, 150, 0);
  delay(100);

}


void moov(double angle, double sped, double speen){ //angle in a number betwin 0 and 2pi, sped in a number betwin 0 and 255, and speen is a number betwin 0 and 255
  int i;
  
  angle = angle /(180) * (3.141592653589793);
  if (!(sped == 0) || !(speen == 0)){
   
    for (i = 0 ; i < 4; i++) {
      motors[i] = 0;
    }
    //double motors[4] = {0, 0, 0, 0};// the order of the motors is left right up down

    speedPart = (abs(sped))/(abs(sped) + abs(speen));
    speenPart = 1- speedPart;
 
    //adding the reguler forward, beckward, left, right movment
    // sixtyrad = 1.0472;
    // fortfiverad = 0.785398;
    sixtyrad = 1.0472;
    fortfiverad = 0.785398;
    motors[0] = -sin(fortfiverad - angle) * sped * speedPart; //right front 
    motors[1] = -sin(fortfiverad + angle) * sped * speedPart; //right back
    motors[2] = sin(fortfiverad-angle) * sped * speedPart; //left back
    motors[3] = (sin(fortfiverad + angle) * sped * speedPart); //left front
 

    // adding the circular motion for the motors
    for (i = 0; i<4; i++){
      motors[i] = motors[i] + (speen * speenPart);
      
      if (motors[i] > 250){
        motors[i] = 250;
      }
      if (motors[i] < -250) {
        
        motors[i] = -250;
      }
      analogWrite(pwm[i], abs(motors[i])); 

      digitalWrite(in_1[i], (signOFx(motors[i]) + 1) / 2);
      digitalWrite(in_2[i], 1 - ((signOFx(motors[i]) + 1) / 2));
    }

    
  }
}

double signOFx(double x){
  return x / abs(x);
}

