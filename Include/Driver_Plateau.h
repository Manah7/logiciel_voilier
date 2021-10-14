#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"

#include "Driver_Timer.h"
#include "Driver_GPIO.h"

/*
Driver pour la rotation du plateau
	PINs utilisés :
		- PA7 -> Pour la direction
		- PA8 -> Pour la PWM
	
		Timer utilisé :
		- TIM1, canal 1 (correspond à PA8)
*/

enum sens {
	HORAIRE, 
	ANTI_HORAIRE
};

/* [[deprecated]] Initialise le module plateau */
void Init_Plateau(void);

/* [[deprecated]] Défini le sens de rotation */
void Set_Rotation_Direction(enum sens s);

/* [[deprecated]] Défini la vitesse de rotation, de 0 à 100 */
void Set_Rotation_Speed(short speed);

/* [[deprecated]] Commence la rotation */
void Start_Rotation(void);

/* [[deprecated]] Arrête la rotation */
void Stop_Rotation(void);

#endif 