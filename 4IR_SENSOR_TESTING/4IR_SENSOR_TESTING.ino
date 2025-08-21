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
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
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
