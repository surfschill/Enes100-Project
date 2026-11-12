#include "vision.h"
#include "motors.h"
#include "navigation.h"
#include "mission.h"
#include "obstacles.h"
#include "goal.h"


void setup() {
    
setupMotors();      // ← missing: set the motor pins as outputs FIRST
  stopMotors();
  visionBegin();
  visionPrint("Setup done");
  delay(2000);

  goToMission();
  stopMotors();
  visionPrint("Finished");
}



void loop() {

    
}

