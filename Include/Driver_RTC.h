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

void RTC_init(void);

time RTC_gettime (void);

#endif
