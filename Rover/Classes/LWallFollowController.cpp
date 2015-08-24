//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;
}

LWheelSpeeds LWallFollowController::wallFollowOutput(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance) {
    _frontDistance = frontDistance;
    _frontLeftDistance = frontLeftDistance;
    _frontRightDistance = frontRightDistance;
    _leftDistance = leftDistance;
    _rightDistance = rightDistance;
}
