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
#include "LDebugLog.h"
#include "LUltrasonic.h"

class LRoverSonics : public LDebugLog {
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
    
    void performNextMeasurement();
    unsigned long frontDistance();
    unsigned long frontRightDistance();
    unsigned long frontLeftDistance();
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LRoverSonics__) */
