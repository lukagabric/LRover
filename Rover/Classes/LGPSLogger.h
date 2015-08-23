//
//  LGPSLogger.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LGPSLogger__
#define __Rover__LGPSLogger__

#include "LDebugLog.h"
#include "LGPS.h"
#include "LLCD.h"

class LGPSLogger : public LDebugLog {
private:
    LGPS *_gps;
public:
    LGPSLogger(LGPS *gps);
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LGPSLogger__) */
