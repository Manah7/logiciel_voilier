#include "Driver_IMU.h"
#include "Driver_I2C.h"


void read(){	
	char valeurs[6];
	int x,y,z;

	I2C_getBytes(0x32,IMU_ADDRESS,valeurs);
	x= valeurs[0] | (valeurs[1]<<8);
	y= valeurs[2] | (valeurs[3]<<8);
	x= valeurs[4] | (valeurs[5]<<8);
	
}


void Initialize_IMU(){
	I2C_Init(100000);

	
}