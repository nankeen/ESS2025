/**
 *	I2C Driver
 *
 *	@author
 *	@version 	v1.1
 *	@ide		STM32CubeIDE
 *	@license	GNU GPL v3
 */
#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>

// Initialize the I2C
void I2CAcc_Init(void);

// Send a byte on I2C
// @param address address of register to write to
// @param data to send
void I2CAcc_Send(uint8_t address, uint8_t data);

// Receive a byte on I2C
// @param address address of register to read from
uint8_t I2CAcc_Get(uint8_t address);

#endif
