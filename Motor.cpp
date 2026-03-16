/*
 * Copyright 2026 Anderson Andino
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
