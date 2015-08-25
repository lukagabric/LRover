//
//  LObstacleDistances.cpp
//  Rover
//
//  Created by Luka Gabric on 25/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LObstacleDistances.h"
#include <algorithm>


LObstacleDistances::LObstacleDistances() {
    _frontDistance = 999;
    _frontLeftDistance = 999;
    _frontRightDistance = 999;
    _leftDistance = 999;
    _rightDistance = 999;
    obstacleDistanceThreshold = 0;
    obstacleClearDistanceThreshold = 0;
}

LObstacleDistances::LObstacleDistances(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance) {
    _frontDistance = frontDistance;
    _frontLeftDistance = frontLeftDistance;
    _frontRightDistance = frontRightDistance;
    _leftDistance = leftDistance;
    _rightDistance = rightDistance;
    obstacleDistanceThreshold = 30;
    obstacleClearDistanceThreshold = 40;
}

#pragma mark - Obstacle Proximity

bool LObstacleDistances::isObstacleDetected() {
    return isObstacleFront() || isObstacleFrontRight() || isObstacleFrontLeft() || isObstacleRight() || isObstacleLeft();
}

bool LObstacleDistances::isObstacleCleared() {
    return (_frontDistance > obstacleClearDistanceThreshold &&
            _frontLeftDistance > obstacleClearDistanceThreshold &&
            _frontRightDistance > obstacleClearDistanceThreshold &&
            _leftDistance > obstacleClearDistanceThreshold &&
            _rightDistance > obstacleClearDistanceThreshold);
}

#pragma mark - Absolute Values

double LObstacleDistances::frontDistance() {
    return _frontDistance;
}

double LObstacleDistances::frontRightDistance() {
    return _frontRightDistance;
}

double LObstacleDistances::frontLeftDistance() {
    return _frontLeftDistance;
}

double LObstacleDistances::rightDistance() {
    return _rightDistance;
}

double LObstacleDistances::leftDistance() {
    return _leftDistance;
}

double LObstacleDistances::rightMinDistance() {
    return std::min(_frontRightDistance, _rightDistance);
}

double LObstacleDistances::leftMinDistance() {
    return std::min(_frontLeftDistance, _leftDistance);
}

#pragma mark - Each Distance

bool LObstacleDistances::isObstacleFront() {
    return _frontDistance < obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleFrontRight() {
    return _frontRightDistance < obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleFrontLeft() {
    return _frontLeftDistance < obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleRight() {
    return _rightDistance < obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleLeft() {
    return _leftDistance < obstacleDistanceThreshold;
}

#pragma mark - Specific Distances

bool LObstacleDistances::isObstacleOnTheLeftSide() {
    return isObstacleFrontLeft() || isObstacleLeft();
}

bool LObstacleDistances::isObstacleOnTheRightSide() {
    return isObstacleFrontRight() || isObstacleRight();
}

#pragma mark -
