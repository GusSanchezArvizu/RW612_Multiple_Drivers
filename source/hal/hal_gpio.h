/*
 * hal_gpio.h
 *
 *  Created on: 14 nov. 2026
 *      Author: gusta
 */


#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Escribe un nivel lógico en uno de los 8 canales asignados al PMOD-LEDx8.
 * @param[in] channel Índice lógico del LED (0 a 7).
 * @param[in] state   Nivel lógico deseado (true = alto / 3.3V, false = bajo / 0V).
 * @return true si la operación fue válida, false si el canal está fuera de rango.
 */
bool HAL_GPIO_WritePmodLed(uint8_t channel, bool state);

#endif /* HAL_GPIO_H */
