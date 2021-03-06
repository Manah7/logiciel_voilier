#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"
#define RTC_ADDRESS  0x68 //1101000
#define IMU_ADDRESS 0x53

/* Besoin de deux pins : PB6(SCL) et PB7(SDA) */

/* Initialise le I2C des ports PB6/PB7 */
void I2C_Init(void);

/* Lance la START condition pour une lecture (mode = 1) ou une écriture (mode = 0)*/
void I2C_START(uint16_t mode, uint16_t device_address);

/* Recupere les données situées dans le registre d'adresse Register_address du
périphérique d'adresse Device_address. Le nombre d'octets récupérés correspond
à la taille de tab*/
void I2C_getBytes(char Register_address, char Device_address, char * tab);


#endif
