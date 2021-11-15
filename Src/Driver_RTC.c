#include "Driver_RTC.h"
#include <stdlib.h>

time gettime(void){
	time t;
	char* data = malloc(7);  // on a besoins de 7 octets pour connaitre la date
	I2C_getBytes(0, RTC_ADDRESS, data);
	t.second = (data[0] & 0x0F) + 10*((data[0]>>4)&0x7);
	t.minute = (data[1] & 0x0F) + 10*(data[1]>>4);
	t.hour = (data[2] & 0x0F) + 10*((data[2]>>4)&0x3);
	t.weekday = data[3];
	t.day = (data[4] & 0x0F) + 10*(data[4]>>4);
	t.month = (data[5] & 0x0F) + 10*(data[5]>>4);
	t.year = (data[6] & 0x0F) + 10*(data[6]>>4);
	return t;
}
