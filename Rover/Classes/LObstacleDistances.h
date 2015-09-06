//
//  LObstacleDistances.h
//  Rover
//
//  Created by Luka Gabric on 25/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LObstacleDistances__
#define __Rover__LObstacleDistances__

class LObstacleDistances {
private:
    double _frontDistance, _frontLeftDistance, _frontRightDistance, _leftDistance, _rightDistance;
    double _frontObstacleDistanceThreshold, _sideObstacleDistanceThreshold, _obstacleClearDistanceThreshold;
public:
    LObstacleDistances();
    LObstacleDistances(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance, double frontObstacleDistanceThreshold, double sideObstacleDistanceThreshold, double obstacleClearDistanceThreshold);

    double frontObstacleDistanceThreshold();
    double sideObstacleDistanceThreshold();
    double obstacleClearDistanceThreshold();

    double frontDistance();
    double frontRightDistance();
    double frontLeftDistance();
    double rightDistance();
    double leftDistance();

    double minDistance();
    double leftMinDistance();
    double rightMinDistance();

    double leftSideDistance(); //always return front left distance if detected, else left
    double rightSideDistance(); //always return front right distance if detected, else right

    bool isObstacleDetected();
    bool isObstacleCleared();
    
    bool isObstacleFront();
    bool isObstacleFrontRight();
    bool isObstacleFrontLeft();
    bool isObstacleRight();
    bool isObstacleLeft();
    bool isObstacleLeftOrRight();

    bool isObstacleOnTheFrontSide();
    bool isObstacleOnTheLeftSide();
    bool isObstacleOnTheRightSide();
};

#endif /* defined(__Rover__LObstacleDistances__) */
