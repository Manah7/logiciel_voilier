#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"

/*
	Driver pour la gestion de la girouette
	PINs utilisées:
		- 2 PINs sur un Timer (pour A et B)
		- 1 PIN quelconque (pour I, le zero)
*/

/* Initialisation de la girouette et des pins correspondant aux entrées A, B et I */
void Init_Girouette(char GPIO_Pin_A, char GPIO_Pin_B, char GPIO_Pin_I);

/* Lancement du timer et de la prise des mesures */
void Start_Mesure_Girouette();

/* Retourne la valeur de l'angle de la girouette */
int Get_Angle();

#endif