/**
 * @file hal_gpio.c
 * @brief Implementación física de GPIO usando el SDK de NXP para RW612.
 */

#include "hal_gpio.h"
#include "fsl_gpio.h"

#define PMOD_LED_CHANNEL_COUNT 8U

typedef struct {
    uint32_t port;
    uint32_t pin;
} rw612_gpio_map_t;

/**
 * @brief Mapeo físico de canales lógicos (0..7) a Puerto/Pin de la RW612.
 * @note Ajusta el orden de las filas si los LEDs encienden invertidos físicamente.
 */
static const rw612_gpio_map_t kPmodLedPinMap[PMOD_LED_CHANNEL_COUNT] = {
    { .port = 0U, .pin = 16U }, /* Canal 0 -> J3  (GPIO_16) */
	{ .port = 1U, .pin = 16U }, /* Canal 5 -> D13 (GPIO_48) */
    { .port = 0U, .pin = 17U }, /* Canal 1 -> H2  (GPIO_17) */
	{ .port = 1U, .pin = 15U }, /* Canal 4 -> E13 (GPIO_47) */
	{ .port = 1U, .pin = 12U }, /* Canal 3 -> J11 (GPIO_44) */
	{ .port = 1U, .pin = 14U }, /* Canal 2 -> J7 Pin 3 (GPIO_46) */
    { .port = 0U, .pin = 18U }, /* Canal 2 -> K3  (GPIO_18) */
    { .port = 1U, .pin = 17U }, /* Canal 6 -> D14 (GPIO_49) */
};

bool HAL_GPIO_WritePmodLed(uint8_t channel, bool state)
{
    if (channel >= PMOD_LED_CHANNEL_COUNT) {
        return false;
    }

    GPIO_PinWrite(GPIO,
                  kPmodLedPinMap[channel].port,
                  kPmodLedPinMap[channel].pin,
                  state ? 1U : 0U);

    return true;
}
