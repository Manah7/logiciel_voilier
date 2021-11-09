#include "Driver_Batterie.h"

MyGPIO_Struct_TypeDef gpio;

void Init_Batterie(void)
{
	gpio.GPIO = GPIOB;
	gpio.GPIO_conf = In_Analog;
	gpio.GPIO_Pin = 0;
	MyGPIO_Init(&gpio);
	
	configADC1(8);
}

int Get_Valeur_Batterie(void)
{
	return getADC1VALUE();
}

int Is_Batterie_Faible(int valeur);