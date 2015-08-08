//
//  LPID.h
//  Rover
//
//  Created by Luka Gabric on 07/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LPID__
#define __Rover__LPID__

#include <Arduino.h>
#include "LLCD.h"
#include "PID_v1.h"
#include "LDebugLog.h"

class LPID : public PID, public LDebugLog {
private:
    double _myInput, _myOutput, _mySetpoint;
public:
    LPID(double kp, double ki, double kd, int direction);
    
    void setSetpoint(double setpoint);
    double setpoint();
    void setInput(double input);
    double input();
    double output();
    
    void printToSerial();
    void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LPID__) */
