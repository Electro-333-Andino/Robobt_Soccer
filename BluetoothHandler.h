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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.S
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <Arduino.h>
#include "BluetoothSerial.h"

class BluetoothHandler {
private:
    BluetoothSerial bt;
    String deviceName;
    bool initialized;
    uint32_t messagesReceived;
    uint32_t lastMessageTime;
    uint32_t connectionLostCount;
    uint32_t invalidCommandCount;

public:
    /**
     * @brief Constructor del manejador Bluetooth
     * @param name Nombre del dispositivo Bluetooth
     */
    BluetoothHandler(const String& name);

    /**
     * @brief Inicializa el módulo Bluetooth
     * @return true si la inicialización fue exitosa
     */
    bool init();

    /**
     * @brief Verifica si hay datos disponibles
     * @return true si hay datos para leer
     */
    bool available();

    /**
     * @brief Lee un comando del buffer Bluetooth
     * @return Carácter del comando leído
     */
    char readCommand();

    /**
     * @brief Verifica la salud de la conexión Bluetooth
     */
    void checkHealth();

    /**
     * @brief Imprime mensaje de bienvenida
     */
    void printWelcome();

    /**
     * @brief Imprime estadísticas del sistema
     */
    void printStats();

    /**
     * @brief Verifica si hay un cliente conectado
     * @return true si hay conexión activa
     */
    bool isConnected();

    /**
     * @brief Obtiene el timestamp del último mensaje
     * @return Tiempo del último mensaje en millis()
     */
    uint32_t getLastMessageTime() const;

    /**
     * @brief Incrementa contador de comandos inválidos
     */
    void incrementInvalidCount();
};

#endif // BLUETOOTH_HANDLER_H
