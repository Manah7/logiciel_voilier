#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"

/* Besoin de deux pins : PB6(SCL) et PB7(SDA) */

/* Initialise le I2C des ports PB6/PB7
avec l'adresse du periphérique 1 */
void I2C_Init(uint32_t ClockSpeed, uint32_t OwnAddress1);

/*Renvoie le contenu stocké dans le registre d'addresse Register_address
du périphérique d'addresse Device_address*/
uint32_t I2C_getdata(uint32_t Device_address, uint32_t Register_address);

#endif
