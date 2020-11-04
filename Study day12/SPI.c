#include "stm32f3xx.h"

void SPI_Init(void);
void SPI_Start(unsigned char a);
void Delaymode(int);

int main(void){

	SPI_Init();
	
	while(1){
		for(char i = 'A';i <= 'Z'; i++){
			SPI_Start(i);
			Delaymode(100);
		}
	}
}

void SPI_Init(void){
	RCC->AHBENR |= 1 << 17;
	RCC->APB2ENR |= 1 << 12;
	
	GPIOA->MODER &= ~0X0000CC00;
	GPIOA->MODER |= 0X00008800;
	GPIOA->AFR[0] &= ~0XF0F00000;
	GPIOA->AFR[0] |= 0X50500000;
	
	GPIOA->MODER &= ~0X00000300;
	GPIOA->MODER |= 0X00000100;
	
	SPI1->CR1 |= 0X031C;
	SPI1->CR2 = 0;
	SPI1->CR1 |= 0x0040;
}

void SPI_Start(unsigned char data)
{
	while(!(SPI1->SR & 0X0002)){}
	GPIOA->BSRR |= 0X00000010;
	SPI1->DR = data;
	while(SPI1->SR & 0X0080){}
	GPIOA->BSRR |= 0X00000010<<16;
}

void Delaymode(int n){
	for(;n >0; n--)
		for(int k =0;k<3195;k++);
}
	
	
	
	
	