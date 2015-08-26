//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"

#define FRONT_Kp 24
#define FRONT_Ki 10
#define FRONT_Kd 0.3

#define SIDE_Kp 15
#define SIDE_Ki 0.2
#define SIDE_Kd 0.12

#pragma mark - Constructor

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;

    double maxWheelSpeed = 255;
    _wallFollowPID->SetOutputLimits(-2*maxWheelSpeed, 2*maxWheelSpeed);
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(LObstacleDistances obstacleDistances) {
    double pidOutput = pidOutputForObstacleDistances(obstacleDistances);
    return wallFollowWheelSpeedsForPIDOutput(pidOutput);
}

double LWallFollowController::pidOutputForObstacleDistances(LObstacleDistances obstacleDistances) {
    bool leftFollow = obstacleDistances.leftMinDistance() < obstacleDistances.rightMinDistance();
    double minimumDistance = obstacleDistances.minDistance();
    
    if (obstacleDistances.isObstacleFront()) {
        _wallFollowPID->SetTunings(FRONT_Kp, FRONT_Ki, FRONT_Kd);
    }
    else {
        _wallFollowPID->SetTunings(SIDE_Kp, SIDE_Ki, SIDE_Kd);
    }
        
    _wallFollowPID->SetControllerDirection(leftFollow ? DIRECT : REVERSE);
    _wallFollowPID->setInput(minimumDistance);
    _wallFollowPID->Compute();

    return _wallFollowPID->output();
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
