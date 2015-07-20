#include "RoverMain.h"
#include "Arduino.h"

unsigned int ENA = 3;
unsigned int IN1 = 2;
unsigned int IN2 = 4;
unsigned int IN3 = 5;
unsigned int IN4 = 7;
unsigned int ENB = 6;

void RoverMain::setup() {
    motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    Serial.begin(9600);
}

void RoverMain::loop() {
    Serial.println("Loop...");
    moveForward();
    turnRight();
    moveForward();
    turnLeft();
    moveForward();
    turnLeft();
    moveForward();
    turnLeft();
    moveForward();
    turnLeft();
    moveForward();
    turnRight();
    moveForward();
    turnRight();
    moveForward();
    turnRight();
}

void RoverMain::moveForward() {
    Serial.println("Forward for 2 seconds");
    motorController->move(255);
    delay(2000);
}

void RoverMain::turnLeft() {
    Serial.println("Left for 0.5 second");
    motorController->turnLeft(200, true);
    delay(500);
}

void RoverMain::turnRight() {
    Serial.println("Left for 0.5 second");
    motorController->turnRight(200, true);
    delay(500);
}
