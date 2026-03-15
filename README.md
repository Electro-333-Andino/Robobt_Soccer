# Robot de Fútbol con ESP32

Este proyecto implementa un robot controlado por Bluetooth, diseñado para jugar al fútbol o para propósitos de demostración.

## Características

- **Control Remoto:** El robot se controla a través de una aplicación móvil mediante Bluetooth.
- **Movimiento Omnidireccional:** Capaz de moverse hacia adelante, hacia atrás, y girar a la izquierda y derecha.
- **Seguridad:** Incluye un sistema de seguridad que detiene los motores si no se reciben comandos después de un tiempo determinado.

## Componentes de Hardware

- **Microcontrolador:** ESP32
- **Driver de Motores:** L298N

## Aplicación de Control

Para controlar el robot, se utiliza la aplicación **Arduino Bluetooth Controller** disponible para Android. La aplicación debe ser configurada para enviar los siguientes caracteres para cada acción:

- **Adelante:** `F`
- **Atrás:** `B`
- **Izquierda:** `L`
- **Derecha:** `R`
- **Detener:** `S`

## Configuración del Proyecto

Toda la configuración principal del robot se encuentra en el archivo `Config.h`.

### Modificar el Nombre del Bluetooth

Para cambiar el nombre con el que el ESP32 aparece en las búsquedas de Bluetooth, modifica la siguiente línea en `Config.h`:

```cpp
#define BT_DEVICE_NAME "Esp32"
```

### Modificar las Velocidades del Robot

Las velocidades para cada movimiento se pueden ajustar en la sección `CONFIGURACIÓN DE VELOCIDADES` dentro del archivo `Config.h`. Las velocidades se definen con un valor entre 0 y 1023 (para una resolución PWM de 10 bits).

Por ejemplo, para cambiar la velocidad de movimiento hacia adelante:

```cpp
// MOVIMIENTO ADELANTE
#define VEL_ADELANTE_A 1013  // Motor A adelante
#define VEL_ADELANTE_B 1023   // Motor B adelante
```

Puedes ajustar los valores de `VEL_ADELANTE_A` y `VEL_ADELANTE_B` para calibrar el movimiento del robot.
