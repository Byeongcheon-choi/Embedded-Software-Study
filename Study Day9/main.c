# include "stm32f3xx.h" 

#define PROI_TIM3 3 /* set priority */
#define PROI_TIM4 4


void DELAYMODE(int a);

int main(void)
{
	__disable_irq();
	RCC->AHBENR |= 0X00020000; /*enable GPIOA clock */
	RCC->AHBENR |= 0X00040000; /*enable GPIOB clock */
	
	GPIOA->MODER &= ~0X00000C00; /* clear PA5 */
	GPIOA->MODER |=  0X00000400; /* Set PA5 output*/
	GPIOA->MODER &= ~0X000003C0; /* clear PB3,4 */
	GPIOA->MODER &=  0X00000140; /* Set PB3,4 output */
	
	RCC->APB1ENR |=  0X00000020; /*TIM3 enable */
	RCC->APB1ENR |=  0X00000040; /*TIM4 enable */
	
	TIM3->PSC = 1000-1; /*TIM3 setting */
	TIM3->ARR = 15500-1;
	TIM3->CR1 = 1;
	TIM3->DIER = 1;
	
	TIM4->PSC = 1000-1; /*TIM4 setting */
	TIM4->ARR = 1562-1;
	TIM4->CR1 = 1;
	TIM4->DIER = 1;
	
	NVIC_SetPriority(TIM3_IRQn,PROI_TIM3); /* set priority*/
	NVIC_EnableIRQ(TIM3_IRQn); /*trigger Interrupt */
	
	NVIC_SetPriority(TIM4_IRQn,PROI_TIM4); /* set priority */
	NVIC_EnableIRQ(TIM4_IRQn); /*trigger Interrupt */
	
	__enable_irq();
	
	while(1){
	}
	
}

void TIM3_IRQHandler(void){ /* In the case of triggerring TIM3 */
	GPIOB->BSRR |= 0X00000008;
	DELAYMODE(500);
	GPIOB->BSRR |= 0X00000008 <<16;
	DELAYMODE(500);
	TIM3->SR=0;
}

void TIM4_IQRHandler(void){ /* In the case of triggering TIM4, but TIM3 has higher priority, So this one is not operating. */
	GPIOA->BSRR |= 0X00000020;
	GPIOA->BSRR |= 0X00000020;
	DELAYMODE(25);
	
	GPIOA->BSRR |= 0X00000020 << 16;
	GPIOA->BSRR |= 0X00000020 << 16;
	
	TIM4->SR = 0;
	
}
void DELAYMODE(int a)
{
	for(;a>0;a--)
		for(int i =0; i < 3195;i++);
}




