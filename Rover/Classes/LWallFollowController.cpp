//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"

#define FRONT_Kp 50
#define FRONT_Ki 20
#define FRONT_Kd 0.3

#define SIDE_Kp 5
#define SIDE_Ki 0.01
#define SIDE_Kd 0.02

#pragma mark - Constructor

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(LObstacleDistances obstacleDistances) {
    double pidOutput = pidOutputForObstacleDistances(obstacleDistances);
    return wallFollowWheelSpeedsForPIDOutput(pidOutput);
}

double LWallFollowController::pidOutputForObstacleDistances(LObstacleDistances obstacleDistances) {
    bool leftFollow = obstacleDistances.leftMinDistance() < obstacleDistances.rightMinDistance();
    double minimumDistance = obstacleDistances.minDistance();
    
    if (obstacleDistances.isObstacleFront() || !obstacleDistances.isObstacleOnTheSide()) {
        updatePIDTunings(FRONT_Kp, FRONT_Ki, FRONT_Kd);
    }
    else {
        updatePIDTunings(SIDE_Kp, SIDE_Ki, SIDE_Kd);
    }
    
    _wallFollowPID->SetControllerDirection(leftFollow ? DIRECT : REVERSE);
    _wallFollowPID->setInput(minimumDistance);
    _wallFollowPID->Compute();
    
    return _wallFollowPID->output();
}

void LWallFollowController::updatePIDTunings(double Kp, double Ki, double Kd) {
    if (_wallFollowPID->GetKp() == Kp && _wallFollowPID->GetKi() == Ki && _wallFollowPID->GetKd() == Kd) return;
    _wallFollowPID->SetTunings(Kp, Ki, Kd);
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
