#include <Arduino.h>
#include "Enes100.h"     // ONLY here
#include "config.h"
#include "vision.h"


void visionBegin() {
  Enes100.begin("TEAM_NAME", FIRE, MARKER_ID, ROOM, WIFI_TX, WIFI_RX);
}

bool  isVisible() { return Enes100.isVisible(); }
float getX()      { return Enes100.getX(); }
float getY()      { return Enes100.getY(); }
float getTheta()  { return Enes100.getTheta(); }
void  visionPrint(const char* msg) { Enes100.println(msg); }

void sendMissionResults(int candles, int topography) {
  Enes100.mission(NUM_CANDLES, candles);
  if (topography == 0) Enes100.mission(TOPOGRAPHY, TOP_A);
  else if (topography == 1) Enes100.mission(TOPOGRAPHY, TOP_B);
  else Enes100.mission(TOPOGRAPHY, TOP_C);
}