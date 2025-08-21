#include <Arduino.h>

// Motor driver pins
int ENA = 10; 
int IN1 = 8;
int IN2 = 9;
int ENB = 5; 
int IN3 = 11;
int IN4 = 12;

// IR sensor pins
int LEFT = 2;
int MIDLEFT = 3;
int MIDRIGHT = 4;
int RIGHT = 6;

//for base speed and proportional gain here 
int mainSpeed = 200;
float Kp=50.0;//for error handling

void setup() {
  // Motor pins as output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensor pins as input
  pinMode(LEFT, INPUT);
  pinMode(MIDLEFT, INPUT);
  pinMode(MIDRIGHT, INPUT);
  pinMode(RIGHT, INPUT);

  // initialize motor speed
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Motor control function
void move(int leftSpeed, int rightSpeed) {
  // Left motor
  if(leftSpeed >= 0){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
  } else {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    leftSpeed = -leftSpeed;
  }

  // Right motor
  if(rightSpeed >= 0){
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  } else {
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    rightSpeed = -rightSpeed;
  }

 // Apply PWM speed
  analogWrite(ENA, constrain(leftSpeed, 0, 255));
  analogWrite(ENB, constrain(rightSpeed, 0, 255));
}

// ---------- Motor Control Functions ----------
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void sharpLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void sharpRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopmotors()
{
  move(0,0);
}

// ---------- Main Loop ----------
void loop() {
  int sensors[4];

  sensors[0] = digitalRead(LEFT);
  sensors[1] = digitalRead(MIDLEFT);
  sensors[2] = digitalRead(MIDRIGHT);
  sensors[3] = digitalRead(RIGHT);
  
  //assigning weight to sensors. weights are the coefficients for calculating the erros
  int weight[4]={-3.-1,1,3};

  //calculating the postioning error for maintaining the perfect drift speed
  int error=0;
  int active=0;
  for(int i=0;i<4;i++)
  {
    if(sensors[i]==LOW) //0 -.means sensor is on line
    {
      error+=weight[i];
      active++;
    }
  }
  
  //now calculating the avg error
  if(active>0)
  {
    error/=active;
  }
  else
  {
    stopmotors();
    return;
  }

  // // Middle sensors → go forward
  // if (midleftVal == LOW && midrightVal == LOW && leftVal == HIGH && rightVal == HIGH) {
  //   forward();
  // }
  // // Slight left correction
  // else if (midleftVal == LOW && midrightVal == HIGH) {
  //   turnLeft();
  // }
  // // Slight right correction
  // else if (midrightVal == LOW && midleftVal == HIGH) {
  //   turnRight();
  // }
  // // Sharp left
  // else if (leftVal == LOW) {
  //   sharpLeft();
  // }
  // // Sharp right
  // else if (rightVal == LOW) {
  //   sharpRight();
  // }
  // // Lost line → stop
  // else {
  //   stopMotors();
  // }

  //now calculating the kip val and proprtional error
  int leftSpeed= mainSpeed- Kp*error;//reducing theinner wheel speed
  int rightSpeed=mainSpeed+Kp*error;//incerasing the outer wheel speed for smooth turns
   
  //for moving motors
  move(leftSpeed,rightSpeed);

}