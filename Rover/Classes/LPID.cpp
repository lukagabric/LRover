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
    
}

#pragma mark - Getters/Setters

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

#pragma mark - Debug

void LPID::printPIDToLCD(LLCD *lcd) {
    lcd->print(0, 0, "kp=");
    lcd->print(3, 0, GetKp(), 2);
    lcd->print(9, 0, "ki=");
    lcd->print(12, 0, GetKi(), 2);
    lcd->print(0, 1, "kd=");
    lcd->print(3, 1, GetKd(), 2);
    lcd->print(9, 1, "O=");
    lcd->print(11, 1, output(), 2);
}

void LPID::printPIDToSerial() {
    Serial.print("\nKp: ");Serial.print(GetKp());Serial.print("    Ki:");Serial.print(GetKi());Serial.print("    Kd:");Serial.print(GetKd());Serial.print("    OUTPUT: ");Serial.println(output());
}

#pragma mark -
