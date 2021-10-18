#include "Driver_Plateau.h"

#define CHANNEL 1

MyTimer_Struct_TypeDef timerPlateau;
MyGPIO_Struct_TypeDef pa7;
MyGPIO_Struct_TypeDef pa8;

enum sens s; /* HORAIRE ou ANTI_HORAIRE */
short speed; /* 0 à 100 */

/*
Initialisation du timer pour la PWM du module
plateau. Les parametres de la PWN sont les suivants :
	- Fréquence > 20kHz
	- DC de 0 à 100%
	
Calcul du PSC et ARR :
	T_timer = T_horloge * prescaler[1 | 2^16] * autoreload
	autoreload = T_timer / (prescaler * T_horloge)
avec :
	T_horloge = 1/72M = 1/72000000
	T_Timer = 1/20000 = 0.00005
	0 < autoreload < 65535
	0 < prescaler < 65535
	
Application des valeurs :
	ARR = 225
	PSC = 16
*/

void Set_Rotation_Direction(enum sens csens) {
	s = csens;
}

void Set_Rotation_Speed(short cspeed) {
	speed = cspeed;
}

void Init_Plateau(void) {
	// Initialisation de la PWM
	timerPlateau.Timer = TIM1;
	timerPlateau.ARR = 225;
	timerPlateau.PSC = 16;
	
	MyTimer_Base_Init(&timerPlateau);
	MyTimer_Base_Start(timerPlateau.Timer);
	
	Set_Rotation_Direction(HORAIRE);
	
	MyTimer_PWM(timerPlateau.Timer, CHANNEL);
	Set_pwm_percentage(timerPlateau.Timer, 0, CHANNEL);
	
	// Initialisation du GPIO
	pa7.GPIO = GPIOA;
	pa7.GPIO_Conf = Out_Ppull;
	pa7.GPIO_Pin = 7;
	MyGPIO_Init(&pa7);
	
}

void Start_Rotation(void) {
	Set_pwm_percentage(timerPlateau.Timer, speed, CHANNEL);
}

