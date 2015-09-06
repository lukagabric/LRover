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
    _frontObstacleDistanceThreshold = 0;
    _sideObstacleDistanceThreshold = 0;
    _obstacleClearDistanceThreshold = 0;
}

LObstacleDistances::LObstacleDistances(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance, double frontObstacleDistanceThreshold, double sideObstacleDistanceThreshold, double obstacleClearDistanceThreshold) {
    _frontDistance = frontDistance;
    _frontLeftDistance = frontLeftDistance;
    _frontRightDistance = frontRightDistance;
    _leftDistance = leftDistance;
    _rightDistance = rightDistance;
    _frontObstacleDistanceThreshold = frontObstacleDistanceThreshold;
    _sideObstacleDistanceThreshold = sideObstacleDistanceThreshold;
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

double LObstacleDistances::frontObstacleDistanceThreshold() {
    return _frontObstacleDistanceThreshold;
}

double LObstacleDistances::sideObstacleDistanceThreshold() {
    return _sideObstacleDistanceThreshold;
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

double LObstacleDistances::minDistance() {
    double sideMinDistance = std::min(leftMinDistance(), rightMinDistance());
    return std::min(frontDistance(), sideMinDistance);
}

double LObstacleDistances::rightMinDistance() {
    return std::min(_frontRightDistance, _rightDistance);
}

double LObstacleDistances::leftMinDistance() {
    return std::min(_frontLeftDistance, _leftDistance);
}

double LObstacleDistances::leftSideDistance() {
    return isObstacleFrontLeft() ? frontLeftDistance() : leftDistance();
}

double LObstacleDistances::rightSideDistance() {
    return isObstacleFrontRight() ? frontRightDistance() : rightDistance();
}

#pragma mark - Each Distance

bool LObstacleDistances::isObstacleFront() {
    return _frontDistance < _frontObstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleFrontRight() {
    return _frontRightDistance < _sideObstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleFrontLeft() {
    return _frontLeftDistance < _sideObstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleRight() {
    return _rightDistance < _sideObstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleLeft() {
    return _leftDistance < _sideObstacleDistanceThreshold;
}

bool LObstacleDistances::isObstacleLeftOrRight() {
    return isObstacleLeft() || isObstacleRight();
}

#pragma mark - Specific Distances

bool LObstacleDistances::isObstacleOnTheFrontSide() {
    return isObstacleFrontLeft() || isObstacleFront() || isObstacleFrontRight();
}

bool LObstacleDistances::isObstacleOnTheLeftSide() {
    return isObstacleFrontLeft() || isObstacleLeft();
}

bool LObstacleDistances::isObstacleOnTheRightSide() {
    return isObstacleFrontRight() || isObstacleRight();
}

#pragma mark -
