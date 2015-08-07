//
//  LLowPassFilter.cpp
//  Rover
//
//  Created by Luka Gabric on 25/07/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LLowPassFilter.h"

#pragma mark - Constructor

LLowPassFilter::LLowPassFilter(double RC, double dt) {
    _RC = RC;
    _dt = dt;
    updateAlpha();
}

#pragma mark - Getters/Setters

void LLowPassFilter::setRC(double RC) {
    _RC = RC;
    updateAlpha();
}

double LLowPassFilter::RC() {
    return _RC;
}

void LLowPassFilter::setDt(double dt) {
    _dt = dt;
    updateAlpha();
}

double LLowPassFilter::dt() {
    return _dt;
}

double LLowPassFilter::alpha() {
    return _alpha;
}

double LLowPassFilter::currentFilteredValue() {
    return _currentFilteredValue;
}


double LLowPassFilter::currentRawValue() {
    return _currentRawValue;
}

#pragma mark - Alpha

void LLowPassFilter::updateAlpha() {
    _alpha = dt() / (RC() + dt());
}

#pragma mark - Filter

double LLowPassFilter::filterValue(double rawValue) {
    _currentRawValue = rawValue;
    _currentFilteredValue = rawValue * alpha() + (1 - alpha()) * currentFilteredValue();
    return currentFilteredValue();
}

#pragma mark -
