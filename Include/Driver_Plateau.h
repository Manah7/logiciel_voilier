#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"
#include "Driver_Timer.h"

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

/* [[deprecated]] Initialise le module plateau */
void Init_Plateau();

/* [[deprecated]] Défini le sens de rotation */
void Set_Rotation_Direction(enum sens s);

/* [[deprecated]] Défini la vitesse de rotation, de 0 à 255 */
void Set_Rotation_Speed(short speed);

/* [[deprecated]] Commence la rotation */
void Start_Rotation();

/* [[deprecated]] Arrête la rotation */
void Stop_Rotation();

#endif 