#ifndef RTC_H
#define RTC_H

#include "stm32f10x.h"
#include "Driver_I2C.h"

typedef struct{
    int year;
    int month;
    int day;
		int weekday;
		int hour;
    int minute;
    int second;
} time;


time RTC_gettime (void);

#endif
