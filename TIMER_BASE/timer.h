#ifndef __timer_H
#define __timer_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
void Timerbase_init(TIM_TypeDef * TIMx,uint16_t ARR,uint16_t PSC);		
TIM_HandleTypeDef* TIM_GetHandle(TIM_TypeDef* TIMx);
////////////////////////////////////////////////////////////////////////////////// 	 
					    
#endif