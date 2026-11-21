/*
 * main.c
 *
 *  Created on: 14 nov. 2026
 *      Author: gusta
 */
/**
 * @file    RW612_Project_PMOD_SiPEED.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "pmod_led.h"
#include "hal_gpio.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    /*
    // 1. Empaquetamos la función física de la RW612 en el contrato que pide el driver
    pmod_led_hal_t led_hal = {
        .gpio_write = HAL_GPIO_WritePmodLed
    };
    pmod_led_t board_leds;
    // 2. Le entregamos el HAL al driver (Inyección de Dependencias)
    PMOD_LED_Init(&board_leds, &led_hal, false);
    // 3. La aplicación usa el driver sin preocuparse por pines ni registros
    PMOD_LED_WriteMask(&board_leds, 0b10101010);
     */
    PRINTF("Hello World\r\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

