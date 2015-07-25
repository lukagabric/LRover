//
//  LLowPassFilter.h
//  Rover
//
//  Created by Luka Gabric on 25/07/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LLowPassFilter__
#define __Rover__LLowPassFilter__

class LLowPassFilter {
protected:
    double _alpha, _currentValue;
public:
    LLowPassFilter(double RC, double dt);
    double filteredValue(double rawValue);
};

#endif /* defined(__Rover__LLowPassFilter__) */
