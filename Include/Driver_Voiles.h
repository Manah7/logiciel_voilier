#ifndef VOILES_H
#define VOILES_H

#include "stm32f10x.h"

/*
Driver pour le réglage des voiles
	PINs utilisés :
		- PA6
		Timer utilisé :
		- TIM3
		- TIM4 ?
*/

/* Réglage des voiles, de 0 à 255, 255 étant le plus bordé */
void Regler_Voiles(short r);

#endif 