//
//  LCompassLogger.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LCompassLogger__
#define __Rover__LCompassLogger__

#include "LDebugLog.h"
#include "LLCD.h"
#include "LCompass.h"

class LCompassLogger : public LDebugLog {
private:
    LCompass *_compass;
public:
    LCompassLogger(LCompass *compass);
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LCompassLogger__) */
