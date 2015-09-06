//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"

#define AGGRESSIVE_Kp 50
#define AGGRESSIVE_Ki 20
#define AGGRESSIVE_Kd 0.3

#define MODERATE_Kp 7
#define MODERATE_Ki 0.012
#define MODERATE_Kd 0.021

#define CONSERVATIVE_Kp 5
#define CONSERVATIVE_Ki 0.01
#define CONSERVATIVE_Kd 0.02

#pragma mark - Constructor

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;
    _pidTuningState = LPIDTuningStateNone;
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(LObstacleDistances obstacleDistances) {
    double pidOutput = pidOutputForObstacleDistances(obstacleDistances);
    return wallFollowWheelSpeedsForPIDOutput(pidOutput);
}

bool LWallFollowController::leftFollow(LObstacleDistances obstacleDistances) {
    return obstacleDistances.leftMinDistance() < obstacleDistances.rightMinDistance();
}

double LWallFollowController::pidOutputForObstacleDistances(LObstacleDistances obstacleDistances) {
    bool followLeft = leftFollow(obstacleDistances);
    double minimumDistance;
    
    if (obstacleDistances.isObstacleFront()) {
        updatePIDTunings(LPIDTuningStateAggressive);
        minimumDistance = obstacleDistances.minDistance();
    }
    else if (!obstacleDistances.isObstacleOnTheSide()) {
        updatePIDTunings(LPIDTuningStateModerate);
        minimumDistance = obstacleDistances.minDistance();
    }
    else {
        updatePIDTunings(LPIDTuningStateConservative);
        minimumDistance = followLeft ? obstacleDistances.leftSideDistance() : obstacleDistances.rightSideDistance();
    }
    
    _wallFollowPID->SetControllerDirection(followLeft ? DIRECT : REVERSE);
    _wallFollowPID->setInput(minimumDistance);
    _wallFollowPID->Compute();

    return _wallFollowPID->output();
}

void LWallFollowController::updatePIDTunings(LPIDTuningState state) {
    if (state == _pidTuningState) return;

    resetPIDTuning();

    switch (state) {
        case LPIDTuningStateConservative:
            _wallFollowPID->SetTunings(CONSERVATIVE_Kp, CONSERVATIVE_Ki, CONSERVATIVE_Kd);
            break;
        case LPIDTuningStateModerate:
            _wallFollowPID->SetTunings(MODERATE_Kp, MODERATE_Ki, MODERATE_Kd);
            break;
        case LPIDTuningStateAggressive:
            _wallFollowPID->SetTunings(AGGRESSIVE_Kp, AGGRESSIVE_Ki, AGGRESSIVE_Kd);
            break;
        case LPIDTuningStateNone:
            _wallFollowPID->SetTunings(0, 0, 0);
            break;
    }
    
    _pidTuningState = state;
}

void LWallFollowController::resetWallFollowParameters() {
    _pidTuningState = LPIDTuningStateNone;
}

void LWallFollowController::resetPIDTuning() {
    _wallFollowPID->SetOutputLimits(0, 0.00001);
    double maxWheelSpeed = 255;
    _wallFollowPID->SetOutputLimits(-2*maxWheelSpeed, 2*maxWheelSpeed);
}

LWheelSpeeds LWallFollowController::wallFollowWheelSpeedsForPIDOutput(double pidOutput) {
    int leftWheelSpeed = 255;
    int rightWheelSpeed = 255;
    
    if (pidOutput > 0) {
        //turn right
        rightWheelSpeed -= pidOutput;
    }
    else {
        //turn left
        leftWheelSpeed += pidOutput;
    }
    
    return {leftWheelSpeed, rightWheelSpeed};
}

#pragma mark -
