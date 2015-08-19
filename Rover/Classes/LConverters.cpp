//
//  LConverters.cpp
//  Rover
//
//  Created by Luka Gabric on 19/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include <stdio.h>
#include "Arduino.h"

#pragma mark - Deg/Rad Conversions

double degToRad(double deg) {
    return (M_PI / 180) * deg;
}

double radToDeg(double rad) {
    return (180 / M_PI) * rad;
}

#pragma mark -
