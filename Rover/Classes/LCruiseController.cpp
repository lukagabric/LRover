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
    
    double maxWheelSpeed = 255;
    _cruisePID->setDefaultOutputLimits(-maxWheelSpeed, maxWheelSpeed);
}

#pragma mark - Output

LWheelSpeeds LCruiseController::cruiseOutput(double headingOffsetDeg) {
    double pidOutput = pidOutputForHeadingOffsetDeg(headingOffsetDeg);
    return cruiseWheelSpeedsForPIDOutput(pidOutput);
}

void LCruiseController::resetCruiseParameters() {
    _cruisePID->resetOutput();
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
