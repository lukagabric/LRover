//
//  LPIDLogger.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LPIDLogger__
#define __Rover__LPIDLogger__

#include "LDebugLog.h"
#include "LLCD.h"
#include "LPID.h"

class LPIDLogger : public LDebugLog {
private:
    LPID *_pid;
public:
    LPIDLogger(LPID *pid);
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LPIDLogger__) */
