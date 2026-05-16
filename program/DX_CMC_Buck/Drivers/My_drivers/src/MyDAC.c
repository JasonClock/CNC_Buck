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
/**
 * 函数名称：DAC_Start
 * 功能描述：启动DAC外设
 * 输入参数：DAC_Struction* dac_structure - 指向DAC_Struction结构体的指针，包含DAC句柄和通道信息
 * 输出参数：无
 */
void DAC_Start(DAC_Struction* dac_structure)
{
    HAL_DAC_Start(dac_structure->hdac, dac_structure->Channel);
}

/**
 * function:Set_DAC_Value_volt
 * description: 设置DAC输出电压值
 * input: float volt - 期望输出的电压值，单位为伏特
 *        DAC_Struction* DAC_Structure - 指向DAC_Struction结构体的指针，包含DAC句柄和通道信息
 * output: 无
 * @param volt
 * @param DAC_Structure
 */
void Set_DAC_Value_volt(float volt, DAC_Struction* DAC_Structure)
{
    uint32_t data = (uint32_t)(volt / 33.0f * 4095.0f);
    HAL_DAC_SetValue(DAC_Structure->hdac, DAC_Structure->Channel, DAC_ALIGN_12B_R, data);

}