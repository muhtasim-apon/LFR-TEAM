#include <Arduino.h>
//now its time to add mainly the smotth curve spped controls 
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

//for the base spped 
int mainSpeed=200;
int turnSpeed=150;//for the inner wheeel smooth turning

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

  // Default motor speed
  analogWrite(ENA, 0);//coz we dont know whether it will tirn or go smooth btw
  analogWrite(ENB, 0);
}

//controlling motor functions with dynamic spped turns 
void move(int leftSpeed, int rightSpeed)
{
  if(leftSpeed>=0)
  {
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
  }
  else{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    leftSpeed=-leftSpeed;
  }
  // Right motor
  if (rightSpeed >= 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    rightSpeed = -rightSpeed;
  }
  analogWrite(ENA,constrain(leftSpeed,0,255));
  analogWrite(ENB,constrain(rightSpeed,0,255));
}

// ---------- Motor Control Functions ----------
//for forward dynamic forward movements
void forward() {
  move(mainSpeed,mainSpeed);
}

void turnLeft() {
  move(turnSpeed,mainSpeed);//slow left, fast right
}

void turnRight() {
  move(mainSpeed,turnSpeed); //fast left, slow right
}

void stopMotors() {
  move(0,0);
}

void sharpLeft() {
  move(0,mainSpeed); //stop left, full right
}

void sharpRight() {
  move(mainSpeed,0); //full left,stop right
}

// ---------- Main Loop ----------
void loop() {
  int leftVal = digitalRead(LEFT);
  int midleftVal = digitalRead(MIDLEFT);
  int midrightVal = digitalRead(MIDRIGHT);
  int rightVal = digitalRead(RIGHT);

  // Middle sensors → go forward
  if (midleftVal == LOW && midrightVal == LOW && leftVal == HIGH && rightVal == HIGH) {
    forward();
  }
  // Slight left correction
  else if (midleftVal == LOW && midrightVal == HIGH) {
    turnLeft();
  }
  // Slight right correction
  else if (midrightVal == LOW && midleftVal == HIGH) {
    turnRight();
  }
  // Sharp left
  else if (leftVal == LOW) {
    sharpLeft();
  }
  // Sharp right
  else if (rightVal == LOW) {
    sharpRight();
  }
  // Lost line → stop
  else {
    stopMotors();
  }
}