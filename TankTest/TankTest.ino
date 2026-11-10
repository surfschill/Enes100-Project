#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"

int done = 0;

void goToMission() {
  // Wait until the vision system sees the marker
  while (!Enes100.isVisible()) {
    delay(50);
  }

  float y = Enes100.getY();

  if (y > 1.0) {
    // Started at A -> face down (-1.57), then drive down to B
    Enes100.println("Going to B");

    while (!(Enes100.getTheta() > -1.65 && Enes100.getTheta() < -1.49)) {
      float t = Enes100.getTheta();

      int speed = 140;
      if (t > -2.0 && t < -1.15) {
      speed = 90;
      }

      if (t > -1.57 && t < 1.57) {
        Tank.setLeftMotorPWM(speed);      // right half: turn clockwise
        Tank.setRightMotorPWM(-speed);
      } else {
        Tank.setLeftMotorPWM(-speed);     // left half: turn counter-clockwise
        Tank.setRightMotorPWM(speed);
      }
      delay(20);
    }
    Tank.turnOffMotors();

    while (Enes100.getY() > 0.8) {      // drive down, stop before B
      Tank.setLeftMotorPWM(200);
      Tank.setRightMotorPWM(200);
      delay(20);
    }
    Tank.turnOffMotors();

  } else {
    // Started at B -> face up (1.57), then drive up to A
    Enes100.println("Going to A");

    while (!(Enes100.getTheta() > 1.49 && Enes100.getTheta() < 1.65)) {
      float t = Enes100.getTheta();
      if (t > -1.57 && t < 1.57) {
        Tank.setLeftMotorPWM(-180);     // right half: turn counter-clockwise
        Tank.setRightMotorPWM(180);
      } else {
        Tank.setLeftMotorPWM(180);      // left half: turn clockwise
        Tank.setRightMotorPWM(-180);
      }
      delay(20);
    }
    Tank.turnOffMotors();

    while (Enes100.getY() < 1.2) {      // drive up, stop before A
      Tank.setLeftMotorPWM(200);
      Tank.setRightMotorPWM(200);
      delay(20);
    }
    Tank.turnOffMotors();
  }

  Enes100.println("At mission site");
}

void setup() {
  Tank.begin();
  Enes100.begin("Jersey Mikes", FIRE, 50, 1116, 52, 50);
  Enes100.println("Connected");
}

void loop() {
  if (done == 0) {
    delay(1000);
    goToMission();
    done = 1;
  }
}