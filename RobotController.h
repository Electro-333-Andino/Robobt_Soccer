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

#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include <Arduino.h>
#include "Motor.h"

class RobotController {
private:
    Motor motorA;              // Motor derecho
    Motor motorB;              // Motor izquierdo
    uint32_t lastCommandTime;  // Timestamp del último comando
    uint32_t lastProcessedTime;// Timestamp del último procesamiento
    bool safetyEnabled;        // Sistema de seguridad activo
    char lastCommand;          // Último comando ejecutado

    /**
     * @brief Actualiza el timestamp del último comando
     */
    void updateCommandTime();

public:
    /**
     * @brief Constructor del controlador
     * @param in1 Pin IN1 Motor A
     * @param in2 Pin IN2 Motor A
     * @param ena Pin ENABLE Motor A
     * @param in3 Pin IN1 Motor B
     * @param in4 Pin IN2 Motor B
     * @param enb Pin ENABLE Motor B
     */
    RobotController(uint8_t in1, uint8_t in2, uint8_t ena,
                    uint8_t in3, uint8_t in4, uint8_t enb);

    /**
     * @brief Inicializa ambos motores
     */
    void init();

    /**
     * @brief Mueve el robot hacia adelante
     */
    void moveForward();

    /**
     * @brief Mueve el robot hacia atrás
     */
    void moveBackward();

    /**
     * @brief Gira el robot a la izquierda
     */
    void turnLeft();

    /**
     * @brief Gira el robot a la derecha
     */
    void turnRight();

    /**
     * @brief Detiene ambos motores
     */
    void stopMotors();

    /**
     * @brief Ejecuta un comando recibido
     * @param cmd Carácter del comando (F/B/L/R/S)
     * @return true si el comando fue válido
     */
    bool executeCommand(char cmd);

    /**
     * @brief Verifica timeout de seguridad
     * @details Detiene motores si no hay comandos en SAFETY_TIMEOUT ms
     */
    void checkSafety();

    /**
     * @brief Activa/desactiva el modo seguridad
     * @param enabled true para activar
     */
    void setSafetyMode(bool enabled);
};

#endif // ROBOT_CONTROLLER_H
