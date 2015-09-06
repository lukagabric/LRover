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

#pragma mark - Constructor/Destructor

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

#pragma mark - Measurement

void LRoverSonics::performNextMeasurement() {
    _measureState = ++_measureState % _sonics.size();
    LUltrasonic *sonic = _sonics.at(_measureState);
    sonic->measureDistance();
    _obstacleDistances = LObstacleDistances(_frontSonic->distance(), _frontLeftSonic->distance(), _frontRightSonic->distance(), _leftSonic->distance(), _rightSonic->distance(), FRONT_OBSTACLE_DISTANCE_THRESHOLD, SIDE_OBSTACLE_DISTANCE_THRESHOLD, OBSTACLE_CLEARED_DISTANCE_THRESHOLD);
}

#pragma mark - Getters

LObstacleDistances LRoverSonics::obstacleDistances() {
    return _obstacleDistances;
}

#pragma mark -
