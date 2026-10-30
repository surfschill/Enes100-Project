#include <Arduino.h>
#include "config.h"
#include "vision.h"
#include "motors.h"
#include "navigation.h"  // if it calls turnTo() etc.
#include "mission.h"     // (or obstacles.h / goal.h — its own header last)