#include "Driver_RTC.h"

uint32_t I2C_getdata(uint32_t Register_address, uint16_t device_address) {
	I2C_START(0);
	I2C1->DR &= 0xFF00;
	I2C1->DR |= Register_address;
	I2C1->CR1 |= I2C_CR1_STOP;
	
	I2C_START(1);
	I2C1->CR1 |= I2C_CR1_ACK;
	char tab[6];
	for (int i=0;i<6;i++){
		while((I2C1->SR1 & I2C_SR1_BTF) == 0) {}
		tab[i]=I2C1->DR;
	}
	
}