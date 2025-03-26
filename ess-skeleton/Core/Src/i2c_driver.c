#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#define I2Cx_TIMEOUT_MAX                        0xA000 /*<! The value of the maximal timeout for I2C waiting loops */

I2C_HandleTypeDef I2cHandle;

/**
  * @brief  I2Cx MSP Init.
  * @param  hi2c: I2C handle
  */
static void I2Cx_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable the I2C peripheral */
  __HAL_RCC_I2C1_CLK_ENABLE();

  /* Enable SCK and SDA GPIO clocks */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* I2Cx SD1 & SCK pin configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_9 | GPIO_PIN_6;
  GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Alternate = GPIO_AF4_I2C1;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Force the I2C peripheral clock reset */
  __HAL_RCC_I2C1_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  __HAL_RCC_I2C1_RELEASE_RESET();

  /* Enable and set I2Cx Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

  /* Enable and set I2Cx Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
}

/**
  * @brief  I2Cx Bus initialization.
  */
void I2CAcc_Init(void)
{
  if(HAL_I2C_GetState(&I2cHandle) == HAL_I2C_STATE_RESET)
  {
    I2cHandle.Instance = I2C1;
    I2cHandle.Init.OwnAddress1 =  0x43;
    I2cHandle.Init.ClockSpeed = ((uint32_t) 100000);
    I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    I2cHandle.Init.OwnAddress2 = 0x00;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;

    /* Init the I2C */
    I2Cx_MspInit(&I2cHandle);
    HAL_I2C_Init(&I2cHandle);
  }
}

/**
  * @brief  Writes a value in a register of the device through BUS.
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written
  */
void I2CAcc_Send(uint8_t Reg, uint8_t Value)
{
  uint16_t Addr = 0b0011001 << 1;

  HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2Cx_TIMEOUT_MAX);

}

/**
  * @brief  Reads a register of the device through BUS.
  * @param  Reg: The target register address to write
  * @retval Data read at register address
  */
uint8_t I2CAcc_Get(uint8_t Reg)
{
  uint16_t Addr = 0b00110010;
  uint8_t value = 0;
  HAL_I2C_Mem_Read(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, I2Cx_TIMEOUT_MAX);

  return value;
}
