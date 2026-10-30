#include <Arduino.h>
#include "config.h"
#include "vision.h"
#include "motors.h"
#include "navigation.h"  // if it calls turnTo() etc.
#include "mission.h"     // (or obstacles.h / goal.h — its own header last)



void goToMission(){
    //... code to go to the mission location
}

void countCandles(){
    //... code to count candles
}

void findTopography(){
    //... code to find topography
}

void doMission(){
    //... code to do the mission
}