#include "Driver_IMU.h"
#include "Driver_I2C.h"


int IsCapsizing(){	
	char valeurs[6];
	int x,y,z;
	double ratio;

	I2C_getBytes(0x32,IMU_ADDRESS,valeurs);
	x= valeurs[0] | (valeurs[1]<<8);
	y= valeurs[2] | (valeurs[3]<<8);
	z= valeurs[4] | (valeurs[5]<<8);
	
	ratio= (double)y/(double)z;
	
	//Si le ratio y/z est plus grand que tan(40°) on renvoie 1 (il y a un rouli)
	return (ratio >=  0.8490);
}


void Initialize_IMU(){
	I2C_Init(100000);
}