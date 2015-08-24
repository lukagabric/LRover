//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"
#include <algorithm>

#pragma mark - Constructor

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance) {
    _frontDistance = frontDistance;
    _frontLeftDistance = frontLeftDistance;
    _frontRightDistance = frontRightDistance;
    _leftDistance = leftDistance;
    _rightDistance = rightDistance;

    double leftMinimumDistance = leftMinDistance();
    double rightMinimumDistance = rightMinDistance();
    bool leftFollow = leftMinimumDistance < rightMinimumDistance;
    double distance = leftFollow ? leftMinimumDistance : rightMinimumDistance;
    
    _wallFollowPID->SetControllerDirection(leftFollow ? DIRECT : REVERSE);
    _wallFollowPID->setInput(distance);
    _wallFollowPID->Compute();
    
    return {0, 0};
}

#pragma mark - Obstacle Proximity

bool LWallFollowController::isObstacleTooClose() {
    return isObstacleFront() || isObstacleFrontRight() || isObstacleFrontLeft() || isObstacleRight() || isObstacleLeft();
}

double LWallFollowController::rightMinDistance() {
    return std::min(_frontRightDistance, _rightDistance);
}

double LWallFollowController::leftMinDistance() {
    return std::min(_frontLeftDistance, _leftDistance);
}

#pragma mark - Each Distance

bool LWallFollowController::isObstacleFront() {
    return _frontDistance < _wallFollowPID->setpoint();
}

bool LWallFollowController::isObstacleFrontRight() {
    return _frontRightDistance < _wallFollowPID->setpoint();
}

bool LWallFollowController::isObstacleFrontLeft() {
    return _frontLeftDistance < _wallFollowPID->setpoint();
}

bool LWallFollowController::isObstacleRight() {
    return _rightDistance < _wallFollowPID->setpoint();
}

bool LWallFollowController::isObstacleLeft() {
    return _leftDistance < _wallFollowPID->setpoint();
}

#pragma mark - Specific Distances

bool LWallFollowController::isObstacleOnTheLeftSide() {
    return isObstacleFrontLeft() || isObstacleLeft();
}

bool LWallFollowController::isObstacleOnTheRightSide() {
    return isObstacleFrontRight() || isObstacleRight();
}

#pragma mark -
