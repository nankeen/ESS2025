#include "pwm_driver.h"
#include "led_driver.h"
#include <assert.h>

// Encapsulate the state of the PWM driver
struct pwm
{
  uint32_t counter;
  uint32_t levels[PWM_CHANNELS];
  LED_t * led_channels[PWM_CHANNELS];
};

// we declare the state as static so it only has file scope and cannot be accessed externally
// this makes the assumption that we only have one pwm_driver instance in the system
static struct pwm state;

// initialize the pwm driver

void pwm_driver_init(LED_t * channels[])
{
  // Start counter at zero
  state.counter = 0;
  // Set all channels to off (i.e. compare value of 0)

  for (int i = 0; i < PWM_CHANNELS; i++) {
    state.levels[i] = 0;
  }
  // store the pointers for each led driver
  for (int i = 0; i < PWM_CHANNELS; i++) {
    if (channels[i] != 0) {
      state.led_channels[i] = channels[i];
    }
  }
}

void pwm_driver_set(uint8_t channel, uint8_t value)
{
  // bounds check
  assert(value <= PWM_MAX_DUTY_CYCLE);
  assert(channel < PWM_CHANNELS);
  // update the compare register depending on which channel is selected
  state.levels[channel] = value;
}

void pwm_driver_update(void)
{
  for (int i = 0; i < PWM_CHANNELS; i++) {
    if (state.levels[i] > state.counter) {
      led_on(state.led_channels[i]);
    } else {
      led_off(state.led_channels[i]);
    }
  }
  // Update Ch0: if compare value is greater than counter, turn on, else turn
  // off
  // Update Ch1
  // Update Ch2
  // Update Ch3
  // update counter value
  if (state.counter++ > PWM_MAX_DUTY_CYCLE) {
    state.counter = 0;
  }
}
