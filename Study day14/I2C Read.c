#include "stm32f3xx.h"

void delaymode(int a);

void I2C_Init(void);
int I2C_Read(char slaveA, char memoryA, char * data);

int main(void){
	char data;
	
	I2C_Init();
	
	RCC->AHBENR |=
	GPIOA->MODER &= ~0X00000C00;
	GPIOA->MODER |=  0X00000400;
	
	while(1)
	{
		
		I2C_Read(0X68, 0, &data);
		
		if( data & 1)
			GPIOA->ODR |= 0X00000020; /* LED ON */
		else
			GPIOA->ODR &= ~0X00000020; /* LED OFF */
		
		delaymode(10);
	}
}

void delaymode(int a){
	for(;a>0;a--)
		for(int i = 0 ;i < 3195; i++);
}

int I2C_Read(char slaveA, char memoryA, char * data)
{
	while(I2C1->ISR & 1<<15); /* wait untill bus is not busy */
	
	I2C1->CR2 |= 1<< 13; /* start generated*/
	
	I2C1->TXDR = slaveA << 1; /* transmit slave address plus write*/
	while(!(I2C1->ISR &1 << 3)); /* untill with the address is matched */
	while(!(I2C1->ISR &2)); /* wait for data register is empty */
	
	I2C1->TXDR = memoryA; /* send Memory address*/
	while(!(I2C1->ISR &2)); /* wait for data register is empty */
	
	I2C1->CR2 |= 1<< 13; /*re-start genertaed */
	
	I2C1->TXDR = slaveA << 1|1; /* transmit slave address plus Read*/
	while(!(I2C1->ISR &1<<3));
	while(!(I2C1->ISR &2));
	I2C1->CR2 |= 1<< 15; /*  */
	
	I2C1->CR2 |= 1<< 14; /*stop generated */
	
	while(!(I2C1->ISR &4)); /* wait untill Recevie data register is empty */
	*data++ = I2C1->RXDR; /* Receive data */
	return 0;
}

