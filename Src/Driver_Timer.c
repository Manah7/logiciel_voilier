#include "Driver_Timer.h"
#include "Driver_GPIO.h"

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) {
	switch ((int)Timer->Timer){
		case (int)TIM1 :
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;
			Timer->Timer->BDTR |= TIM_BDTR_MOE ;
      break;
    case (int)TIM2 :
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;
      break;
    case (int)TIM3 :
      RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
      break;
    case (int)TIM4 :
      RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;
			break;
  }
	
	Timer->Timer->ARR = Timer->ARR;
  Timer->Timer->PSC = Timer->PSC;
}


void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio ){
	// Mise du bit UIE (registre DIER) à 1 --> déclanchement de l'int. par le timer
	Timer->DIER |= (1 << 0);
	
	switch ((int)Timer) {
		case (int)TIM1:
			// Configuration NVIC cf. doc p.198
			NVIC->ISER[0] |= (0x1 << 25);
			// Priorité
      NVIC->IP[25] = Prio;
    break;
    case (int)TIM2:
			NVIC->ISER[0] |= (0x1 << 28);
			NVIC->IP[28] = Prio;
    break;
    case (int)TIM3:
			NVIC->ISER[0] |= (0x1 << 29);
      NVIC->IP[29] = Prio;
    break;
    case (int)TIM4:
      NVIC->ISER[0] |= (0x1 << 30);
      NVIC->IP[30] = Prio;
    break;
  }
}


void (* pFncT1) (void);
void (* pFncT2) (void);
void (* pFncT3) (void);
void (* pFncT4) (void);


void Setup_Callback (void (* ptrFonction) (void), TIM_TypeDef * Timer)
{
	switch ((int)Timer) {
		case (int)TIM1:
			pFncT1 = ptrFonction;
    break;
    case (int)TIM2:
			pFncT2 = ptrFonction;
    break;
    case (int)TIM3:
			pFncT3 = ptrFonction;
    break;
    case (int)TIM4:
      pFncT4 = ptrFonction;
    break;
  }
}


void TIM1_UP_IRQHandler (void) {
	// Reset flag (Status register)
	TIM1->SR &= ~(1 << 0);
	// Appel du callback
	if (pFncT1 != 0) {
		(*pFncT1) ();
	}
} 

void TIM2_IRQHandler (void) {
	TIM2->SR &= ~(1 << 0);
	if (pFncT2 != 0) {
		(*pFncT2) ();
	}
} 

void TIM3_IRQHandler (void) {
	TIM3->SR &= ~(1 << 0);
	if (pFncT3 != 0) {
		(*pFncT3) ();
	}
} 

void TIM4_IRQHandler (void) {
	TIM4->SR &= ~(1 << 0);
	if (pFncT4 != 0) {
		(*pFncT4) ();
	}
} 
	

// PWM
void MyTimer_PWM(TIM_TypeDef * Timer , char Channel){
	MyGPIO_Struct_TypeDef gpio;
	gpio.GPIO_Conf = AltOut_Ppull;
	
	Timer->CCER |= TIM_CCER_CC1E;
	
	switch (Channel) {
		case (char) 1:
			// Setup des bits OC1M cf. doc p. 349
			Timer->CCMR1 &= ~(1 << 4);
			Timer->CCMR1 |= (1 << 5) | (1 << 6);
			Timer->CCMR1 &= ~((0x1<<0) | (0x1<<1)); //Set en output
		
			switch ((int)Timer){
				case (int)TIM1:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 8;
				break;
				case (int)TIM2:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 0;
				break;
				case (int)TIM3:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 6;
				break;
				case (int)TIM4:
					gpio.GPIO = GPIOB;
					gpio.GPIO_Pin = 6;
				break;
			}
		break;
		case (char) 2:
			Timer->CCMR1 &= ~(1 << (4 + 8));
			Timer->CCMR1 |= (1 << (5 + 8)) | (1 << (6 + 8));
			Timer->CCMR1 &= ~(((0x1<<0) | (0x1<<1)) <<8);
		
			switch ((int)Timer){
				case (int)TIM1:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 9;
				break;
				case (int)TIM2:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 1;
				break;
				case (int)TIM3:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 7;
				break;
				case (int)TIM4:
					gpio.GPIO = GPIOB;
					gpio.GPIO_Pin = 7;
				break;
			}
		break;
		case (char) 3:
			Timer->CCMR2 &= ~(1 << 4);
			Timer->CCMR2 |= (1 << 5) | (1 << 6);
			Timer->CCMR2 &= ~((0x1<<0) | (0x1<<1));
		
			switch ((int)Timer){
				case (int)TIM1:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 10;
				break;
				case (int)TIM2:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 2;
				break;
				case (int)TIM3:
					gpio.GPIO = GPIOB;
					gpio.GPIO_Pin = 0;
				break;
				case (int)TIM4:
					gpio.GPIO = GPIOB;
					gpio.GPIO_Pin = 8;
				break;
			}
			
		break;
		case (char) 4:
			Timer->CCMR1 &= ~(1 << (4 + 8));
			Timer->CCMR1 |= (1 << (5 + 8)) | (1 << (6 + 8));
			
			switch ((int)Timer){
				case (int)TIM1:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 10;
				break;
				case (int)TIM2:
					gpio.GPIO = GPIOA;
					gpio.GPIO_Pin = 3;
				break;
				case (int)TIM3:
					gpio.GPIO = GPIOB;
					gpio.GPIO_Pin = 1;
				break;
				case (int)TIM4:
					gpio.GPIO = GPIOB;
					gpio.GPIO_Pin = 9;
				break;
			}
		break;
	}
	MyGPIO_Init(&gpio);
}

void Set_pwm_percentage(TIM_TypeDef * Timer, int pctg, char Channel){
	short cycle = Timer->ARR * pctg / 100;
	switch (Channel) {
		case (char) 1:
			Timer->CCR1 = cycle;
			break;
		case (char) 2:
			Timer->CCR2 = cycle;
			break;
		case (char) 3:
			Timer->CCR3 = cycle;
			break;
		case (char) 4:
			Timer->CCR4 = cycle;
			break;
	}
}


void Set_pwm_percentage_precise(TIM_TypeDef * Timer, int pdml, char Channel){
	short cycle = Timer->ARR * pdml / 10000;
	switch (Channel) {
		case (char) 1:
			Timer->CCR1 = cycle;
			break;
		case (char) 2:
			Timer->CCR2 = cycle;
			break;
		case (char) 3:
			Timer->CCR3 = cycle;
			break;
		case (char) 4:
			Timer->CCR4 = cycle;
			break;
	}
}



