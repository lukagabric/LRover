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
    _kpMax = 25;
    
    _kiMin = 0;
    _kiMax = 1;
    
    _kdMin = 0;
    _kdMax = 5;
}

#pragma mark - Configuration

void LPIDTuner::configurePIDConstants() {
    int potKp = analogRead(_potKp);
    int potKi = analogRead(_potKi);
    int potKd = analogRead(_potKd);
    
    double kp = map(potKp, 0, 1023, _kpMin * 100, _kpMax * 100) / 100.0;
    double ki = map(potKi, 0, 1023, _kiMin * 100, _kiMax * 100) / 100.0;
    double kd = map(potKd, 0, 1023, _kdMin * 100, _kdMax * 100) / 100.0;
    
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