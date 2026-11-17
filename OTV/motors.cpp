#include "Arduino.h"
#include "Enes100.h"
#include "motors.h"

const int LEFT_EN   = 9;      // ENB  (PWM ~9)
const int LEFT_IN1  = 10;     // IN3
const int LEFT_IN2  = 11;     // IN4

const int RIGHT_EN  = 6;      
const int RIGHT_IN1 = 8;      
const int RIGHT_IN2 = 7;

void setupMotors() {
  pinMode(LEFT_EN, OUTPUT);  pinMode(LEFT_IN1, OUTPUT);  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT); pinMode(RIGHT_IN1, OUTPUT); pinMode(RIGHT_IN2, OUTPUT);
}

void setMotors(int left, int right) {
  if (left >= 0) { digitalWrite(LEFT_IN1, HIGH); digitalWrite(LEFT_IN2, LOW); }
  else           { digitalWrite(LEFT_IN1, LOW);  digitalWrite(LEFT_IN2, HIGH); }
  analogWrite(LEFT_EN, constrain(abs(left), 0, 255));

  if (right >= 0) { digitalWrite(RIGHT_IN1, HIGH); digitalWrite(RIGHT_IN2, LOW); }
  else            { digitalWrite(RIGHT_IN1, LOW);  digitalWrite(RIGHT_IN2, HIGH); }
  analogWrite(RIGHT_EN, constrain(abs(right), 0, 255));
}

void stopMotors() {
  setMotors(0, 0);
}