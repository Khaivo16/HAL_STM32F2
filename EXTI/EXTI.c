#include "EXTI.h"

void EXTI_config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t trigger){
		GPIO_InitTypeDef   GPIO_InitStructure;
		IRQn_Type irq;
		uint8_t pinsource;
	
		if (GPIOx==GPIOA) {__HAL_RCC_GPIOA_CLK_ENABLE();}
		else if (GPIOx==GPIOB) {__HAL_RCC_GPIOB_CLK_ENABLE();}
		else if (GPIOx==GPIOC) {__HAL_RCC_GPIOC_CLK_ENABLE();}
		else if (GPIOx==GPIOD) {__HAL_RCC_GPIOD_CLK_ENABLE();}
		else if (GPIOx==GPIOE) {__HAL_RCC_GPIOE_CLK_ENABLE();}
		else if (GPIOx==GPIOF) {__HAL_RCC_GPIOF_CLK_ENABLE();}
		
		if (GPIO_Pin==GPIO_PIN_0) {irq=EXTI0_IRQn;pinsource = 0;}
		else if (GPIO_Pin==GPIO_PIN_1) {irq=EXTI1_IRQn;pinsource = 1;}
		else if (GPIO_Pin==GPIO_PIN_2) {irq=EXTI2_IRQn;pinsource = 2;}
		else if (GPIO_Pin==GPIO_PIN_3) {irq=EXTI3_IRQn;pinsource = 3;}
		else if (GPIO_Pin==GPIO_PIN_4) {irq=EXTI4_IRQn;pinsource = 4;}
		else if (GPIO_Pin==GPIO_PIN_5) {irq=EXTI9_5_IRQn;pinsource = 5;}
		else if (GPIO_Pin==GPIO_PIN_6) {irq=EXTI9_5_IRQn;pinsource = 6;}
		else if (GPIO_Pin==GPIO_PIN_7) {irq=EXTI9_5_IRQn;pinsource = 7;}
		else if (GPIO_Pin==GPIO_PIN_8) {irq=EXTI9_5_IRQn;pinsource = 8;}
		else if (GPIO_Pin==GPIO_PIN_9) {irq=EXTI9_5_IRQn;pinsource = 9;}
		else if (GPIO_Pin==GPIO_PIN_10) {irq=EXTI15_10_IRQn;pinsource = 10;}
		else if (GPIO_Pin==GPIO_PIN_11) {irq=EXTI15_10_IRQn;pinsource = 11;}
		else if (GPIO_Pin==GPIO_PIN_12) {irq=EXTI15_10_IRQn;pinsource = 12;}
		else if (GPIO_Pin==GPIO_PIN_13) {irq=EXTI15_10_IRQn;pinsource = 13;}
		else if (GPIO_Pin==GPIO_PIN_14) {irq=EXTI15_10_IRQn;pinsource = 14;}
		else if (GPIO_Pin==GPIO_PIN_15) {irq=EXTI15_10_IRQn;pinsource = 15;}
		
		if (trigger == TRIGGER_FALLING) {
				GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
				GPIO_InitStructure.Pull = GPIO_PULLUP;
				GPIO_InitStructure.Pin = GPIO_Pin;
				HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
		}
		else if (trigger == TRIGGER_RISING) {
				GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
				GPIO_InitStructure.Pull = GPIO_PULLDOWN;
				GPIO_InitStructure.Pin = GPIO_Pin;
				HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
		}
		else {
		GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
		GPIO_InitStructure.Pull = GPIO_NOPULL;
		GPIO_InitStructure.Pin = GPIO_Pin;
		HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
		}
		
		 /* Enable and set EXTI15_10 Interrupt to the lowest priority */
		HAL_NVIC_SetPriority(irq, 0, 0);
		HAL_NVIC_EnableIRQ(irq);
}