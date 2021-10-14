#ifndef RTC_H
#define RTC_H

#include "stm32f10x.h"

typedef struct{
    int year;
    int month;
    int day;
    int minute;
    int second;
} time;

void RTC_init();

time RTC_gettime ();

#endif