#pragma once

void  visionBegin();
bool  isVisible();
float getX();
float getY();
float getTheta();
void  visionPrint(const char* msg);
void  sendMissionResults(int candles, int topography);  // topography: 0=A, 1=B, 2=C