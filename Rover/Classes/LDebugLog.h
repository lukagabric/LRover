//
//  LDebugLog.h
//  Rover
//
//  Created by Luka Gabric on 08/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LDebugLog__
#define __Rover__LDebugLog__

#include "LLCD.h"

class LDebugLog {
public:
    virtual ~LDebugLog() {};
    virtual void printToSerial() = 0;
    virtual void printToLCD(LLCD *lcd) = 0;
};

#endif /* defined(__Rover__LDebugLog__) */
