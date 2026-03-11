/**
 * @file BluetoothHandler.h
 * @brief Manejador de comunicación Bluetooth Serial
 * @author Anderson Andino
 * @version 3.2
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
