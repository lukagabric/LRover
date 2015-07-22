#include "Arduino.h"
#include "LUltrasonic.h"

#define MAX_MEASUREABLE_DISTANCE 300
#define INFINITE_DISTANCE 999999

LUltrasonic::LUltrasonic(unsigned int echoPin, unsigned int triggerPin) {
    _echoPin = echoPin;
    _triggerPin = triggerPin;
}

unsigned long LUltrasonic::measureDistance() {
	unsigned long duration, distance; 
	
	digitalWrite(_triggerPin, LOW); 
	delayMicroseconds(10); 
	digitalWrite(_triggerPin, HIGH); 
	delayMicroseconds(20); 
	digitalWrite(_triggerPin, LOW); 
	duration = pulseIn(_echoPin, HIGH); 
	distance = duration / 29 / 2;
	
	return distance <= MAX_MEASUREABLE_DISTANCE ? distance : INFINITE_DISTANCE;
}


unsigned long LUltrasonic::measureDistance3() {
    unsigned long measures[3];
    
    int i = 0;

    do {
        unsigned long distance = measureDistance();
        if (distance <= MAX_MEASUREABLE_DISTANCE) {
            measures[i++] = distance;
        }
        delay(2);
    } while (i < 3);

    return min((measures[0] + measures[1]) / 2, min((measures[1] + measures[2]) / 2, (measures[0] + measures[2]) / 2));
}
