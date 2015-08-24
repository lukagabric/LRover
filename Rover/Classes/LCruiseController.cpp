//
//  LCruiseController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LCruiseController.h"
#include <algorithm>

#pragma mark - Constructor

LCruiseController::LCruiseController(LPID *cruisePID) {
    _cruisePID = cruisePID;
}

#pragma mark - Output

LWheelSpeeds LCruiseController::cruiseOutput(LGeoLocation currentLocation, LGeoLocation goalLocation, double currentHeadingDeg) {
    if (!currentLocation.isValid()) return {0, 0};
    
    double offsetDeg;
    if (hasLocationChanged(currentLocation)) {
        offsetDeg = headingOffsetDeg(currentLocation, goalLocation, currentHeadingDeg);
    }
    else {
        offsetDeg = _lastHeadingOffsetDeg;
    }
    
    double pidOutput = pidOutputForHeadingOffsetDeg(offsetDeg);
    
    return cruiseWheelSpeedsForPIDOutput(pidOutput);
}

bool LCruiseController::hasLocationChanged(LGeoLocation currentLocation) {
    bool hasLocationChanged = !currentLocation.isEqualTo(_lastLocation);
    _lastLocation = currentLocation;
    return hasLocationChanged;
}

double LCruiseController::headingOffsetDeg(LGeoLocation currentLocation, LGeoLocation goalLocation, double currentHeadingDeg) {
    double goalHeadingDeg = currentLocation.headingDegTo(goalLocation);

    double headingOffsetDeg = goalHeadingDeg - currentHeadingDeg;
    
    if (headingOffsetDeg < -180) {
        headingOffsetDeg += 360;
    }
    else if (headingOffsetDeg > 180) {
        headingOffsetDeg -= 360;
    }
    
    return headingOffsetDeg;
}

double LCruiseController::pidOutputForHeadingOffsetDeg(double headingOffsetDeg) {
    _cruisePID->setInput(headingOffsetDeg);
    _cruisePID->Compute();
    return _cruisePID->output();
}

LWheelSpeeds LCruiseController::cruiseWheelSpeedsForPIDOutput(double pidOutput) {
    int leftWheelSpeed = 255;
    int rightWheelSpeed = 255;
    
    if (pidOutput > 0) {
        //turn left
        leftWheelSpeed -= pidOutput;
        leftWheelSpeed = std::max(minimumForwardWheelSpeed, leftWheelSpeed);
    }
    else {
        //turn right
        rightWheelSpeed += pidOutput;
        rightWheelSpeed = std::max(minimumForwardWheelSpeed, rightWheelSpeed);
    }
    
    return {leftWheelSpeed, rightWheelSpeed};
}

#pragma mark -
