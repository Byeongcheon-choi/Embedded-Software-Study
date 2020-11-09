#include "stm32f3xx.h"

void SPI_Init(void);
void SPI_Start(unsigned char a);
void Delaymode(int);

int main(void){

	SPI_Init();
	
	while(1){
		for(char i = 'A';i <= 'Z'; i++){
			SPI_Start(i); /* write the letter */
			Delaymode(100);
		}
	}
}

void SPI_Init(void){
	RCC->AHBENR |= 1 << 17; /*GPIOA clock enable */
	RCC->APB2ENR |= 1 << 12; /* SPI clock enalbe*/
	
	GPIOA->MODER &= ~0X0000CC00; /*clear */
	GPIOA->MODER |= 0X00008800; /*set PA5,7 to alternate mode */
	GPIOA->AFR[0] &= ~0XF0F00000; /* clear*/
	GPIOA->AFR[0] |= 0X50500000; /*set AF5 */
	
	GPIOA->MODER &= ~0X00000300; /* clear */
	GPIOA->MODER |= 0X00000100; /* set PA4 Output mode */
	
	SPI1->CR1 |= 0X031C; /*set SPI */
	SPI1->CR2 = 0; 
	SPI1->CR1 |= 0x0040; /* SPI enable */
}

void SPI_Start(unsigned char data)
{
	while(!(SPI1->SR & 0X0002)); /* wait the transfer buffer empty*/
	GPIOA->BSRR |= 0X00000010<<16; /*Reset the Pin status*/
	SPI1->DR = data; /*write data */
	while(SPI1->SR & 0X0080); /*Wait until transfering data is finished */
	GPIOA->BSRR |= 0X00000010; /*Set the Pin status*/
}

void Delaymode(int n){
	for(;n >0; n--)
		for(int k =0;k<3195;k++);
}
	
	
	
	
	
