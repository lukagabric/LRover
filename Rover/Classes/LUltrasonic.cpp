#include "Arduino.h"
#include "LUltrasonic.h"
#include "LLCD.h"

#define MAX_MEASUREABLE_DISTANCE 300

#pragma mark - Constructor

LUltrasonic::LUltrasonic(unsigned int echoPin, unsigned int triggerPin) {
    _echoPin = echoPin;
    _triggerPin = triggerPin;
    
    pinMode(_echoPin, INPUT);
    pinMode(_triggerPin, OUTPUT);
    
    _distance = 0;
}

#pragma mark - Measurment

unsigned long LUltrasonic::singleDistanceMeasurement() {
	unsigned long duration, measuredDistance;

	digitalWrite(_triggerPin, LOW); 
	delayMicroseconds(10); 
	digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(20);
	digitalWrite(_triggerPin, LOW);
	duration = pulseIn(_echoPin, HIGH, 2500);
	measuredDistance = duration / 29 / 2;
    
    return measuredDistance <= MAX_MEASUREABLE_DISTANCE ? measuredDistance : LULTRASONIC_INFINITE_DISTANCE;
}

#pragma mark - Updates

void LUltrasonic::measureDistance() {
    _distance = singleDistanceMeasurement();
}

void LUltrasonic::measureDistance3() {
    unsigned long measures[3];
    
    int i = 0;

    do {
        unsigned long measuredDistance = singleDistanceMeasurement();
        if (measuredDistance <= MAX_MEASUREABLE_DISTANCE) {
            measures[i++] = measuredDistance;
        }
        delay(2);
    } while (i < 3);

    _distance = min((measures[0] + measures[1]) / 2, min((measures[1] + measures[2]) / 2, (measures[0] + measures[2]) / 2));
}

#pragma mark - Getter

unsigned long LUltrasonic::distance() {
    return _distance;
}

#pragma mark - LDebugLog

void LUltrasonic::printToSerial() {
    Serial.print("\nDISTANCE: ");Serial.print(distance());Serial.println(" cm");
}

void LUltrasonic::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "DISTANCE (cm)");
    lcd->print(0, 1, distance(), 1);
}

#pragma mark -
