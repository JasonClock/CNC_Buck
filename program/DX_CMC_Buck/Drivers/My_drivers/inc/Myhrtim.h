//
// Created by 18032 on 2026/5/4.
//

#ifndef CNC_BUCK_HRTIM_H
#define CNC_BUCK_HRTIM_H
/*=======头文件========*/
#include <main.h>
#include <Myhrtim.h>
#include <stm32f3xx_hal_hrtim.h>
#include <hrtim.h>
/*========宏定义========*/
#define HRTIM_PERIOD 23040
#define HRTIM_PERIOD_Half 11520

void HRTIM_Start(void);
void HRTIM_change_Duty(float Duty);

#endif //CNC_BUCK_HRTIM_H
