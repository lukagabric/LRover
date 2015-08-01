#include "RoverWallFollower.h"
#include "RoverNavigator.h"

RoverNavigator rover;

void setup() {
    rover.setup();
}

void loop() {
    rover.loop();
}
