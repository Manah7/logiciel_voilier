#include "Driver_Voiles.h"

#define CHANNEL 1

MyTimer_Struct_TypeDef timerVoiles;
MyGPIO_Struct_TypeDef pa6;

/* 
Fonction interne. Ajuste un short pour correspondre à
une valeur entre 5 et 10 % (entre 1 et 2 ms, cycle 20ms).
*/ 
int Convert_to_Pc(short v) {
	return ((int) v + 5) * 100;
}

/*
Initialisation du timer pour la PWM du module
voiles. Les parametres de la PWN sont les suivants :
	- Une pulsation toutes les 20 ms
	- La durée d'impulsion est comprise entre 1 et 2 ms
	
Calcul du PSC et ARR :
	T_timer = T_horloge * prescaler[1 | 2^16] * autoreload
	autoreload = T_timer / (prescaler * T_horloge)
avec :
	T_horloge = 1/72M = 1/72000000
	T_Timer = 20 ms = 0.02
	0 < autoreload < 65535
	0 < prescaler < 65535
	
Application des valeurs :
	ARR = 1381
	PSC = 1042
*/
void Init_Voiles(void) {
	timerVoiles.Timer = TIM3;
	timerVoiles.ARR = 1381;
	timerVoiles.PSC = 1042;
	
	MyTimer_Base_Init(&timerVoiles);
	MyTimer_Base_Start(timerVoiles.Timer);
	
	MyTimer_PWM(timerVoiles.Timer, CHANNEL);
	Set_pwm_percentage_precise(timerVoiles.Timer, Convert_to_Pc(0), CHANNEL);
}

/*
	Regle la PWM entre 5% (1ms) et 10% (2ms)
*/
void Regler_Voiles(short r) {
	Set_pwm_percentage_precise(timerVoiles.Timer, Convert_to_Pc(r), CHANNEL);
}
