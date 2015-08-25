//
//  LRoverSonics.h
//  Rover
//
//  Created by Luka Gabric on 21/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LRoverSonics__
#define __Rover__LRoverSonics__

#include "vector"
#include "LUltrasonic.h"
#include "LObstacleDistances.h"

class LRoverSonics {
private:
    LUltrasonic *_frontSonic;
    LUltrasonic *_frontRightSonic;
    LUltrasonic *_frontLeftSonic;
    LUltrasonic *_rightSonic;
    LUltrasonic *_leftSonic;
    
    unsigned int _measureState;
    
    std::vector<LUltrasonic *> _sonics;
    
    LObstacleDistances _obstacleDistances;
    
public:
    LRoverSonics();
    ~LRoverSonics();
    
    void performNextMeasurement();
    
    LObstacleDistances obstacleDistances();
};

#endif /* defined(__Rover__LRoverSonics__) */
