/* Includes */
#include "main.h"
// LED driver
#include "led_driver.h"
// ESS helpers
#include "ess_helper.h"
// Loop delay
#include "loop_delay.h"
// PWM driver
#include "pwm_driver.h"

int main(void) {
  /* Initialize system */
  HAL_Init();
  /* Initialize peripherals on board */
  ess_helper_init();

  while (1) {
  }
}
