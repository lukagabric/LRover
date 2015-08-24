//
//  LRoverSonics.cpp
//  Rover
//
//  Created by Luka Gabric on 21/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LRoverSonics.h"
#include "LRoverNavigator.h"
#include "Arduino.h"

LRoverSonics::LRoverSonics() {
    _frontSonic = new LUltrasonic(SONIC_FRONT_ECHO, SONIC_FRONT_TRIG);
    _frontRightSonic = new LUltrasonic(SONIC_FRONT_RIGHT_ECHO, SONIC_FRONT_RIGHT_TRIG);
    _frontLeftSonic = new LUltrasonic(SONIC_FRONT_LEFT_ECHO, SONIC_FRONT_LEFT_TRIG);
    _rightSonic = new LUltrasonic(SONIC_RIGHT_ECHO, SONIC_RIGHT_TRIG);
    _leftSonic = new LUltrasonic(SONIC_LEFT_ECHO, SONIC_LEFT_TRIG);
    
    _sonics.push_back(_frontLeftSonic);
    _sonics.push_back(_rightSonic);
    _sonics.push_back(_frontSonic);
    _sonics.push_back(_leftSonic);
    _sonics.push_back(_frontRightSonic);
    
    _measureState = 0;
}

LRoverSonics::~LRoverSonics() {
    delete _frontSonic;
    delete _frontRightSonic;
    delete _frontLeftSonic;
    delete _rightSonic;
    delete _leftSonic;
}


void LRoverSonics::performNextMeasurement() {
    _measureState = ++_measureState % _sonics.size();
    LUltrasonic *sonic = _sonics.at(_measureState);
    sonic->measureDistance();
}

unsigned long LRoverSonics::frontDistance() {
    return _frontSonic->distance();
}

unsigned long LRoverSonics::frontRightDistance() {
    return _frontRightSonic->distance();
}

unsigned long LRoverSonics::frontLeftDistance() {
    return _frontLeftSonic->distance();
}

unsigned long LRoverSonics::rightDistance() {
    return _rightSonic->distance();
}

unsigned long LRoverSonics::leftDistance() {
    return _leftSonic->distance();
}

bool LRoverSonics::isObstacleTooClose() {
    return isObstacleFront() || isObstacleFrontRight() || isObstacleFrontLeft() || isObstacleRight() || isObstacleLeft();
}

bool LRoverSonics::isObstacleFront() {
    return frontDistance() < OBSTACLE_DISTANCE_THRESHOLD;
}

bool LRoverSonics::isObstacleFrontRight() {
    return frontRightDistance() < OBSTACLE_DISTANCE_THRESHOLD;
}

bool LRoverSonics::isObstacleFrontLeft() {
    return frontLeftDistance() < OBSTACLE_DISTANCE_THRESHOLD;
}

bool LRoverSonics::isObstacleRight() {
    return rightDistance() < OBSTACLE_DISTANCE_THRESHOLD;
}

bool LRoverSonics::isObstacleLeft() {
    return leftDistance() < OBSTACLE_DISTANCE_THRESHOLD;
}

#pragma mark -
