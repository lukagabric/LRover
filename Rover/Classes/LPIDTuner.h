//
//  LPIDTuner.h
//  Rover
//
//  Created by Luka Gabric on 07/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LPIDTuner__
#define __Rover__LPIDTuner__

#include <Arduino.h>
#include "LPID.h"

class LPIDTuner {
private:
    LPID *_pid;
    uint8_t _potKp, _potKi, _potKd;
    unsigned long _kpMin, _kpMax, _kiMin, _kiMax, _kdMin, _kdMax;
public:
    LPIDTuner(LPID *pid);
    void configurePIDConstants();

    void setPots(uint8_t potKp, uint8_t potKi, uint8_t potKd);
    
    void setKpMinMax(unsigned long kpMin, unsigned long kpMax);
    void setKiMinMax(unsigned long kiMin, unsigned long kiMax);
    void setKdMinMax(unsigned long kdMin, unsigned long kdMax);
};

#endif /* defined(__Rover__LPIDTuner__) */
