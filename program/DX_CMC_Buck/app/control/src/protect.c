//
// Created by 18032 on 2026/5/19.
//

#include "../inc/protect.h"
#include <MyADC.h>
#include <PID.h>
#include <stm32f3xx_hal_hrtim.h>
void OVP_Check(void) {
    if ((float)ADC_Voltage.ADC_Buf[0] * 33.0f / 4095.0f < 26.0f) {
        PID_volt.PID_OVP_Flag = 0;
    }
}
void OCP_Check(void) {
    if ((float)ADC_Current.ADC_Buf[0] * 33.0f / 4095.0f < 8.4f) {
        PID_volt.PID_OCP_Flag = 0;
    }
}
void HAL_HRTIM_Fault3Callback(HRTIM_HandleTypeDef *hhrtim)
{
    if (hhrtim->Instance == HRTIM1)
    {
        PID_volt.PID_OVP_Flag = 0;

        // 停止 PID 输出
        PID_volt.PID_Flag = 0;
        PID_volt.Output = 0;

        // 清积分，防止恢复时占空比突然冲上去
        PID_volt.Integral = 0;
    }
}

void HAL_HRTIM_Fault2Callback(HRTIM_HandleTypeDef *hhrtim)
{
    if (hhrtim->Instance == HRTIM1)
    {
        PID_volt.PID_OCP_Flag = 0;

        // 停止 PID 输出
        PID_volt.PID_Flag = 0;
        PID_volt.Output = 0;

        // 清积分，防止恢复时占空比突然冲上去
        PID_volt.Integral = 0;
    }
}