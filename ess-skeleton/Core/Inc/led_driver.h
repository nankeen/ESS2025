/**
 * LED Driver
 *
 * @author Andrew Markham
 * @version v1.0
 * @ide STM32Cube
 * @license GNU GPL v3
 */
#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include <stdint.h>

// Generic struct to encapsulate LED state.
typedef struct
{
	volatile uint32_t *port;
	uint16_t pin;
} LED_t;

// Function Declarations
void led_init(LED_t *led, volatile uint32_t *port, uint32_t pin);
void led_on(LED_t *led);
void led_off(LED_t *led);
#endif
