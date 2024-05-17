#ifndef __LED7_H
#define __LED7_H 			   
#include "sys.h"
#include <stdio.h>

void LED7_init();
void QuetLed_va_IC (int data);
void QuetLED_12(int data);
void QuetLED_45(int data);
void clock_74HC594();

#endif