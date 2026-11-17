#pragma once
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

const char* const TEAM_NAME = "Jersey Mikes"; // must match your ML model name exactly
const int MARKER_ID = 137;                     // number on your ArUco marker 
const int ROOM      = 1201;                   // 1116, 1120, or 1201

// Flame sensors: one per candle position on the fire site.
// Edit this list to match how your sensors are wired.
const int FLAME_PINS[]    = {A0, A1, A2, A3, A4};
const int NUM_FLAME_PINS  = sizeof(FLAME_PINS) / sizeof(FLAME_PINS[0]);
const int FLAME_THRESHOLD = 450;  // lit reads ~40-50, unlit ~850-900 (from tests/ir_sensors.ino)
const int FLAME_SAMPLES   = 10;   // readings averaged per sensor to smooth out flicker





