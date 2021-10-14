#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"

/* Besoin de deux pins : PB6(SCL) et PB7(SDA) */

/* Initialise le I2C des ports PB6/PB7
avec l'adresse du periphérique 1 et 2 */
void I2C_Init(uint32_t ClockSpeed, uint32_t OwnAddress1, uint32_t AddressingMode, uint32_t OwnAddress2);

void I2C_Adress();

#endif
