#include <Arduino.h>
#include "Enes100.h"     // ONLY here
#include "config.h"
#include "vision.h"

// Check ENES100 connection
bool ENES100isconnected() { 
  return Enes100.isConnected(); }
// Check communication state
int ENES100state() {
  return Enes100.state(); }
  // Initialize ENES100 for Arduino Uno R4 Wifi
void visionBegin() {
  Enes100.begin(TEAM_NAME, FIRE, MARKER_ID, ROOM); //For Arduino Uno R4: team name, mission, room num, aruco id) 
  Enes100.println("Starting Jersey Mikes Vision System...");}
// Check if Aruco Marker is visible
void waitforVisible() {
  while (!Enes100.isVisible()) {
    delay(100); // Wait until the ArUco marker is visible
  }
  // Check if the marker is visible
  if (Enes100.isVisible()) {
    Enes100.println("ArUco marker detected! Jersey Mikes is visible.");
  }
}
// Print message to ENES100 serial monitor
void visionPrint(const char* msg) {
  Enes100.println(msg);
}
