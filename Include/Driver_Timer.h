#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct {
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef ;

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer );

void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio ); 

void Setup_Callback (void (* ptrFonction) (void), TIM_TypeDef * Timer);

void MyTimer_PWM(TIM_TypeDef * Timer , char Channel);

/* Regle le pourcentage de la PWM */
void Set_pwm_percentage(TIM_TypeDef * Timer, int pctg, char Channel);

/* [[deprecated]] Version plus précise de Set_pwm_percentage, prenant un entier entre 0 et 10000 */
void Set_pwm_percentage_precise(TIM_TypeDef * Timer, int pdml, char Channel);

#define MyTimer_Base_Start(Timer) (Timer->CR1 |= ( 1 << 0))
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~( 1 << 0))

#endif 
