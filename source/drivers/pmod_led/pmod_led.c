/*
 * pmod_led.c
 *
 *  Created on: 20 nov. 2026
 *      Author: gusta
 */

#include "pmod_led.h"

pmod_led_status_t PMOD_LED_Init(pmod_led_t *dev, const pmod_led_hal_t *hal, bool active_low)
{
	if(dev == NULL || hal == NULL || hal->gpio_write == NULL)
	{
		return PMOD_LED_ERR_NULL_PTR;
	}

	dev->active_low = active_low;
	dev->current_mask = 0b00000000;
	dev->is_initialized = true;
	dev->hal = *hal;

	pmod_led_status_t init_state = PMOD_LED_WriteMask(dev, 0x00);
	if(init_state != PMOD_LED_OK)
	{
		dev->is_initialized = false;
		return init_state;
	}
	return PMOD_LED_OK;
}

pmod_led_status_t PMOD_LED_WriteMask(pmod_led_t *dev, uint8_t bitmask)
{
	if(dev == NULL || dev->is_initialized == false)
	{
		return PMOD_LED_ERR_NULL_PTR;
	}

	for(uint8_t i = 0; i < PMOD_LED_MAX_CHANNELS; i++)
	{
		// Corrimiento de i posiciones para evaluar bit pot bit + enmascaramiento + evaluación boleana
		bool single_bit = ((bitmask >> i)&0x01U) != 0U;
		// Bandera de estado para seguir la lógica de encendido del led
		bool led_status = dev->active_low ? !single_bit : single_bit;
		if(!dev->hal.gpio_write(i,led_status))
		{
			return PMOD_LED_ERR_HAL_FAILURE;
		}
	}
	dev->current_mask = bitmask;
	return PMOD_LED_OK;
}

pmod_led_status_t PMOD_LED_SetSingle(pmod_led_t *dev, uint8_t channel, bool state)
{
	if(dev == NULL || dev->is_initialized == false)
	{
		return PMOD_LED_ERR_NULL_PTR;
	}
	else if(channel >= PMOD_LED_MAX_CHANNELS)
	{
		return PMOD_LED_ERR_INVALID_CHANNEL;
	}
	bool led_status = dev->active_low ? !state : state;

	if(!dev->hal.gpio_write(channel,led_status))
	{
		return PMOD_LED_ERR_HAL_FAILURE;
	}
	if(state)
	{
		dev->current_mask |= (0x01U << channel);
	}
	else
	{
		dev->current_mask &= ~(0x01U << channel);
	}

	return PMOD_LED_OK;
}

pmod_led_status_t PMOD_LED_ToggleSingle(pmod_led_t *dev, uint8_t channel)
{
	if(dev == NULL || dev->is_initialized == false)
	{
		return PMOD_LED_ERR_NULL_PTR;
	}
	else if(channel >= PMOD_LED_MAX_CHANNELS)
	{
		return PMOD_LED_ERR_INVALID_CHANNEL;
	}
	uint8_t led_mask = dev->current_mask ^ (0x01U<<channel);
	bool single_bit = ((led_mask >> channel)&0x01U) != 0U;
	bool led_status = dev->active_low ? !(single_bit): single_bit;
	if(!dev->hal.gpio_write(channel,led_status))
	{
		return PMOD_LED_ERR_HAL_FAILURE;
	}
	dev->current_mask = led_mask;
	return PMOD_LED_OK;
}



