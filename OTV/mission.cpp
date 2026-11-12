#include <Arduino.h>
#include "config.h"
#include "vision.h"
#include "motors.h"
#include "navigation.h"  // if it calls turnTo() etc.
#include "mission.h"     // (or obstacles.h / goal.h — its own header last)


void gotoMissionA(){
x = 0.5;
y = 1.5;

}
void gotoMissionB(){
MissionB_X = 0.5;
MissionB_Y = 0.5;
float Angle = atan2(MissionB_Y - getY(), MissionB_X - getX());
turnToAngle(Angle);
}
void goToMission(){
    //... code to go to the mission location
   
}

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
Topography matchTopography(int b1, int b2, int b3) {
    // HIGH = 1, LOW = 0
  if (b1 == HIGH && b2 == HIGH && b3 == LOW)  return TOP_A;
  if (b1 == HIGH && b2 == LOW  && b3 == LOW)  return TOP_B;
  if (b1 == HIGH && b2 == HIGH && b3 == HIGH) return TOP_C;
  return TOP_UNKNOWN;
}
// reads the button pin values and returns results to matchtopography function
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

void doMission(){
    //... code to do the mission
}
