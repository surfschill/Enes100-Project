#ifndef VISION_H
#define VISION_H
#include <Arduino.h>

//This vision.h files tells the other Arduino files which vision funcs are available

//Connection functions
bool ENES100isconnected();
BYTE ENES100state();
// Initialization
void  visionBegin();

// Visibility
bool  isVisible();
// Coordinate Acquisition
float getX();
float getY();
float getTheta();
// Communication
void  visionPrint(const char* msg);
//Mision Results
void  sendMissionResults(int candles, int topography);  

#endif