//
//  LPIDTuner.cpp
//  Rover
//
//  Created by Luka Gabric on 07/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LPIDTuner.h"

#pragma mark - Constructor

LPIDTuner::LPIDTuner(LPID *pid, uint8_t potKp, uint8_t potKi, uint8_t potKd) {
    _pid = pid;

    setPots(potKp, potKi, potKd);
    
    _kpMin = 0;
    _kpMax = 2500;
    _kpDivide = 100;
    
    _kiMin = 0;
    _kiMax = 100;
    _kiDivide = 100;
    
    _kdMin = 0;
    _kdMax = 500;
    _kdDivide = 100;
}

#pragma mark - Configuration

void LPIDTuner::configurePIDConstants() {
    int potKp = analogRead(_potKp);
    int potKi = analogRead(_potKi);
    int potKd = analogRead(_potKd);
    
    double kp = map(potKp, 0, 1023, _kpMin, _kpMax) / _kpDivide;
    double ki = map(potKi, 0, 1023, _kiMin, _kiMax) / _kiDivide;
    double kd = map(potKd, 0, 1023, _kdMin, _kdMax) / _kdDivide;
    
    _pid->SetTunings(kp, ki, kd);
}

#pragma mark - Setters

void LPIDTuner::setPots(uint8_t potKp, uint8_t potKi, uint8_t potKd) {
    _potKp = potKp;
    _potKi = potKi;
    _potKd = potKd;
}

void LPIDTuner::setKpMinMaxDiv(unsigned long kpMin, unsigned long kpMax, double kpDivide) {
    _kpMin = kpMin;
    _kpMax = kpMax;
    _kpDivide = kpDivide;
}

void LPIDTuner::setKiMinMaxDiv(unsigned long kiMin, unsigned long kiMax, double kiDivide) {
    _kiMin = kiMin;
    _kiMax = kiMax;
    _kiDivide = kiDivide;
}

void LPIDTuner::setKdMinMaxDiv(unsigned long kdMin, unsigned long kdMax, double kdDivide) {
    _kdMin = kdMin;
    _kdMax = kdMax;
    _kdDivide = kdDivide;
}

#pragma mark -