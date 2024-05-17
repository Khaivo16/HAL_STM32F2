#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
								  
////////////////////////////////////////////////////////////////////////////////// 	 
 /* Includes
 */

/**
 * Interrupt trigger enumeration
 * 
 * Parameters:
 * 	- EXTI_Trigger_Rising:
 * 		Trigger interrupt on rising edge on line
 * 	- EXTI_Trigger_Falling:
 * 		Trigger interrupt on falling edge on line
 * 	- EXTI_Trigger_Rising_Falling:
 * 		Trigger interrupt on any edge on line
 */

void EXTI_config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t trigger);	 					    
#endif