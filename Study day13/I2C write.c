#include "stm32f3xx.h"


void I2C_Init(void);
int I2CWrite(char, char);
void delaymode(int);

int main(void){
	I2C_Init();
	I2CWrite(0x0e,0);
	
	while(1){
	}
}

void delaymode(int n){
	for(;n >0; n--)
		for(int k =0;k<3195;k++);
}
void I2C_Init(void){
	RCC->AHBENR |= 1<<18;  /* GPIOB clock enalbe*/
	RCC->APB1ENR |= 1 << 21; /* I2C clock enable */
	
	GPIOB->MODER &= ~0X000F0000; /* PB8,PB9 clear*/
	GPIOB->MODER |=  0X000A0000; /* PB8,PB9 set*/
	GPIOB->AFR[1] &= ~0X000000ff; /* set PB9,9 clear*/
	GPIOB->AFR[1] |=  0X00000044; /* af4 set */
	GPIOB->OTYPER |=  0X00000300; /* Output open drain */
	GPIOB->PUPDR &= ~0X000F0000; /* clear*/
	GPIOB->PUPDR |=  0X00050000; /* Pull-up method*/
	
	I2C1->CR1 |= 1; /* Enalbe I2C */
}

int I2CWrite(char Memory, char data)
{
	while(I2C1->ISR & 0X00008000); /* Wait the bus not busy */
	
	I2C1->CR2 |= 1 << 13;  /* start generation */
	
	I2C1->TXDR |= 0x68 << 1; /* send slave address */
	while(I2C1->ISR & 0X00000008); /* wait slave address set*/
	I2C1->ICR |= 1<<3; /*clear slave address flag  */
	while(I2C1->ISR & 0X00000001); /* wait until transmit data regi empty*/
	
	I2C1->TXDR |= Memory; /* send Memory address */
	while(I2C1->ISR & 0X00000001); /* wait until transmit data regi empty*/
	
	I2C1->TXDR |= data; /* send Data */
	while(I2C1->ISR & 1<<6); /* wait until transfer data is finished */
	
	I2C1->CR2 |= 1<<14; /* stop generation */
	
	return 0;
}
