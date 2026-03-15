/**
 * @file BluetoothHandler.cpp
 * @brief Implementación del manejador Bluetooth
 * @author Anderson Andino
 * @version 3.2
*/

#include "BluetoothHandler.h"
#include "Config.h"

BluetoothHandler::BluetoothHandler(const String& name)
    : deviceName(name), initialized(false), messagesReceived(0),
      lastMessageTime(0), connectionLostCount(0), invalidCommandCount(0) {}

bool BluetoothHandler::init() {
    // Reinicio limpio si ya estaba iniciado
    if (initialized) {
        bt.end();
    }

    if (!bt.begin(deviceName)) {
        Serial.println(F("[BT ERROR] No se pudo inicializar Bluetooth"));
        return false;
    }

    initialized = true;
    Serial.println(F("[BT OK] Bluetooth inicializado correctamente"));
    return true;
}

bool BluetoothHandler::available() {
    return initialized && bt.available();
}

char BluetoothHandler::readCommand() {
    if (!initialized) return '\0';

    char cmd = bt.read();

    // Limpieza condicional de buffer (solo si hay exceso)
    int clearCount = 0;
    if (bt.available() > BT_BUFFER_THRESHOLD) {
        while (bt.available()) {
            bt.read();
            clearCount++;
            delay(1);  // yield cooperativo
        }
        if (clearCount > 0) {
            Serial.printf(F("[BT INFO] Buffer drenado (%d bytes)\n"), clearCount);
        }
    }

    messagesReceived++;
    lastMessageTime = millis();
    return cmd;
}

void BluetoothHandler::checkHealth() {
    if (!initialized) return;

    if (!bt.hasClient() && lastMessageTime > 0) {
        if (millis() - lastMessageTime > 5000) {
            connectionLostCount++;
            Serial.println(F("[BT] Cliente desconectado"));
            lastMessageTime = 0;
        }
    }
}

void BluetoothHandler::printWelcome() {
    Serial.println(F("=========================================="));
    Serial.println(F("ESP32 Control de Motores v3.2 (Modular)"));
    Serial.printf(F("Nombre BT: %s\n"), deviceName.c_str());
    Serial.println(F("=========================================="));
    Serial.println(F("Comandos: F (adelante), B (atrás), L (izq), R (der), S (stop)"));
    Serial.printf(F("Timeout seguridad: %dms\n"), SAFETY_TIMEOUT);
    Serial.println(F("Estado inicial: MOTORES APAGADOS"));
    Serial.println(F("=========================================="));
}

void BluetoothHandler::printStats() {
    Serial.println(F("\n--- ESTADÍSTICAS ---"));
    Serial.printf(F("Mensajes recibidos: %d\n"), messagesReceived);
    Serial.printf(F("Comandos inválidos: %d\n"), invalidCommandCount);
    Serial.printf(F("Cliente conectado: %s\n"), isConnected() ? "SÍ" : "NO");
    Serial.printf(F("Conexiones perdidas: %d\n"), connectionLostCount);
    Serial.printf(F("Uptime: %lu s\n"), millis() / 1000);
    Serial.printf(F("Memoria libre: %d bytes\n"), ESP.getFreeHeap());
    Serial.println(F("--------------------\n"));
}

bool BluetoothHandler::isConnected() {
    return initialized && bt.hasClient();
}

uint32_t BluetoothHandler::getLastMessageTime() const {
    return lastMessageTime;
}

void BluetoothHandler::incrementInvalidCount() {
    invalidCommandCount++;
}
