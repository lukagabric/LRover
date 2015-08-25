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
    _obstacleDistanceThreshold = 0;
    _obstacleClearDistanceThreshold = 0;
}

LObstacleDistances::LObstacleDistances(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance, double obstacleDistanceThreshold, double obstacleClearDistanceThreshold) {
    _frontDistance = frontDistance;
    _frontLeftDistance = frontLeftDistance;
    _frontRightDistance = frontRightDistance;
    _leftDistance = leftDistance;
    _rightDistance = rightDistance;
    _obstacleDistanceThreshold = obstacleDistanceThreshold;
    _obstacleClearDistanceThreshold = obstacleClearDistanceThreshold;
}

#pragma mark - Obstacle Proximity

bool LObstacleDistances::isObstacleDetected() {
    return isObstacleFront() || isObstacleFrontRight() || isObstacleFrontLeft() || isObstacleRight() || isObstacleLeft();
}

bool LObstacleDistances::isObstacleCleared() {
    return (_frontDistance > _obstacleClearDistanceThreshold &&
            _frontLeftDistance > _obstacleClearDistanceThreshold &&
            _frontRightDistance > _obstacleClearDistanceThreshold &&
            _leftDistance > _obstacleClearDistanceThreshold &&
            _rightDistance > _obstacleClearDistanceThreshold);
}

#pragma mark - Absolute Values

double LObstacleDistances::obstacleDistanceThreshold() {
    return _obstacleDistanceThreshold;
}

double LObstacleDistances::obstacleClearDistanceThreshold() {
    return _obstacleClearDistanceThreshold;
}

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
    return _frontDistance < _obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleFrontRight() {
    return _frontRightDistance < _obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleFrontLeft() {
    return _frontLeftDistance < _obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleRight() {
    return _rightDistance < _obstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleLeft() {
    return _leftDistance < _obstacleDistanceThreshold;
}

#pragma mark - Specific Distances

bool LObstacleDistances::isObstacleOnTheLeftSide() {
    return isObstacleFrontLeft() || isObstacleLeft();
}

bool LObstacleDistances::isObstacleOnTheRightSide() {
    return isObstacleFrontRight() || isObstacleRight();
}

#pragma mark -
