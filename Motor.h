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

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
private:
    uint8_t in1;            // Pin dirección 1
    uint8_t in2;            // Pin dirección 2
    uint8_t enablePin;      // Pin PWM (velocidad)
    uint16_t pwmFreq;       // Frecuencia PWM
    uint8_t pwmResolution;  // Resolución PWM
    bool isMoving;          // Estado de movimiento

public:
    /**
     * @brief Constructor del motor
     * @param pin1 Pin IN1 del puente H
     * @param pin2 Pin IN2 del puente H
     * @param en Pin ENABLE (PWM) del puente H
     * @param freq Frecuencia PWM (default: 20kHz)
     * @param res Resolución PWM en bits (default: 10 bits = 0-1023)
     */
    Motor(uint8_t pin1, uint8_t pin2, uint8_t en,
          uint16_t freq = 20000, uint8_t res = 10);

    /**
     * @brief Inicializa los pines y configura PWM
     */
    void init();

    /**
     * @brief Establece la velocidad del motor
     * @param speed Valor entre 0-1023 (o según resolución PWM)
     */
    void setSpeed(uint16_t speed);

    /**
     * @brief Mueve el motor hacia adelante
     * @param speed Velocidad (0-1023)
     */
    void forward(uint16_t speed);

    /**
     * @brief Mueve el motor hacia atrás
     * @param speed Velocidad (0-1023)
     */
    void backward(uint16_t speed);

    /**
     * @brief Detiene el motor completamente
     */
    void stop();

    /**
     * @brief Obtiene el estado de movimiento
     * @return true si el motor está en movimiento
     */
    bool getIsMoving() const;
};

#endif // MOTOR_H
