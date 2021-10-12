#include "Driver_ADC.h"

int nombreChannel = 1;

void configADC1(int channel){
    //nombreChannel++;
    // On configure la clock ADC1
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // On réduit la fréquence pour l'ADC
    
    // On active l'ADC (ADC_CR2_ADON)
    ADC1->CR2 |= (0x01 << 0);
    
    ADC1->SQR1 &= ~((~(nombreChannel-1)&(0xF)) << 20);
    ADC1->SQR1 |= (nombreChannel-1)<<20;
    ADC1->SQR3 |= channel << ((nombreChannel-1)*5);
}

void calibrateADC1() {
	// Calibration
	ADC1->CR2 |= ADC_CR2_CAL;
	while (ADC1->CR2 & ADC_CR2_CAL);
}

void setExternalTriggerADC1(){
	//On setup l'external trigger sur Timer 3 TRGO event
  ADC1->CR2 |= (0x1<<(2+17));

	//On active l'external trigger
	ADC1->CR2 |= (0x1<<20);
}

int getADC1Value(){
	// ADON := 1 --> lancement conversion
  ADC1->CR2 |= ADC_CR2_ADON;
	
	// On attend SR.EOC à 1
  while(!(ADC1->SR & ADC_SR_EOC)) {};
	
	// Remise à zéro de EOC
  ADC1->SR &= ~ADC_SR_EOC;
      
	// Lecture
  return ADC1->DR & ~((0x0F) << 12);
}
