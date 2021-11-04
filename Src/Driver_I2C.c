#include "Driver_I2C.h"

void I2C_Init(uint32_t ClockSpeed, uint32_t OwnAddress) {
	
	// Déclaration GPIO
	MyGPIO_Struct_TypeDef GPIO_SCL;
	MyGPIO_Struct_TypeDef GPIO_SDA;
	
	// Reset des registres I2C
	RCC->APB1RSTR |=  RCC_APB1RSTR_I2C1RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
	I2C1->CR1 |= I2C_CR1_SWRST; 
	I2C1->CR1 &= ~I2C_CR1_SWRST; 
	
	// Initialisation des GPIO
	GPIO_SCL.GPIO = GPIOB;
	GPIO_SCL.GPIO_Pin = 6;
	GPIO_SCL.GPIO_Conf = AltOut_Ppull;
	GPIO_SDA.GPIO = GPIOB;
	GPIO_SDA.GPIO_Pin = 7;
	GPIO_SDA.GPIO_Conf = AltOut_Ppull;
	
	MyGPIO_Init(&GPIO_SCL);
	MyGPIO_Init(&GPIO_SDA);
	
	
	
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;
	
	I2C1->CR1 |= I2C_CR1_PE;     // Peripheral Enable
	I2C1->CR2 |= I2C_CR2_FREQ_1;
  I2C1->CCR |= ClockSpeed;
	//I2C1->OAR1 |= OwnAddress;
}
