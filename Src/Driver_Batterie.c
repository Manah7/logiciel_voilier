#include "Driver_Batterie.h"

MyGPIO_Struct_TypeDef gpio;

void Init_Batterie(void)
{
	gpio.GPIO = GPIOB;
	gpio.GPIO_Conf = In_Analog;
	gpio.GPIO_Pin = 0;
	MyGPIO_Init(&gpio);
	
	configADC1(8);
}

int Get_Valeur_Batterie(void)
{
	return ((getADC1Value() * 12000)/4095);
}

int Is_Batterie_Faible(int valeur)
{
	// l'ADC retournant une valeur sur 12 bits,
	// on se retrouve avec des valeurs comprises entre
	// 0 et 4095 (2^12=4096)
	// donc on a vBatt = (valADC * 12)/4095
	return ((getADC1Value() * V_BAT) / VALEUR_MAX_ADC) < 11.0;
}
