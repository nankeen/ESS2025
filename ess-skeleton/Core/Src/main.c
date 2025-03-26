/* Includes */
#include "main.h"
// LED driver
#include "led_driver.h"
// ESS helpers
#include "ess_helper.h"
// PWM driver
#include "pwm_driver.h"
// Hardware timers
#include "stm32f4xx_hal_tim.h"
// Hardware interrupt timers
#include "stm32f4xx_it.h"

// Initialize Timer 4
TIM_HandleTypeDef TIM_Handle; //define a handle

// Initialize Timer 4 for interrupts
void TMR4_Init_ISR(void) {
  /* Enable clock for TIM4 */
  __TIM4_CLK_ENABLE();
  TIM_Handle.Instance = TIM4; //Same timer whose clocks we enable
  // timer_tick_frequency = 16000000 / (0 + 1) = 16000000
  TIM_Handle.Init.Prescaler = 0;
  /* Count up */
  TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  /*
  Set timer period when it must reset
  First you have to know max value for timer
  In our case it is 16bit = 65535
  Frequency = timer_tick_frequency / (TIM_Period + 1)
  If you get Period larger than max timer value (in our case 65535),
  you have to choose larger prescaler and slow down timer tick frequency
  */
  TIM_Handle.Init.Period = 1599;
  TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TIM_Handle.Init.RepetitionCounter = 0;
  TIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  /* Initialize TIM4 */
  HAL_TIM_Base_Init(&TIM_Handle);
  /* Start count on TIM4 */
  HAL_TIM_Base_Start_IT(&TIM_Handle);
  /* Enable the TIM4 gloabal Interrupt */
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

// This is triggered when the counter overflows
void TIM4_IRQHandler(void) {
  // In case other interrupts are also running
  if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET) {
    if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET) {
      __HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
      pwm_driver_update();
    }
  }
}

// GPIO port D
#define PORTD ((volatile uint32_t *)0x40020C14)

int main(void) {
  /* Initialize system */
  HAL_Init();
  /* Initialize peripherals on board */
  ess_helper_init();

  // Setup LEDs
  LED_t leds[PWM_CHANNELS];

  led_init(&leds[0], PORTD, 12);
  led_init(&leds[1], PORTD, 13);
  led_init(&leds[2], PORTD, 14);
  led_init(&leds[3], PORTD, 15);

  LED_t *leds_ptr[] = {&leds[0], &leds[1], &leds[2], &leds[3]};

  // set up the pwm driver
  pwm_driver_init(leds_ptr);

  // set brightness values
  uint32_t levels[] = {75, 50, 25, 0};
  for (uint32_t i = 0; i < sizeof(levels) / sizeof(uint32_t); i++) {
    levels[i] += 1;
    levels[i] %= 100;
    pwm_driver_set(i, levels[i]);
  }

  TMR4_Init_ISR();
  while (1) {
  }
}
