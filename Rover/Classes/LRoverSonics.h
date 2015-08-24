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

class LRoverSonics {
private:
    LUltrasonic *_frontSonic;
    LUltrasonic *_frontRightSonic;
    LUltrasonic *_frontLeftSonic;
    LUltrasonic *_rightSonic;
    LUltrasonic *_leftSonic;
    
    unsigned int _measureState;
    
    std::vector<LUltrasonic *> _sonics;
    
public:
    LRoverSonics();
    ~LRoverSonics();
    
    void performNextMeasurement();
    unsigned long frontDistance();
    unsigned long frontRightDistance();
    unsigned long frontLeftDistance();
    unsigned long rightDistance();
    unsigned long leftDistance();
    
    bool isObstacleTooClose();
    bool isObstacleFront();
    bool isObstacleFrontRight();
    bool isObstacleFrontLeft();
    bool isObstacleRight();
    bool isObstacleLeft();
};

#endif /* defined(__Rover__LRoverSonics__) */
