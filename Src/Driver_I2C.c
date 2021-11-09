#include "Driver_I2C.h"

void I2C_Init(uint32_t ClockSpeed) {
	
	// Déclaration GPIO
	MyGPIO_Struct_TypeDef GPIO_SCL;
	MyGPIO_Struct_TypeDef GPIO_SDA;
	
	// Reset des registres I2C
	RCC->APB1RSTR |=  RCC_APB1RSTR_I2C1RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;
	I2C1->CR1 |= I2C_CR1_SWRST; 
	I2C1->CR1 &= ~I2C_CR1_SWRST; 
	
	// Initialisation des GPIO
	GPIO_SCL.GPIO = GPIOB;
	GPIO_SCL.GPIO_Pin = 6;
	GPIO_SCL.GPIO_Conf = AltOut_Ppull;
	GPIO_SDA.GPIO = GPIOB;
	GPIO_SDA.GPIO_Pin = 7;
	GPIO_SDA.GPIO_Conf = AltOut_Ppull;
	
	MyGPIO_Init(&GPIO_SCL);
	MyGPIO_Init(&GPIO_SDA);
	
	I2C1->CR1 |= I2C_CR1_PE;     // Peripheral Enable
	I2C1->CR2 |= I2C_CR2_FREQ_1;
  I2C1->CCR |= ClockSpeed;  //100kHz
}

void I2C_getBytes(char Register_address, char Device_adress, char * tab){
	//On envoie un start
	I2C_START(0, Device_adress);
	//On mets l'adresse du registre dans DR (sans toucher au bits réservés)
	I2C1->DR = (I2C1->DR & 0xFF00) | (0xFF & Register_address);
	//On attend un ack
	while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {}
	//On fait un stop puis un start en lecture
	I2C1->CR1 |= I2C_CR1_STOP;
	I2C_START(1, Device_adress);
	//On attend l'ACK
	while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {}
	
	//On active l'ACK automatique
	I2C1->CR1 |=  I2C_CR1_ACK;
	int i;
		for(i=0 ; i<sizeof(tab);i++){
			//Si c'est le dernier byte on envoie un NACK
			if(i==sizeof(tab)-1) I2C1->CR2 |=  I2C_CR2_LAST;
			//Attente de la réception d'une donnée
			while((I2C1->SR1 & I2C_SR1_BTF)==0) {}
				tab[i]=(char)I2C1->DR;
		}
		
		//On envoie un stop 
		I2C1->CR1 |= I2C_CR1_STOP;
		
}

void I2C_sendBytes(char Register_address, char Device_adress, char val){
	//On envoie un start
	I2C_START(0, Device_adress);
	//On mets l'adresse du registre dans DR (sans toucher au bits réservés)
	I2C1->DR = (I2C1->DR & 0xFF00) | (0xFF & Register_address);
	//On attend un ack
	while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {}
	//On fait un stop puis un start en lecture
	I2C1->CR1 |= I2C_CR1_STOP;
	//On attend l'ACK
	while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {}
		
	//On mets les donnée
	I2C1->DR = (I2C1->DR & 0xFF00) | (0xFF & val);
	
	
	//On attend un ACK
		while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {}
			
			
		//On envoie un stop 
		I2C1->CR1 |= I2C_CR1_STOP;
		
}

void I2C_START(uint16_t mode, uint16_t device_address) {
	while((I2C1->SR1 & I2C_SR2_BUSY)!=0x0000) {} //Bus libre?
	I2C1->CR1 |= I2C_CR1_START; //Génération bit start
	while ((I2C1->SR1 & I2C_SR1_SB) != 0x0000){} //bit start bien passé?
	I2C1->DR |= (RTC_ADDRESS <<1) | mode;  //On met l'adresse dans la mémoire et on ajoute 1 a droite pour se placer en mode lecture 
	while ((I2C1->SR1 & I2C_SR1_ADDR) == 0x0000) {} //Attente ACK
	I2C1->SR1 &= (~I2C_SR1_ADDR); //Fin de l'adressage 
	
}

