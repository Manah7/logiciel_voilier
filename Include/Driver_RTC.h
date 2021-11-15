#ifndef RTC_H
#define RTC_H

#include "stm32f10x.h"
#include "Driver_I2C.h"

/* Structure de donnée contenant la date (année, mois, jour, jour de la semaine, heure, minute et seconde)*/
typedef struct{
    int year;
    int month;
    int day;
		int weekday;
		int hour;
    int minute;
    int second;
} time;


time gettime (void);

#endif
