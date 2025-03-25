/**
 * Four Channel PWM driver
 */
#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H
#include <stdint.h>

// include led_driver to get the definition of LED_t
#include "led_driver.h"

// Set the maximum duty cycle to 100%
#define PWM_MAX_DUTY_CYCLE 100
#define PWM_CHANNELS 4

// initialize pwm driver. This assumes that led_init() has been previously
// called for each channel to populate the LED_t struct properly
// [channels] must be an array with exactly PWM_CHANNELS pointers
void pwm_driver_init(LED_t *channels[]);

// Set brightness value for a particular channel (channel between 0 and 3).
// Value ranges between 0 (0%) and 100 (100%).
void pwm_driver_set(uint8_t channel, uint8_t value);

/**
 * Update PWM output for each channel
 * This function is called periodically.
 * It checks the status of each pwm channel and decides whether to turn it on or
 * off.
 *
 * @warning This assumes that pwm_driver_init() has been called for each channel
 * before this function is called.
 *
 * No return
 */
void pwm_driver_update(void);

#endif
