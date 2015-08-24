//
//  LUltrasonicLogger.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LUltrasonicLogger__
#define __Rover__LUltrasonicLogger__

#include "LDebugLog.h"
#include "LLCD.h"
#include "LUltrasonic.h"

class LUltrasonicLogger : public LDebugLog {
private:
    LUltrasonic *_sonic;
public:
    LUltrasonicLogger(LUltrasonic *sonic);
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LUltrasonicLogger__) */
