#include <Arduino.h>
#include "config.h"
#include "vision.h"      
#include "motors.h"      
#include "mission.h"

//  settings for getting to the mission site 
const int   TURN_SPEED       = 180;  // turning when far from the target angle
const int   TURN_SLOW        = 120;   // turning when close (less overshoot)
const int   DRIVE_SPEED      = 200;
const float MISSION_A_STOP_Y = 1.2;  // stop here when driving up to A
const float MISSION_B_STOP_Y = 0.8;  // stop here when driving down to B


// Stop the motors and wait until the vision system can see the marker.
static void waitForVisible() {
  while (!isVisible()) {
    stopMotors();
    delay(50);
  }
}

// Spin in place. Clockwise = left forward, right back.
static void spinClockwise(int speed)        { setMotors(speed, -speed); }
static void spinCounterClockwise(int speed) { setMotors(-speed, speed); }


// Turn until facing DOWN (between -1.65 and -1.49), toward B.
static void turnToFaceB() {
  while (true) {
    waitForVisible();
    float t = getTheta();
    if (t > -1.65 && t < -1.49) break;            // facing down: done

    int speed = TURN_SPEED;
    if (t > -2.0 && t < -1.15) speed = TURN_SLOW; // close: slow down

    if (t > -1.57 && t < 1.57) spinClockwise(speed);         // right half
    else                       spinCounterClockwise(speed);  // left half
    delay(20);
  }
  stopMotors();
}

// Turn until facing UP (between 1.49 and 1.65), toward A.
static void turnToFaceA() {
  while (true) {
    waitForVisible();
    float t = getTheta();
    if (t > 1.49 && t < 1.65) break;              // facing up: done

    int speed = TURN_SPEED;
    if (t > 1.15 && t < 2.0) speed = TURN_SLOW;   // close: slow down

    if (t > -1.57 && t < 1.57) spinCounterClockwise(speed);  // right half
    else                       spinClockwise(speed);         // left half
    delay(20);
  }
  stopMotors();
}


// Drive forward until y drops to stopY (driving down toward B).
static void driveDownTo(float stopY) {
  while (true) {
    waitForVisible();
    if (getY() <= stopY) break;
    setMotors(DRIVE_SPEED, DRIVE_SPEED);
    delay(20);
  }
  stopMotors();
}

// Drive forward until y rises to stopY (driving up toward A).
static void driveUpTo(float stopY) {
  while (true) {
    waitForVisible();
    if (getY() >= stopY) break;
    setMotors(DRIVE_SPEED, DRIVE_SPEED);
    delay(20);
  }
  stopMotors();
}

//  mission navigation 

// Started at B we go up to A.
void goToMissionA() {
  visionPrint("Going to A");
  turnToFaceA();
  driveUpTo(MISSION_A_STOP_Y);
}

// Started at A we go down to B.
void goToMissionB() {
  visionPrint("Going to B");
  turnToFaceB();
  driveDownTo(MISSION_B_STOP_Y);
}

// Pick the site on the opposite side from where we start.
void goToMission() {
  waitForVisible();

  if (getY() > 1.0) {
    goToMissionB();     // started at A
  } else {
    goToMissionA();     // started at B
  }

  visionPrint("At mission site");
}

//mission tasks 

void countCandles() {
  // ... code to count candles
}

void findTopography() {
  // ... code to find topography
}

void doMission() {
  // ... code to do the mission
}