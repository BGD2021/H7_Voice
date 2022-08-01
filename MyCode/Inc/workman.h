#ifndef __WORKMAN_H__
#define __WORKMAN_H__
#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "arm_math.h"
#include <math.h>
#include <stdio.h>
#include "kalman.h"
#define RED_Pin GPIO_PIN_7
#define RED_GPIO_Port GPIOB
void init_start();
void while_do();
//TIM3ÖÐ¶ÏÏìÓ¦º¯Êý
void resTIM3();
void getPhase750(int countAvg);
void getPhase1250(int countAvg);
float getphase(int x,int y);

void sort(float *p,int len);
#endif
