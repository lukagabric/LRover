//
//  LRoverSonicsLogger.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LRoverSonicsLogger__
#define __Rover__LRoverSonicsLogger__

#include "LRoverSonics.h"
#include "LDebugLog.h"
#include "LLCD.h"

class LRoverSonicsLogger : public LDebugLog {
private:
    LRoverSonics *_sonics;
public:
    LRoverSonicsLogger(LRoverSonics *sonics);
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LRoverSonicsLogger__) */
