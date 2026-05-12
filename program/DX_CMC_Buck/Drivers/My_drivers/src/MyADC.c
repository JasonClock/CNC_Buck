//
// Created by 18032 on 2026/5/4.
//

#include "../inc/MyADC.h"

ADC_ConfigTypeDef ADC_Voltage = {
    .hadc = &hadc2,
    .ADC_Channel = ADC_CHANNEL_13,
    .ADC_Buf = {0}
};
ADC_ConfigTypeDef ADC_Current = {
    .hadc = &hadc1,
    .ADC_Channel = ADC_CHANNEL_12,
    .ADC_Buf = {0}
};


/**
 * function: ADC_DMA_Start
 * description: 启动ADC的DMA传输
 * input: ADC_ConfigTypeDef *ADC_Config - ADC配置结构体指针，包含ADC句柄、通道和数据缓冲区
 * output: 无
 */
void ADC_DMA_Start(const ADC_ConfigTypeDef *ADC_Config)
{
    // 校准ADC

    while (HAL_ADCEx_Calibration_Start(ADC_Config->hadc, ADC_SINGLE_ENDED) != HAL_OK);
    HAL_ADC_Start_DMA(ADC_Config->hadc, (uint32_t*)ADC_Config->ADC_Buf, 1);
    __HAL_DMA_DISABLE_IT(ADC_Config->hadc->DMA_Handle, DMA_IT_HT);
    __HAL_DMA_DISABLE_IT(ADC_Config->hadc->DMA_Handle, DMA_IT_TC);
}

uint16_t ADC_DMA_Get_Value(ADC_ConfigTypeDef ADC_Config) {
    return ADC_Config.ADC_Buf[0];
}

