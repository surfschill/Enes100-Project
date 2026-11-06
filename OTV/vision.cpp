#include <Arduino.h>
#include "Enes100.h"     // ONLY here
#include "config.h"
#include "vision.h"

// Check ENES100 connection
bool ENES100isconnected() { 
  return Enes100.isConnected(); }
// Check communication state
BYTE ENES100state() {
  return Enes100.state(); }
  // Initialize ENES100 for Arduino Uno R4 Wifi
void vision.begin() {
  Enes100.begin("Jersey Mikes", FIRE, 137, 1201); //For Arduino Uno R4: team name, mission, room num, aruco id) 
  Enes100.println("Starting ENES100 Vision System...");}
// Check if Aruco Marker is visible
bool isVisible() { 
  return Enes100.isVisible(); }
// Retrieve OTV coordinates
float getX()      { return Enes100.getX(); }
float getY()      { return Enes100.getY(); }
float getTheta()  { return Enes100.getTheta(); }
// Print message to ENES100 serial monitor
void visionPrint(const char* msg) {
  Enes100.println(msg);
}
// Assign values to the three buttons to detect topography
int detectTopography() {
  //... code to detect topography
  int button1 = digitalRead(BUTTON1);
  int button2 = digitalRead(BUTTON2);
  int button3 = digitalRead(BUTTON3);
// TOP_A = 1, 1, 0
  if (button1 == 1 && button2 == 1 && button3 == 0) {
    return 0; // Topography A
  }
  // TOP_B = 1, 0, 0
  else if (button1 == 1 && button2 == 0 && button3 == 0) {
    return 1; // Topography B
  }
  // TOP_C = 1, 1, 1
  else if (button1 == 1 && button2 == 1 && button3 == 1) {
    return 2; // Topography C
  }
  // Unknown topography
  else {
    return -1; 
  }
}
// Report mission results
void sendMissionResults(int candles, int topography) {
  Enes100.mission(NUM_CANDLES, candles);
  if (topography == 0) Enes100.mission(TOPOGRAPHY, TOP_A);
  else if (topography == 1) Enes100.mission(TOPOGRAPHY, TOP_B);
  else Enes100.mission(TOPOGRAPHY, TOP_C);
}