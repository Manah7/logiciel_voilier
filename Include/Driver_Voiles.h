#ifndef VOILES_H
#define VOILES_H

#include "stm32f10x.h"

#include "Driver_Timer.h"
#include "Driver_GPIO.h"

/*
Driver pour le réglage des voiles
	PINs utilisés :
		- PA6 (D12)
		Timer utilisé :
		- TIM3, channel 1 (correspond à PA6)
*/

/* Initialise le module voiles. Regle les voiles en position 0. */
void Init_Voiles(void);

/* Réglage des voiles, de 0 à 100 (inclus), 100 étant le plus bordé */
void Regler_Voiles(short r);

#endif 
