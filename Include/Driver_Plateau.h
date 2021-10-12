#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"

/*
Driver pour la rotation du plateau
	PINs utilisés :
		- PA7
		- PA8
		- PB6 ?
		Timer utilisé :
		- TIM3
		- TIM4 ?
*/

enum sens {
	HORAIRE, 
	ANTI_HORAIRE
};

/* Défini le sens de rotation */
void Set_Rotation_Direction(enum sens s);

/* Défini la vitesse de rotation, de 0 à 255 */
void Set_Rotation_Speed(short speed);

/* Commence la rotation */
void Start_Rotation();

/* Arrête la rotation */
void Stop_Rotation();

#endif 