#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"

typedef struct {
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ; //numero de 0 a 15
	char GPIO_Conf ; // voir c i dessous
} MyGPIO_Struct_TypeDef ;


#define In_Floating 0x04
#define In_PullDown 0x0C
#define In_PullUp 0x08
#define In_Analog 0x00
#define Out_Ppull 0x01
#define Out_OD 0x05
#define AltOut_Ppull 0x09
#define AltOut_OD 0x0D


void MyGPIO_Init( MyGPIO_Struct_TypeDef * GPIOStructPtr ) ;
int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) ; 
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

#endif
