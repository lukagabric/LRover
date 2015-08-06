//
//  LLCD.cpp
//  Rover
//
//  Created by Luka Gabric on 06/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LLCD.h"

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LLCD::LLCD() {
    _lcd = new LiquidCrystal_I2C(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
    
    _lcd->begin(20,2);
    _lcd->setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    _lcd->setBacklight(HIGH);
    _lcd->home();    
}

void LLCD::print(unsigned int column, unsigned int line, const char str[]) {
    if (line > 1) return;
    
    _lcd->setCursor(column, line);
    _lcd->print(str);
}

void LLCD::print(unsigned int column, unsigned int line, double n, int digits) {
    if (line > 1) return;
    
    _lcd->setCursor(column, line);
    _lcd->print(n, digits);
}
