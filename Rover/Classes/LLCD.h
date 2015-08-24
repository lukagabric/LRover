//
//  LLCD.h
//  Rover
//
//  Created by Luka Gabric on 06/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LLCD__
#define __Rover__LLCD__

#include <LCD.h>
#include <LiquidCrystal_I2C.h>

class LLCD {
private:
    LiquidCrystal_I2C _lcd;
public:
    LLCD();
    void clear();
    void print(unsigned int column, unsigned int line, const char str[]);
    void print(unsigned int column, unsigned int line, double n, int digits);
};

#endif /* defined(__Rover__LLCD__) */
