#include "Arduino.h"
#include "LUltrasonic.h"

#pragma mark - Constructor

LUltrasonic::LUltrasonic(unsigned int echoPin, unsigned int triggerPin) {
    _sonic = new NewPing(triggerPin, echoPin, MAX_MEASUREABLE_DISTANCE);
    _distance = LULTRASONIC_INFINITE_DISTANCE;
}

#pragma mark - Measurment

unsigned long LUltrasonic::singleDistanceMeasurement() {
    unsigned long measuredDistance = _sonic->ping_cm();
    
    return measuredDistance <= MAX_MEASUREABLE_DISTANCE && measuredDistance > 0 ? measuredDistance : LULTRASONIC_INFINITE_DISTANCE;
}

#pragma mark - Updates

void LUltrasonic::measureDistance() {
    unsigned long currentTime = millis();
    _distance = singleDistanceMeasurement();
    Serial.print(_distance);Serial.print("\t");Serial.println(millis() - currentTime);
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

#pragma mark -
