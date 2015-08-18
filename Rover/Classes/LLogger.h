//
//  LLogger.h
//  Rover
//
//  Created by Luka Gabric on 08/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LLogger__
#define __Rover__LLogger__

#include "vector"
#include "LLCD.h"
#include "LDebugLog.h"

class LLogger {
    std::vector<LDebugLog*> _logItems;
    unsigned int _lcdDebugLogState;
    LLCD *_lcd;
public:
    LLogger(LLCD *lcd, std::vector<LDebugLog*> logItems);
    void debugLogToLCD();
    void skipNextDebugLogToLCD();
    void debugLogToSerial();
};

#endif /* defined(__Rover__LLogger__) */
