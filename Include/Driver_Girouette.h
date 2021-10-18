#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"
#include "Driver_Timer.h"
#include <stdlib.h>

/*
	Driver pour la gestion de la girouette
	PINs utilisées:
		- 2 PINs sur un Timer (pour A et B)
			- TIM2_CH1 : PA0 (A)
			- TIM2_CH2 : PA1 (B)
		- 1 PIN quelconque (pour I, le zero)
*/

/* Initialisation de la girouette et de l'interruption liée à la détection du zéro */
void Init_Girouette(void);

/* Lancement du timer et de la prise des mesures */
void Start_Mesure_Girouette(void);

/* Arrêt du timer et de la prise de mesures */
void Stop_Mesure_Girouette(void);

/* Retourne la valeur de l'angle de la girouette */
int Get_Angle(void);

/* handler d'interruption de remise à zéro */
void EXTI2_IRQHandler(void);

#endif
