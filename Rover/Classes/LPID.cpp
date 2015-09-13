//
//  LPID.cpp
//  Rover
//
//  Created by Luka Gabric on 07/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LPID.h"

#pragma mark - Constructor

LPID::LPID(double kp, double ki, double kd, int direction) : PID(&_myInput, &_myOutput, &_mySetpoint, kp, ki, kd, DIRECT) {
    _mySetpoint = 0;
    _myInput = 0;
    _myOutput = 0;
}

#pragma mark - Getters/Setters

void LPID::setDefaultOutputLimits(double defaultOutMin, double defaultOutMax) {
    _defaultOutMin = defaultOutMin;
    _defaultOutMax = defaultOutMax;
    resetOutput();
}

double LPID::defaultOutMin() {
    return _defaultOutMin;
}

double LPID::defaultOutMax() {
    return _defaultOutMax;
}

void LPID::resetOutput() {
    SetOutputLimits(0, 0.00000001);
    SetOutputLimits(defaultOutMin(), defaultOutMax());
}

void LPID::setSetpoint(double setpoint) {
    _mySetpoint = setpoint;
}

double LPID::setpoint() {
    return _mySetpoint;
}

void LPID::setInput(double input) {
    _myInput = input;
}

double LPID::input() {
    return _myInput;
}

double LPID::output() {
    return _myOutput;
}

#pragma mark -
