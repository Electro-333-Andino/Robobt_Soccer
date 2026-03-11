/**
 * @file Motor.cpp
 * @brief Implementación de la clase Motor
 * @author Anderson Andino
 * @version 3.2
*/

#include "Motor.h"

Motor::Motor(uint8_t pin1, uint8_t pin2, uint8_t en, uint16_t freq, uint8_t res)
    : in1(pin1), in2(pin2), enablePin(en), pwmFreq(freq),
      pwmResolution(res), isMoving(false) {}

void Motor::init() {
    // Configurar pines digitales
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enablePin, OUTPUT);

    // Estado inicial: apagado
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    // Configurar PWM (API ESP32 Core 3.x.x)
    ledcAttach(enablePin, pwmFreq, pwmResolution);
    ledcWrite(enablePin, 0);

    isMoving = false;
}

void Motor::setSpeed(uint16_t speed) {
    // Limitar velocidad al máximo según resolución
    uint16_t maxSpeed = (1 << pwmResolution) - 1; // 2^bits - 1
    if (speed > maxSpeed) speed = maxSpeed;

    ledcWrite(enablePin, speed);
    isMoving = (speed > 0);
}

void Motor::forward(uint16_t speed) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    setSpeed(speed);
}

void Motor::backward(uint16_t speed) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    setSpeed(speed);
}

void Motor::stop() {
    setSpeed(0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    isMoving = false;
}

bool Motor::getIsMoving() const {
    return isMoving;
}
