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

#include "RobotController.h"
#include "Config.h"

RobotController::RobotController(uint8_t in1, uint8_t in2, uint8_t ena,
                                 uint8_t in3, uint8_t in4, uint8_t enb)
    : motorA(in1, in2, ena, PWM_FREQUENCY, PWM_RESOLUTION),
      motorB(in3, in4, enb, PWM_FREQUENCY, PWM_RESOLUTION),
      lastCommandTime(0), lastProcessedTime(0),
      safetyEnabled(true), lastCommand('\0') {}

void RobotController::init() {
    motorA.init();
    motorB.init();
    Serial.println(F("[ROBOT] Inicializado en modo SEGURO (motores apagados)"));
}

void RobotController::moveForward() {
    motorA.forward(VEL_ADELANTE_A);
    motorB.forward(VEL_ADELANTE_B);
    updateCommandTime();
    Serial.printf(F("-> Adelante (A:%d, B:%d)\n"), VEL_ADELANTE_A, VEL_ADELANTE_B);
}

void RobotController::moveBackward() {
    motorA.backward(VEL_ATRAS_A);
    motorB.backward(VEL_ATRAS_B);
    updateCommandTime();
    Serial.printf(F("-> Atrás (A:%d, B:%d)\n"), VEL_ATRAS_A, VEL_ATRAS_B);
}

void RobotController::turnLeft() {
    motorA.backward(VEL_IZQUIERDA_A);
    motorB.forward(VEL_IZQUIERDA_B);
    updateCommandTime();
    Serial.printf(F("-> Izquierda (A:%d, B:%d)\n"), VEL_IZQUIERDA_A, VEL_IZQUIERDA_B);
}

void RobotController::turnRight() {
    motorA.forward(VEL_DERECHA_A);
    motorB.backward(VEL_DERECHA_B);
    updateCommandTime();
    Serial.printf(F("-> Derecha (A:%d, B:%d)\n"), VEL_DERECHA_A, VEL_DERECHA_B);
}

void RobotController::stopMotors() {
    motorA.stop();
    motorB.stop();
    Serial.println(F("-> Motores detenidos"));
}

bool RobotController::executeCommand(char cmd) {
    cmd = toupper(cmd);
    uint32_t now = millis();

    // Anti-rebote: ignorar comandos repetidos muy rápidos
    if (now - lastProcessedTime < MIN_COMMAND_INTERVAL) {
        if (cmd == lastCommand && cmd != 'S') {
            updateCommandTime();
            return true;
        }
    }

    lastProcessedTime = now;
    lastCommand = cmd;

    // Ejecutar comando
    switch (cmd) {
        case 'F':
            moveForward();
            return true;
        case 'B':
            moveBackward();
            return true;
        case 'L':
            turnLeft();
            return true;
        case 'R':
            turnRight();
            return true;
        case 'S':
            stopMotors();
            return true;
        default:
            stopMotors();
            Serial.printf(F("[SEGURIDAD] Comando desconocido '%c'\n"), cmd);
            return false;
    }
}

void RobotController::checkSafety() {
    if (!safetyEnabled) return;

    bool motorsActive = motorA.getIsMoving() || motorB.getIsMoving();

    if (motorsActive && lastCommandTime > 0) {
        if (millis() - lastCommandTime > SAFETY_TIMEOUT) {
            stopMotors();
            Serial.println(F("[SEGURIDAD] Timeout - motores detenidos"));
            lastCommandTime = 0;
        }
    }
}

void RobotController::setSafetyMode(bool enabled) {
    safetyEnabled = enabled;
    Serial.printf(F("[SEGURIDAD] %s\n"), enabled ? "ACTIVADO" : "DESACTIVADO");
}

void RobotController::updateCommandTime() {
    lastCommandTime = millis();
}
