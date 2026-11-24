/*
 * main.c
 *
 *  Created on: 20 nov. 2026
 *  Author: Gustavo Sanchez
 *  GitHub: GusSanchezArvizu
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"

/* TODO: insert other include files here. */
#include "pmod_led.h"
#include "hal_gpio.h"
/* TODO: insert other definitions and declarations here. */
#define WALK_STEP_DELAY_US 25000U /* 75 ms entre cada LED */

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    //BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    // Empaquetamos la función física de la RW612 en el contrato que pide el driver
    pmod_led_hal_t led_hal = {
        .gpio_write = HAL_GPIO_WritePmodLed
    };
    pmod_led_t board_leds;
    PMOD_LED_Init(&board_leds, &led_hal, false);
    PMOD_LED_WriteMask(&board_leds, 0b10101010);

    PRINTF("Hello World\r\n");

    uint8_t pos = 0U;
	int8_t direction = 1; /* +1 avanza (0 -> 7), -1 retrocede (7 -> 0) */
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	uint8_t pattern = (uint8_t)(1U << pos);
		if (PMOD_LED_WriteMask(&board_leds, pattern) != PMOD_LED_OK) {
			PRINTF("Error de comunicacion con el HAL en pos %u\r\n", pos);
			break;
		}
		if (pos == (PMOD_LED_MAX_CHANNELS - 1U)) {
			direction = -1;
		} else if (pos == 0U) {
			direction = 1;
		}
		pos = (uint8_t)((int8_t)pos + direction);
		SDK_DelayAtLeastUs(WALK_STEP_DELAY_US, SystemCoreClock);
    }
    return 0 ;
}

