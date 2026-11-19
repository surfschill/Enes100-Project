#include <Arduino.h>
#include "config.h"
#include "vision.h"      // for getX(), getY(), getTheta(), isVisible()
#include "motors.h"      // for setMotors(), stopMotors()
#include "navigation.h"

// Retrieve OTV coordinates
void getCoordinates(float &x, float &y, float &theta) {
  x = Enes100.getX();
  y = Enes100.getY();
  theta = Enes100.getTheta(); }

void turnToAngle(float targetAngle) {
float turnAngle = targetAngle - getTheta();

}

void driveToY(float targetY) {
    setMotors(100, 100); // Set motors to move forward at speed 100S
    if (getY() >= targetY) {
        stopMotors(); // Stop motors when target Y is reached
    }
}

void driveToX(float targetX) {
    setMotors(100, 100); // Set motors to move forward at speed 100
    if (getX() >= targetX) {
        stopMotors(); // Stop motors when target X is reached
    }
}