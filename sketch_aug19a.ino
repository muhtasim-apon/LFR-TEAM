#include<Arduino.h>
//setting up pin numbers for the output pin
int ENA=10;//for enabling the speed of left wheel
int IN1=8;//setting pin 8 for left wheel direction 1
int IN2=9;//setting pin 9 for left wheel direction 2
int ENB=13;//for the right wheel
int IN3=11;//for the right two wheels
int IN4=12;//same for right wheels
void setup() {
  //for setting output pins
  pinMode(ENA,OUTPUT);//setting pin 10 as output for aurdino as ena
  pinMode(IN1,OUTPUT);//similar for all of these aurdino these pins are now outputs btw
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  //now a default spped spetting
  analogWrite(ENA,200);//both motor ow 200 pwm speed
  analogWrite(ENB,200);
}

void loop() {
  //for rotating in speed=direction 
  //high -supplies 5v to the l298 motor pins btw and low 0 v
  //case 1 -> moving forward
  digitalWrite(IN1,HIGH);//all  1 0 like combo move forward
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(2000);//it will stop for 2 second and then execute the next code

  //Case-2 -> for moving backward
  digitalWrite(IN1,LOW);//all  0 1 like combo move forward
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(2000);

  //Case-3 -> for turning left
  digitalWrite(IN1,LOW);//Left will completely stop right wheel only move forward
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(2000);//it will stop for 2 second and then execute the next code

  //Case-4->for turning right
  digitalWrite(IN1,HIGH);//Right will completely stop left wheel only move forward
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(2000);

  //Case-5-> stopping the all motors
  digitalWrite(IN1,LOW);//all  0 0 like combo move forward
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(2000);

}
