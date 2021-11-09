#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"

/* Besoin de deux pins : PB6(SCL) et PB7(SDA) */

/* Initialise le I2C des ports PB6/PB7
avec l'adresse du periphérique 1 */
void I2C_Init(uint32_t ClockSpeed, uint32_t OwnAddress1);

/* Lance la START condition pour une lecture (mode = 1) ou une écriture (mode = 0)*/
void I2C_START(uint16_t mode, uint16_t device_address);



#endif
