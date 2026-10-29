#include "Enes100.h"

void setup() {
    
    Enes100.begin("Jersey Mikes", FIRE, 10, 1116);
    float OTV_XPOSITION=Enes100.getX();
    float OTV_YPOSITION=Enes100.getY();
    float OTV_THETA=Enes100.getTheta();
    bool OTV_VISIBILITY=Enes100.isVisible();

    if(OTV_YPOSITION > 1.0){
        goToMissionB (OTV_XPOSITION, OTV_YPOSITION);
    }
    
}


void goToMissionB (float OTV_XPOSITION, float OTV_YPOSITION){

    float MissionB_XPOSITION = 0.5; // Example target X position for Mission B
    float MissionB_YPOSITION = 0.5; // Example target Y position for Mission B
    float DirectionTowardsMissionB = atan2(MissionB_YPOSITION - OTV_YPOSITION, MissionB_XPOSITION - OTV_XPOSITION);
    turnOTV(DirectionTowardsMissionB);

}

void loop() {

    
}

void turnOTV(float DirectionTowardsMissionB){

    while(OTV_THETA != DirectionTowardsMissionB){
        
    }
}