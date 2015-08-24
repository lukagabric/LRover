//
//  LMotorControllerLogger.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LMotorControllerLogger__
#define __Rover__LMotorControllerLogger__

#include "LDebugLog.h"
#include "LLCD.h"
#include "LMotorController.h"

class LMotorControllerLogger : public LDebugLog {
private:
    LMotorController *_motorController;
public:
    LMotorControllerLogger(LMotorController *motorController);
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LMotorControllerLogger__) */
