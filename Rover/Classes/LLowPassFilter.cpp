//
//  LLowPassFilter.cpp
//  Rover
//
//  Created by Luka Gabric on 25/07/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LLowPassFilter.h"

LLowPassFilter::LLowPassFilter(double RC, double dt) {
    _alpha = dt / (RC + dt);
}

double LLowPassFilter::filteredValue(double rawValue) {
    _currentValue = rawValue * _alpha + (1 - _alpha) * _currentValue;
    return _currentValue;
}
