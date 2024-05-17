#include "usart.h"
//UART1 PA9-PA10
//UART2 PA2-PA3
//UART3 PB10-PB11

static UART_HandleTypeDef USART1Handle = {USART1};

static UART_HandleTypeDef USART2Handle = {USART2};

UART_HandleTypeDef* UART_GetHandle(USART_TypeDef* USARTx) {

	if (USARTx == USART1) {
		return &USART1Handle;
	}

	if (USARTx == USART2) {
		return &USART2Handle;
	}
	return 0;
}

typedef struct
{
  char* buffer;
	uint8_t size;
	uint8_t in;
	uint8_t out;
	uint8_t num;
} USART_t;   

char USART1_buffer[100];
char USART2_buffer[100];
char USART3_buffer[100];

USART_t USART1_st={USART1_buffer,100,0,0,0};
USART_t USART2_st={USART2_buffer,100,0,0,0};
USART_t USART3_st={USART3_buffer,100,0,0,0};

int fputc(int ch, FILE *f)
{ 
//	while((USART1->SR&0X40)==0);
//    USART1->DR = (u8) ch;   
send_data(USART2,ch);	
	return ch;
}

void USART_config(USART_TypeDef *USARTx,pin_uart Pin,uint32_t baund){
		
		/* System Clocks Configuration */
		UART_HandleTypeDef* Handle = UART_GetHandle(USARTx);
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		IRQn_Type NVIC_IRQChannel;
		if (USARTx==USART1) {__HAL_RCC_USART1_CLK_ENABLE();NVIC_IRQChannel=USART1_IRQn;}
		else if (USARTx==USART2) {__HAL_RCC_USART2_CLK_ENABLE();NVIC_IRQChannel=USART2_IRQn;}
		else if (USARTx==USART3) {__HAL_RCC_USART3_CLK_ENABLE();NVIC_IRQChannel=USART3_IRQn;}
		
		if (Pin==pins_PA9_PA10) {GPIO_Set_AF(GPIOA,GPIO_PIN_9 | GPIO_PIN_10,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART1);}		
		else if (Pin==pins_PA2_PA3) {GPIO_Set_AF(GPIOA,GPIO_PIN_2 | GPIO_PIN_3,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART2);}	
		else if (Pin==pins_PB10_PB11) {GPIO_Set_AF(GPIOB,GPIO_PIN_10 | GPIO_PIN_11,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);}
		
  Handle->Instance          = USARTx;
  
  Handle->Init.BaudRate     = baund;
	Handle->Init.WordLength   = UART_WORDLENGTH_8B;
  Handle->Init.StopBits     = UART_STOPBITS_1;
  Handle->Init.Parity       = UART_PARITY_NONE;
  Handle->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  Handle->Init.Mode         = UART_MODE_TX_RX;
  Handle->Init.OverSampling = UART_OVERSAMPLING_16;
			
			/* Configure USARTy */
	__HAL_UART_DISABLE(Handle);
	
			if (HAL_UART_Init(Handle) != HAL_OK)
	{
		/* Initialization Error */
		//Error_Handler();
	}
	__HAL_UART_ENABLE(Handle);
	HAL_NVIC_SetPriority(NVIC_IRQChannel, 0, 0);
	__HAL_UART_ENABLE_IT(Handle, UART_IT_RXNE);
	HAL_NVIC_EnableIRQ(NVIC_IRQChannel);
	
}
void USART_to_buffer(USART_t *u,char c)
{
	if (u->in==u->size) {u->in=0;}
	u->buffer[u->in]=c;
	u->in++;
	u->num++;	
}



void send_data(USART_TypeDef* USARTx, char str)
{ 
		UART_HandleTypeDef* Handle = UART_GetHandle(USARTx);
		HAL_UART_Transmit(Handle, (uint8_t *)&str, 1, HAL_MAX_DELAY);
	//USARTx->DR=str;
}

void send_string(USART_TypeDef* USARTx,char *str)
{
	while(*str) {
				send_data(USARTx,*str++);
	}
}

void send_num(USART_TypeDef* USARTx,uint32_t num)
{
		char str[100];
		sprintf(str,"%d\n",num);
		send_string(USARTx,str);	
}
void send_num_float(USART_TypeDef* USARTx,float num)
{
		char str[100];
		sprintf(str,"%.1f\n",num);
		send_string(USARTx,str);	
}



char get_c(USART_TypeDef* USARTx)
{
	USART_t *u;
	char c=0;
	if (USARTx==USART1) {u=&USART1_st;}
	if (USARTx==USART2) {u=&USART2_st;}
	if (USARTx==USART3) {u=&USART3_st;}
	
	if (u->num>0) {
	if (u->out==u->size) {u->out=0;}	
	c=u->buffer[u->out];
	u->out++;
	u->num--;
	}
	return c;
}

uint8_t get_str(USART_TypeDef* USARTx,char *str,uint8_t len)
{
		uint8_t pos=0;;
		char c;
		while (pos<len) {
			c=get_c(USARTx);	
			if (c) {
				str[pos]=c; 
				if (c=='\n') {pos++;break;} else pos++;
				if (pos>len) pos=0;
			}
			else break;
		}
		str[pos]='\0';
	return pos;
}
void USART2_IRQHandler(void)
{
		USART_to_buffer(&USART2_st,USART2->DR);
}

void USART1_IRQHandler(void)
{
		USART_to_buffer(&USART1_st,USART1->DR);
}


