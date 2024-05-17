#ifndef __uart_H
#define __uart_H 			   
#include "sys.h"
#include <stdio.h>
#include "stm32f2xx_hal.h"
typedef enum
{ 	
	pins_PA9_PA10,
	pins_PA2_PA3,
	pins_PB10_PB11
}
pin_uart;

int fputc(int ch, FILE *f);
void USART_config(USART_TypeDef *USARTx,pin_uart Pin,uint32_t baund);
void send_data(USART_TypeDef* USARTx, char str);
void send_string(USART_TypeDef* USARTx,char *str);
void send_num(USART_TypeDef* USARTx,uint32_t num);
void send_num_float(USART_TypeDef* USARTx,float num);
char get_c(USART_TypeDef* USARTx);
uint8_t get_str(USART_TypeDef* USARTx,char *str,uint8_t len);
#endif