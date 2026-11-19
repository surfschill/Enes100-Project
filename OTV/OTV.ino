#include <Arduino.h>
#include <Enes100.h>
#include "config.h"
#include "vision.h"
#include "motors.h"
#include "navigation.h"
#include "mission.h"

// Prevent the mission from running multiple times
bool missionComplete = false; // change to true when the mission is complete

void setup() {
   setMotors(); // sets up the motors
   visionBegin(); // turns on the ENES100 vision system
   StopMotors();
}



void loop() {
      if (missionComplete) {
    stopMotors();
    return; 
}
getCoordinates(float &x, float &y, float &theta);  // get the current coordinates of the OTV
goToMission();

  int candles = countCandles();

  Topography topography = detectTopography();

  sendMissionResults(candles, topography);

  doMission();

  stopMotors();



  missionComplete = true;
}
  
