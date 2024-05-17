#include "LED7.h"
unsigned char maled_CC[10] = {0xAF, 0xA0, 0x6E, 0xEA, 0xE1, 0xCB, 0xCF, 0xA2, 0xEF, 0xEB};
unsigned char led_pos[5] = {0x08, 0x10,0x20,0x40,0x80};  //Vi Tri Quet Led
void clock_74HC594()
{
	GPIOB->ODR |= (1<<3); //logic 1 to PB3
	GPIOB->ODR &= ~(1<<3); //logic 0 to PB3
}
void data_74HC594( unsigned char data)
{
	for (char i=0;i<=7;i++)
	{
		if ((data &(1<<(7-i)))==0) GPIOB->ODR &=~(1<<5);
		else GPIOB->ODR |=(1<<5);
		clock_74HC594();
	}

}
void QuetLED_12(int data) {
		char ngan, tram, chuc, dv,chuc_ngan;
		chuc=data/10;
		dv=data%10;
	//----led1----
	data_74HC594(led_pos[0]);
	data_74HC594(maled_CC[chuc]);
	GPIOE->ODR |= (1<<0); //logic 1 to PB0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PB1
	HAL_Delay (1);
	//-------led2------
	data_74HC594(led_pos[1]);
	data_74HC594(maled_CC[dv]);
	GPIOE->ODR |= (1<<0); //logic 1 to PB1
	GPIOE->ODR &= ~(1<<0); //logic 0 to PB1
	HAL_Delay (1);
}
void QuetLED_45(int data) {
	char ngan, tram, chuc, dv,chuc_ngan;
	chuc=data/10;
	dv=data%10;
	//----led4----
	data_74HC594(led_pos[3]);
	data_74HC594(maled_CC[chuc]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay (1);
	//-------led5------
	data_74HC594(led_pos[4]);
	data_74HC594(maled_CC[dv]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay (1);
}

void QuetLed_va_IC (int data)
{
	char ngan, tram, chuc, dv,chuc_ngan;
	chuc_ngan=data/10000;
	ngan=data%10000/1000;
	tram=data%10000%1000/100;
	chuc=data%10000%1000%100/10;
	dv=data%10000%1000%100%10;
	//----led1----
	data_74HC594(led_pos[0]);
	data_74HC594(maled_CC[chuc_ngan]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay(1);
	//-------led2------
	data_74HC594(led_pos[1]);
	data_74HC594(maled_CC[ngan]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay(1);
	//---------led3------
	data_74HC594(led_pos[2]);
	data_74HC594(maled_CC[tram]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay(1);
	//------led4
	data_74HC594(led_pos[3]);
	data_74HC594(maled_CC[chuc]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay(1);
	//------led5
	data_74HC594(led_pos[4]);
	data_74HC594(maled_CC[dv]);
	GPIOE->ODR |= (1<<0); //logic 1 to PE0
	GPIOE->ODR &= ~(1<<0); //logic 0 to PE0
	HAL_Delay(1);
}

void LED7_init(){
		RCC->AHB1ENR |= (1<<1) | (1<<4);
		GPIOB->MODER |= (1<<(2*5)) ;
		GPIOB->MODER &= ~(3<<6) ;
		GPIOB->MODER |= (1<<(3*2));
		GPIOB->OSPEEDR |= (1<<(2*5)) | (1<<(2*3));
		GPIOB->OTYPER |= (0<<5) | (0<<3);
		
		GPIOE->MODER |= (1<<(2*0)) | (1<<(2*2)) | (1<<(2*1));
		GPIOE->OSPEEDR |= (1<<(2*0)) | (1<<(2*2))| (1<<(2*1));
		GPIOE->OTYPER |= (0<<0) | (0<<2) | (0<<1);
		GPIOE->ODR &= ~(1<<2);
}