#include "Arduino.h"
#include "LUltrasonic.h"

#define MAX_MEASUREABLE_DISTANCE 300

LUltrasonic::LUltrasonic(unsigned int echoPin, unsigned int triggerPin) {
    _echoPin = echoPin;
    _triggerPin = triggerPin;
    
    pinMode(_echoPin, INPUT);
    pinMode(_triggerPin, OUTPUT);
}

unsigned long LUltrasonic::measuredDistance() {
	unsigned long duration, measuredDistance;

	digitalWrite(_triggerPin, LOW); 
	delayMicroseconds(10); 
	digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(20);
	digitalWrite(_triggerPin, LOW);
	duration = pulseIn(_echoPin, HIGH);
	measuredDistance = duration / 29 / 2;
    
    return measuredDistance <= MAX_MEASUREABLE_DISTANCE ? measuredDistance : LULTRASONIC_INFINITE_DISTANCE;
}

void LUltrasonic::updateDistance() {
    distance = measuredDistance();
}

void LUltrasonic::updateDistance3() {
    unsigned long measures[3];
    
    int i = 0;

    do {
        unsigned long measuredDistance = measureDistance();
        if (measuredDistance <= MAX_MEASUREABLE_DISTANCE) {
            measures[i++] = measuredDistance;
        }
        delay(2);
    } while (i < 3);

    return min((measures[0] + measures[1]) / 2, min((measures[1] + measures[2]) / 2, (measures[0] + measures[2]) / 2));
}
