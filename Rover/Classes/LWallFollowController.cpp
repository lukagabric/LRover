//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"

#pragma mark - Constructor

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(LObstacleDistances obstacleDistances) {
    double leftMinimumDistance = obstacleDistances.leftMinDistance();
    double rightMinimumDistance = obstacleDistances.rightMinDistance();
    bool frontObstacle = obstacleDistances.isObstacleFront();
    bool leftFollow = leftMinimumDistance < rightMinimumDistance;
    double distance = leftFollow ? leftMinimumDistance : rightMinimumDistance;
    
    double maxWheelSpeed = 255;
    
    _wallFollowPID->SetControllerDirection(leftFollow ? REVERSE : DIRECT);
    _wallFollowPID->SetOutputLimits(-2*maxWheelSpeed, 2*maxWheelSpeed);
    _wallFollowPID->setInput(distance);
    _wallFollowPID->Compute();
    
    return {0, 0};
}

double LWallFollowController::pidOutputForObstacleDistances(LObstacleDistances obstacleDistances) {
    _wallFollowPID->setInput(obstacleDistances.leftMinDistance());
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
