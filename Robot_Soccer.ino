/*
 * @author Anderson Andino
 * @version 3.2
*/

#include "BluetoothSerial.h"

// Verificación de Bluetooth habilitado
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no está habilitado! Por favor ejecuta make menuconfig para habilitarlo
#endif

// Incluir todos los archivos de cabecera
#include "Config.h"
#include "Motor.h"
#include "RobotController.h"
#include "BluetoothHandler.h"

// ==================== INSTANCIAS GLOBALES ====================
RobotController robot(MOTOR_A_IN1, MOTOR_A_IN2, MOTOR_A_ENABLE,
                      MOTOR_B_IN1, MOTOR_B_IN2, MOTOR_B_ENABLE);

BluetoothHandler bluetooth(BT_DEVICE_NAME);

uint32_t lastStatsTime = 0;
uint32_t lastBTCheck = 0;

// ==================== SETUP ====================
void setup() {
    // Inicializar comunicación serial
    Serial.begin(SERIAL_BAUDRATE);
    delay(100);

    Serial.println(F("\n\n=== INICIANDO SISTEMA ==="));

    // Inicializar robot (motores)
    robot.init();

    // Inicializar Bluetooth
    if (!bluetooth.init()) {
        Serial.println(F("[ERROR CRÍTICO] Bluetooth falló"));
        while (1) {
            delay(1000);
            Serial.print(F("."));
        }
    }

    // Mostrar mensaje de bienvenida
    bluetooth.printWelcome();
    Serial.println(F("[SISTEMA] Listo para recibir comandos\n"));
}

// ==================== LOOP ====================
void loop() {
    // Verificar timeout de seguridad
    robot.checkSafety();

    // Verificar salud de la conexión Bluetooth
    bluetooth.checkHealth();

    // Verificar y reiniciar BT si es necesario
    if (millis() - lastBTCheck > BT_HEALTH_CHECK) {
        lastBTCheck = millis();
        if (!bluetooth.isConnected()) {
            Serial.println(F("[BT] Cliente no conectado, reiniciando Bluetooth..."));
            bluetooth.init();
        }
    }

    // Procesar comandos Bluetooth
    if (bluetooth.available()) {
        char cmd = bluetooth.readCommand();

        // Filtrar caracteres no válidos (espacios, saltos de línea, etc.)
        if (cmd == '\0' || cmd == '\n' || cmd == '\r' || cmd == ' ' || cmd == '\t') {
            return;
        }

        // Filtrar caracteres fuera del rango ASCII imprimible
        if (cmd < 32 || cmd > 126) {
            Serial.printf(F("[BT] Carácter no válido: 0x%02X\n"), (uint8_t)cmd);
            robot.executeCommand('S');  // Detener por seguridad
            bluetooth.incrementInvalidCount();
            return;
        }

        // Ejecutar comando
        Serial.printf(F("[CMD] '%c' | "), cmd);
        if (!robot.executeCommand(cmd)) {
            Serial.println(F("INVÁLIDO"));
            bluetooth.incrementInvalidCount();
        }
    }

    // Imprimir estadísticas periódicamente
    if (millis() - lastStatsTime > STATS_INTERVAL) {
        bluetooth.printStats();
        lastStatsTime = millis();
    }

    // Mantener viva la tarea Bluetooth y controlar CPU
    yield();
    delay(5);
}
