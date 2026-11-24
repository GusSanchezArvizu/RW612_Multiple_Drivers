/*
 * pmod_led.h
 *
 *  Created on: 20 nov. 2026
 *  Author: Gustavo Sanchez
 *  GitHub: GusSanchezArvizu
 *
 */

#ifndef PMOD_LED_H
#define PMOD_LED_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define PMOD_LED_MAX_CHANNELS 8U

/** @brief Códigos de retorno explícitos para tolerancia a fallos. */
typedef enum {
    PMOD_LED_OK = 0,
    PMOD_LED_ERR_NULL_PTR,
    PMOD_LED_ERR_INVALID_CHANNEL,
    PMOD_LED_ERR_HAL_FAILURE
} pmod_led_status_t;

/** @brief Interfaz HAL inyectada (punteros a funciones físicas del MCU). */
typedef struct {
    bool (*gpio_write)(uint8_t channel, bool logic_level);
} pmod_led_hal_t;

/** @brief Instancia del driver (encapsula el estado del módulo). */
typedef struct {
    pmod_led_hal_t hal;
    bool active_low;      /**< true si el LED enciende con 0 lógico, false con 1 */
    uint8_t current_mask; /**< Estado actual de los 8 LEDs (bit 0 = LED 1 ... bit 7 = LED 8) */
    bool is_initialized;
} pmod_led_t;

/**
 * @brief Inicializa la instancia del módulo PMOD-LEDx8 y apaga todos los LEDs.
 * @param[out] dev Puntero a la estructura del dispositivo.
 * @param[in]  hal Puntero a las funciones de abstracción de hardware.
 * @param[in]  active_low Polaridad eléctrica de los LEDs en la placa.
 * @return PMOD_LED_OK si la inicialización fue exitosa.
 */
pmod_led_status_t PMOD_LED_Init(pmod_led_t *dev, const pmod_led_hal_t *hal, bool active_low);

/**
 * @brief Escribe una máscara de 8 bits directamente en los 8 LEDs.
 * @param[in,out] dev Puntero a la instancia del driver.
 * @param[in]     bitmask Byte donde cada bit representa el estado deseado de un LED.
 * @return PMOD_LED_OK o código de error correspondiente.
 */
pmod_led_status_t PMOD_LED_WriteMask(pmod_led_t *dev, uint8_t bitmask);

/**
 * @brief Enciende o apaga un LED individual (0 a 7) sin alterar los demás.
 */
pmod_led_status_t PMOD_LED_SetSingle(pmod_led_t *dev, uint8_t channel, bool state);

/**
 * @brief Invierte el estado lógico actual de un LED individual (0 a 7).
 */
pmod_led_status_t PMOD_LED_ToggleSingle(pmod_led_t *dev, uint8_t channel);

#endif // PMOD_LED_H
