//
// Created by 18032 on 2026/5/4.
//

#include "../inc/MyDAC.h"

DAC_Struction DAC_Volt = {
    .hdac = &hdac1,
    .Channel = DAC_CHANNEL_2
};


DAC_Struction DAC_Current = {
    .hdac = &hdac2,
    .Channel = DAC_CHANNEL_1
};
/*
 * 函数名称：
 * 功能：
 * 变量：
 */
void DAC_Start(DAC_Struction* dac_structure)
{
    HAL_DAC_Start(dac_structure->hdac, dac_structure->Channel);
}

void Set_DAC_Voltage(float volt, DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    uint32_t data = (uint32_t)(volt / 3.3 * 4095);
    HAL_DAC_SetValue(hdac, Channel, DAC_ALIGN_12B_R, data);
}