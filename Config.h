/**
  * @file Config.h
  * @brief Archivo de configuración central del robot
  * @details Contiene todas las constantes configurables del sistema
  * @author Anderson Andino
  * @version 3.2
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==================== CONFIGURACIÓN BLUETOOTH ====================
#define BT_DEVICE_NAME "Esp32"

// ==================== CONFIGURACIÓN DE PINES GPIO ====================
// Motor A (Derecho)
#define MOTOR_A_IN1 27
#define MOTOR_A_IN2 26
#define MOTOR_A_ENABLE 13

// Motor B (Izquierdo)
#define MOTOR_B_IN1 33
#define MOTOR_B_IN2 32
#define MOTOR_B_ENABLE 14

// ==================== CONFIGURACIÓN DE VELOCIDADES ====================
// Rango: 0-1023 (10 bits PWM)

// MOVIMIENTO ADELANTE
#define VEL_ADELANTE_A 1013  // Motor A adelante
#define VEL_ADELANTE_B 1023   // Motor B adelante

// MOVIMIENTO ATRÁS
#define VEL_ATRAS_A 1023   // Motor A atrás
#define VEL_ATRAS_B 1023   // Motor B atrás

// GIRO IZQUIERDA
#define VEL_IZQUIERDA_A 1023  // Motor A (reversa)
#define VEL_IZQUIERDA_B 1023  // Motor B (adelante)

// GIRO DERECHA
#define VEL_DERECHA_A 1023  // Motor A (adelante)
#define VEL_DERECHA_B 1023  // Motor B (reversa)

// ==================== CONFIGURACIÓN DEL SISTEMA ====================
#define SAFETY_TIMEOUT 2000          // ms - Timeout sin comandos
#define MIN_COMMAND_INTERVAL 50      // ms - Intervalo mínimo entre comandos
#define STATS_INTERVAL 60000         // ms - Intervalo de estadísticas (60s)
#define BT_HEALTH_CHECK 5000         // ms - Chequeo de salud Bluetooth
#define BT_BUFFER_THRESHOLD 5        // bytes - Umbral para limpiar buffer

// ==================== CONFIGURACIÓN PWM ====================
#define PWM_FREQUENCY 20000   // Hz - Frecuencia PWM (20 kHz)
#define PWM_RESOLUTION 10     // bits - Resolución PWM (0-1023)

// ==================== CONFIGURACIÓN SERIAL ====================
#define SERIAL_BAUDRATE 115200  // baudios

#endif // CONFIG_H
