#include "Driver_Communication.h"
USART_TypeDef * UART;
//à mettre dans le .c
void (* pFncUART) (char);

void SendChar(char character){
	//Tant que la transmission précédente n'est pas finit (tant que le bit TC de SR est à 0)
	while(((UART->SR>>6)&0x1)==0x0);
	UART->DR = character;
}

void Config_UART(USART_TypeDef * UART_par){
	MyGPIO_Struct_TypeDef gpioRX, gpioTX;
	
	UART = UART_par;

	//On configure les GPIO :	
	gpioTX.GPIO_Conf = AltOut_Ppull;
	gpioRX.GPIO_Conf = In_Floating;
	switch ((int)UART){
				case (int)USART2:
					gpioTX.GPIO = GPIOA;
					gpioTX.GPIO_Pin = 2;
					gpioRX.GPIO = GPIOA;
					gpioRX.GPIO_Pin = 3;
				break;
				case (int)USART3:
					gpioTX.GPIO = GPIOB;
					gpioTX.GPIO_Pin = 10;
					gpioRX.GPIO = GPIOB;
					gpioRX.GPIO_Pin = 11;
				break;
	}
	MyGPIO_Init(&gpioTX);
	MyGPIO_Init(&gpioRX);

	//On active la clock :
	switch ((int)UART){
		case ((int)USART2) : 
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			//RCC->APB1ENR |= (0x1 <<17);
		break;
		case ((int)USART3) : 
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
			//RCC->APB1ENR |= (0x1 << 18);
		break;
	}
	// [M] On met à 0 le bit M (12) de CR1 pour définir la taille des mots à 8
	UART->CR1 &= ~(0x1 << 12); 
	
	// [UE] On met à 1  le bit UE (13) de CR1 pour activer l'UART
	UART->CR1 |= (0x1 <<13);
	
	// [STOP] On configure un stop bit : cf https://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Datasheet.pdf page 10
	// -> on met à 0 les bits STOP (12 et 13) de CR2
	UART->CR2 &= ~((0x1<< 12) | (0x1 << 13));
	
	// UART BaudRate 9600 (cf prof)
	// -> Comme la clock du USART3 est à 36 MHz il faut la valeur 234,375 dans le registre de baudRate
	//-> cf p.804
	UART->BRR |= (234 <<4);
	UART->BRR |= 6;
	
	// [TE] On mets à 1 le bit TE de CR1 pour envoyer une frame de première transmission
	UART->CR1 |= (0x1 << 3);
	
	// [TC]
	UART->SR |= (0x1 <<6);
}
void Send_Message(const char message[]){
	int i = 0;
	do{
		SendChar((char)message[i]);
		i++;
	}while( message[i]!='\0');
}

/*
void Init_Message_Sending(int delay){
	MyTimer_Struct_TypeDef Timer;
	
}*/

void Init_Message_Receiving(void (* ptrFonction) (char)){
	//On setup la fonction de callback
	pFncUART = ptrFonction;
	
	switch ((int)UART){
		case ((int)USART2) : 
			// Configuration NVIC cf. doc p.198
		  NVIC_EnableIRQ(USART2_IRQn);
		  NVIC_SetPriority(USART2_IRQn, 10);
			//NVIC->ISER[1] |= (0x1 << (38-32));
      //NVIC->IP[25] = 45;
		break;
		case ((int)USART3) : 
			NVIC_EnableIRQ(USART3_IRQn);
		  NVIC_SetPriority(USART3_IRQn, 11);
			//NVIC->ISER[1] |= (0x1 << (39-32));
      //NVIC->IP[25] = 46;
		break;
	}	
	// [RXNEIE] On active les interruption à la reception en mettant le bit RXNEIE de CR1 à 1 
	UART->CR1 |= (0x1<<5);
	
	// [RE] On lance la réception en mettant le bit RE de CR1 à 1: 
	UART->CR1 |= (0x1 <<2);
	
}

void USART2_IRQHandler(){
	//Si le bit RXNE de SR est à 1 (on a bien reçu une donnée) on appelle la fonction
	if((UART->SR>>6)&0x1){
		// [DR] On récupère le caratère dans DR
		pFncUART(UART->DR);
		//On remet le bit à 0
		UART->SR &= ~(0x1<<6);
	}
}
void USART3_IRQHandler(){
	// [RXNE]Si le bit RXNE de SR est à 1 (on a bien reçu une donnée) on appelle la fonction
	if((UART->SR>>6)&0x1){
		//On récupère le caratère dans DR
		pFncUART(UART->DR);
		//On remet le bit à 0
		UART->SR &= ~(0x1<<6);
	}
}


