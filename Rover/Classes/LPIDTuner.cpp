//
//  LPIDTuner.cpp
//  Rover
//
//  Created by Luka Gabric on 07/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LPIDTuner.h"

#pragma mark - Constructor

LPIDTuner::LPIDTuner(LPID *pid) {
    _pid = pid;
    
    _potKp = A0;
    _potKi = A1;
    _potKd = A2;
    
    _kpMin = 0;
    _kpMax = 2500;
    
    _kiMin = 0;
    _kiMax = 100;
    
    _kdMin = 0;
    _kdMax = 500;
}

#pragma mark - Configuration

void LPIDTuner::configurePIDConstants() {
    int potKp = analogRead(_potKp);
    int potKi = analogRead(_potKi);
    int potKd = analogRead(_potKd);
    
    double kp = map(potKp, 0, 1023, _kpMin, _kpMax) / 100.0;
    double ki = map(potKi, 0, 1023, _kiMin, _kiMax) / 100.0;
    double kd = map(potKd, 0, 1023, _kdMin, _kdMax) / 100.0;
    
    _pid->SetTunings(kp, ki, kd);
}

#pragma mark - Setters

void LPIDTuner::setPots(uint8_t potKp, uint8_t potKi, uint8_t potKd) {
    _potKp = potKp;
    _potKi = potKi;
    _potKd = potKd;
}

void LPIDTuner::setKpMinMax(unsigned long kpMin, unsigned long kpMax) {
    _kpMin = kpMin;
    _kpMax = kpMax;
}

void LPIDTuner::setKiMinMax(unsigned long kiMin, unsigned long kiMax) {
    _kiMin = kiMin;
    _kiMax = kiMax;
}

void LPIDTuner::setKdMinMax(unsigned long kdMin, unsigned long kdMax) {
    _kdMin = kdMin;
    _kdMax = kdMax;
}


#pragma mark -