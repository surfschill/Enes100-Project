#include <Arduino.h>
#include "motors.h"




void setMotors(int leftSpeed, int rightSpeed) {
  // Set the speed of the left and right motors
  analogWrite(LEFT_MOTOR_PIN, leftSpeed);
  analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
}

void StopMotors() {
  // Stop both motors
  setMotors(0, 0);
}

void turnRight(int speed) {
  // Turn the robot right by setting the left motor forward and the right motor backward
  setMotors(speed, -speed);
}

void turnLeft(int speed) {
  // Turn the robot left by setting the left motor backward and the right motor forward
  setMotors(-speed, speed);
}