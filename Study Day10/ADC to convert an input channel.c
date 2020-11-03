#include "stm32f3xx.h"

int main(void){
	
	int result;
	
	RCC->AHBENR |= 1 <<17;
	
	GPIOA->MODER &= ~0X00000C00;
	GPIOA->MODER |=  0X00000400;
	
	RCC->AHBENR |= 1 <<17;
	
	GPIOA->MODER |= 0XC; /* Analog input for PA1 */
	
	RCC->AHBENR |= 1 << 28;
	ADC1->CR2 =| 0; /* continuous converion -> free running mode */
	ADC1->CR2 =| 1; /* Enable ADC */
	ADC1->SQR1 = 0; /* Set sequence length */
	ADC1->SQR1 |= 1<<6; /* start CH 1*/
	
	while(1)
	{
		ADC1->CR2 |= 4; /* start Conversion */
		while(!(ADC1->ISR & 4)) {} /* Until conversion complete*/
		result = ADC1->DR; /* Get the Conversion result */
		if( result & 0x100)
			GPIOA->BSRR = 2<<1; /* Turn LED on */
		else
			GPIOA->BSRR = 2<<16; /* Turn LED off */
	}
	
	
}