//
// Created by 18032 on 2026/5/4.
//

#ifndef CNC_BUCK_MYADC_H
#define CNC_BUCK_MYADC_H
#include <main.h>
#include "adc.h"
/*=======数据类型=======*/
typedef struct {
    ADC_HandleTypeDef* hadc;
    uint32_t ADC_Channel;
    volatile uint16_t ADC_Buf[1];
} ADC_ConfigTypeDef;

/*======变量=======*/
extern ADC_ConfigTypeDef ADC_Voltage;
extern ADC_ConfigTypeDef ADC_Current;


void ADC_DMA_Start(const ADC_ConfigTypeDef *ADC_Config);

uint16_t ADC_DMA_Get_value(ADC_ConfigTypeDef* ADC_Config);


#endif //CNC_BUCK_MYADC_H
