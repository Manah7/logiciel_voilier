#include "Driver_GPIO.h"


void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	
	if (GPIOStructPtr->GPIO_Pin < 8) {
		GPIOStructPtr->GPIO->CRL &= ~(0xF << 4 * GPIOStructPtr->GPIO_Pin);
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << 4 * GPIOStructPtr->GPIO_Pin);
	} else {
		GPIOStructPtr->GPIO->CRH &= ~(0xF << 4 * (GPIOStructPtr->GPIO_Pin-8));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << 4 * (GPIOStructPtr->GPIO_Pin - 8));
	}
}

int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	return GPIO->IDR & (0x01 << GPIO_Pin);
}

void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->BSRR |= (0x01 << GPIO_Pin) ;
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->BSRR |= (0x01 << GPIO_Pin) << 16 ;
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= (0x01 << GPIO_Pin);
}

