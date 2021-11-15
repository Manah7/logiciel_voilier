#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Driver_Voiles.h"
#include "Driver_Girouette.h"
#include "Driver_Plateau.h"
#include "Driver_Communication.h"
#include "Driver_Batterie.h"
#include "Driver_IMU.h"
#include "Driver_RTC.h"

#define CLOCK 72000000
#define MAX_BORDAGE 100


// [[debug]] Variable de debug
int v;
int t;

// Dernier angle mesuré
int angle;

// Callback appelé lors de la réception d'un message
void reception(char par){
	Send_Message("[REGLAGE]\n");
	Set_Rotation_Speed((int) par);
	Start_Rotation();
}

// Fonction d'ajustement des voiles en fonction de l'orientation du vent
int angle_to_bordage(int angle) {
	if (angle > 359) {
		return (angle-359)*100000/359*MAX_BORDAGE/100000;
	} else {
		return (360-angle)*100000/359*MAX_BORDAGE/100000;
	}
}

void envoyer_allure(int angle) {
	if (angle <= 80 || angle >= 738) {
		Send_Message("Je suis au PRES !\n");
	} else if (angle <= 140 || angle >= 678) {
		Send_Message("Je suis au BON PLEIN !\n");
	} else if (angle <= 220 || angle >= 598) {
		Send_Message("Je suis au TRAVERS !\n");
	} else if (angle <= 300 || angle >= 528) {
		Send_Message("Je suis au LARGUE !\n");
	} else {
		Send_Message("Je suis VENT ARRIERE !\n");
	}
}

// Point d'entrée
int main () {	
	// Configuration de l'horloge
  RCC->APB2ENR |=(0x01 << 2)|(0x01 << 3)|(0x01 << 4);
	
	// Initialisation des composants
	Init_Plateau();
	Init_Voiles();
	Init_Girouette();
	Init_Batterie();
	Start_Mesure_Girouette();
	Initialize_IMU();
	
	// Lancement de la communication USART
	Config_UART(USART3);
	Init_Message_Receiving(&reception);

	while (1) {
		// Réglage des voiles en fonction de l'allure
		angle = Get_Angle();
		envoyer_allure(angle);
		Regler_Voiles(angle_to_bordage(angle));
		
		// [[debug]]
		//t = gettime().second;
		
		// [[debug]] 
		v = Get_Valeur_Batterie();
		
		// Verification de la tension batterie
		if (Is_Batterie_Faible()) {
			Send_Message("Batterie faible !\n");
		}
		
		// [[deprecated]] Vérification de l'inclinaison
		/*
		if (IsCapsizing()){
			Send_Message("AAAAAAAAAAAAAAAAAAAH!!!!\n");
		}
		*/
	}
}
