#include "stm32f3xx.h"

int main(void)
{
	int data =0; /* set variable */
	RCC->AHBENR |= 1 << 17; /* GPIOA enable  */
	GPIOA->MODER |= 00000300; /*  PA4 set analog(Cause this pin is for DAC output pin) */
	
	RCC->APB1ENR |= 1<<29; /* DAC clock Enable */
	DAC->CR |= 1; /* DAC channel 1 enable  */
	
	while(1)
	{
		DAC->DHR12R1 = data++ & 0x0fff; /* Using Channel 1 12bit and Right Aligned data */
	}
}



	