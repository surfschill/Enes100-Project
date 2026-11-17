#include <Arduino.h>
#include <Enes100.h>
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
void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
}


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
// Button pins for topography detection and Flame sensor pins
const int BUTTON1 = 2; // CHANGE TO MATCH BUTTON WIRING
const int BUTTON2 = 3;
const int BUTTON3 = 4;
const int FLAME_PINS[]    = {A0, A1, A2, A3, A4}; //CHANGE TO MATCH FLAME SENSOR WIRING
const int NUM_FLAME_PINS  = sizeof(FLAME_PINS) / sizeof(FLAME_PINS[0]);
const int FLAME_THRESHOLD = 450;  // lit reads ~40-50, unlit ~850-900 (from tests/ir_sensors.ino)
const int FLAME_SAMPLES   = 10;   // readings averaged per sensor to smooth out flicker
// Returns true if the flame sensor on `pin` sees a lit candle.
// Averages several readings so one flicker doesn't change the count.
bool isCandleLit(int pin){
    long total = 0;
    for (int i = 0; i < FLAME_SAMPLES; i++) {
        total += analogRead(pin);
        delay(5);
    }
    int average = total / FLAME_SAMPLES;
    return average < FLAME_THRESHOLD;   // lower reading = flame detected
}

// Returns how many lit candles the flame sensors detect.
int countCandles(){
    int count = 0;
    for (int i = 0; i < NUM_FLAME_PINS; i++) {
        if (isCandleLit(FLAME_PINS[i])) {
            count++;
        }
    }
    return count;
}
// Topography detection functions
// Four diff types: TOP_UNKNOWN, TOP_A, TOP_B, TOP_C
const int TOP_UNKNOWN = -1; //our own "no match" value
Topography matchTopography(int b1, int b2, int b3) {
    // HIGH = 1, LOW = 0
    //returns the library's TOP_A/TOP_B/TOP_C if a match is found, otherwise TOP_UNKNOWN
  if (b1 == HIGH && b2 == HIGH && b3 == LOW)  return TOP_A; // 1,1,0
  if (b1 == HIGH && b2 == LOW  && b3 == LOW)  return TOP_B; // 1,0,0
  if (b1 == HIGH && b2 == HIGH && b3 == HIGH) return TOP_C; // 1,1,1
  return TOP_UNKNOWN;
}
// reads the 3 button values and passes them to matchTopography
Topography detectTopography() {
  int b1 = digitalRead(BUTTON1);
  int b2 = digitalRead(BUTTON2);
  int b3 = digitalRead(BUTTON3);
  return matchTopography(b1, b2, b3);
}
// Reports mission results
void sendMissionResults(int candles, int topography) {
  Enes100.mission(NUM_CANDLES, candles);
  if (topography != TOPO_UNKNOWN) {
    Enes100.mission(TOPOGRAPHY, topography);
  }
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