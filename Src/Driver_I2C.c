#include "Driver_I2C.h"
#define RTC_ADDRESS 1101000

void I2C_Init(uint32_t ClockSpeed, uint32_t OwnAddress) {
	
	// Déclaration GPIO
	MyGPIO_Struct_TypeDef GPIO_SCL;
	MyGPIO_Struct_TypeDef GPIO_SDA;
	
	// Reset des registres I2C
	RCC->APB1RSTR |=  RCC_APB1RSTR_I2C1RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;
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
	
	
	
	
	I2C1->CR1 |= I2C_CR1_PE;     // Peripheral Enable
	I2C1->CR2 |= I2C_CR2_FREQ_1;
  I2C1->CCR |= ClockSpeed;
	//I2C1->OAR1 |= OwnAddress;
}

void I2C_START(uint16_t mode) {
	while((I2C1->SR1 & I2C_SR2_BUSY)!=0x0000) {}
	I2C1->CR1 |= I2C_CR1_START;
	while ((I2C1->SR1 & I2C_SR1_SB) != 0x0000){}
	I2C1->DR |= (RTC_ADDRESS <<1) | mode;  //On met l'adresse dans la mémoire et on ajoute 1 a droite pour se placer en mode lecture 
	while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {}
	I2C1->SR1 &= (~I2C_SR1_ADDR); 
	
}
