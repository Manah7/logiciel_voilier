#include "Driver_Batterie.h"

#define SEUIL 11500

MyGPIO_Struct_TypeDef gpio;

void Init_Batterie(void)
{
	gpio.GPIO = GPIOB;
	gpio.GPIO_Conf = In_Analog;
	gpio.GPIO_Pin = 0;
	MyGPIO_Init(&gpio);
	
	// continuous mode
	ADC1->CR2 |= ADC_CR2_CONT;
	
	configADC1(8);
	calibrateADC1();
}

int Get_Valeur_Batterie(void)
{
	return ((getADC1Value() * (3300*13)/4095));
}

int Is_Batterie_Faible()
{
	// l'ADC retournant une valeur sur 12 bits,
	// on se retrouve avec des valeurs comprises entre
	// 0 et 4095 (2^12=4096)
	// donc on a vBatt = (valADC * 12)/4095
	return Get_Valeur_Batterie() < SEUIL;
}
