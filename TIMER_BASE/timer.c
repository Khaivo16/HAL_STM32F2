#include "timer.h"


static TIM_HandleTypeDef TIM2Handle = {TIM2};

static TIM_HandleTypeDef TIM3Handle = {TIM3};

static TIM_HandleTypeDef TIM4Handle = {TIM4};

TIM_HandleTypeDef* TIM_GetHandle(TIM_TypeDef* TIMx) {
	if (TIMx == TIM2) {
		return &TIM2Handle;
	}
	if (TIMx == TIM3) {
		return &TIM3Handle;
	}
	if (TIMx == TIM4) {
		return &TIM4Handle;
	}
	return 0;
}

void Timerbase_init(TIM_TypeDef * TIMx,uint16_t ARR,uint16_t PSC) {
		TIM_HandleTypeDef* Handle = TIM_GetHandle(TIMx);
		IRQn_Type irq;
		uint8_t pinsource;
	
		if (TIMx == TIM2) {__HAL_RCC_TIM2_CLK_ENABLE();irq=TIM2_IRQn;pinsource=2;}
		else if (TIMx == TIM3) {__HAL_RCC_TIM3_CLK_ENABLE();irq=TIM3_IRQn;pinsource=3;}
		else if (TIMx == TIM4) {__HAL_RCC_TIM4_CLK_ENABLE();irq=TIM4_IRQn;pinsource=4;}
		
		Handle->Instance = TIMx;
		Handle->Init.Period = PSC-1;
		Handle->Init.Prescaler = ARR-1;
		Handle->Init.ClockDivision = 0;
		Handle->Init.CounterMode = TIM_COUNTERMODE_UP;
		Handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if(HAL_TIM_Base_Init(Handle) != HAL_OK)
		{
			/* Initialization Error */
//			Error_Handler();
		}
		HAL_NVIC_SetPriority(irq, 0, pinsource);
		HAL_NVIC_EnableIRQ(irq);
		
}
