#ifndef BATTERIE_H
#define BATTERIE_H

#include "Driver_ADC.h"
#include "Driver_GPIO.h"

#define V_BAT 12
#define VALEUR_MAX_ADC 4095

/*
	Driver pour la gestion de la batterie
	PINs utilisées :
	- 1 PIN d'entrée pour l'ADC : PB0
*/

/* Initialise le driver */
void Init_Batterie(void);

/* Retourne la valeur de tension renvoyée par la batterie */
int Get_Valeur_Batterie(void);

/* Indique si la tension de la batterie est trop faible (< 11V)*/
int Is_Batterie_Faible(void);

#endif
