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
