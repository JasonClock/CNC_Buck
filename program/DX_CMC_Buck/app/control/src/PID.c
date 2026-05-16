//
// Created by 18032 on 2026/5/4.
//

#include "../inc/PID.h"
#include <Myhrtim.h>
#include <MyADC.h>

/*=========宏定义============*/
#define BUCK_VIN         48.0f

#define DUTY_MIN         0.02f
#define DUTY_MAX         0.95f

/*=========变量============*/
PID_t PID_volt;
PID_t PID_Current;

/**
 * function:PID_Init
 * description: 初始化PID控制器的参数和状态
 * input: PID_t *PID - 指向PID控制器结构体的指针
 * output: 无
 * @param PID
 */
void PID_Init(PID_t *PID)
{
    PID->Kp = 0.005f;
    PID->Ki = 0.0005f;

    PID->Target = 24.0f;
    PID->Real = 0;
    PID->Feedback= 0;

    PID->duty_max =0.80f;
    PID->duty_min = 0.20f;

    PID->Integral_max = 0.15f;   // 积分限幅，单位是占空比


    PID->Proportion = 0.0f;
    PID->Integral = 0.0f;

    PID->Last_Error = 0;
    PID->New_Error = 0;

    PID->PID_Flag = 1;
}

/**
 * function:PID_SetTarget
 * @param PID
 * @param Target
 */
void PID_SetTarget(PID_t *PID, float Target)
{
    PID->Target = Target;
}

/**
 * function:PID_Limit
 * description: 设置PID控制器的输出限幅值
 * input: PID_t *PID - 指向PID控制器结构体的指针
 *        float max - 输出的最大值
 *        float min - 输出的最小值
 * output: 无
 * @param PID
 * @param max
 * @param min
 */
void PID_limit(PID_t *PID, float max, float min)
{
    PID->duty_max = max;
    PID->duty_min = min;
}

/**
 * function:PID_control_volt
 * description: 执行电压PID控制算法，根据目标电压和实际电压计算占空比，并通过HRTIM输出控制信号
 * input: PID_t *PID - 指向PID控制器结构体的指针，包含目标值、实际值、误差和输出等参数
 * output: 无
 * @param PID
 */
void PID_control_volt(PID_t *PID)
{

        /*=======电压采样========*/
        PID->Feedback = (float)ADC_Voltage.ADC_Buf[0] * 33.0f / 4095.0f;

        if (PID->Feedback < 10.0f)
            return;

        /*======误差计算========*/
        PID->New_Error = PID->Target - PID->Feedback;

        /*========前馈占空比========*/
        float duty_ff = PID->Target / BUCK_VIN;

        /*=======P计算=======*/
        PID->Proportion = PID->Kp * PID->New_Error;

        /*=======I计算=======*/
         if (PID->Integral < PID->Integral_max && PID->Integral > -PID->Integral_max)
              PID->Integral += PID->Ki * PID->New_Error;

        /*========积分限幅=========*/

        if (PID->Integral > PID->Integral_max)
            PID->Integral = PID->Integral_max;
        else if (PID->Integral < -PID->Integral_max)
            PID->Integral = -PID->Integral_max;

        /*======调节=========*/
        float duty = duty_ff + PID->Proportion + PID->Integral;

        // /*===积分限幅===*/
        // if (PID->Integral > PID->max_Peak) {
        //     PID->Integral = PID->max_Peak;
        // } else if (PID->Integral < -PID->max_Peak) {
        //     PID->Integral = -PID->max_Peak;
        // }

        /*=========占空比限幅==========*/
        if (duty > PID->duty_max)
            duty = PID->duty_max;
        else if (duty < PID->duty_min)
            duty = PID->duty_min;

        // PID->Output = PID->Kp * PID->New_Error;

        // /*=====P I 计算======*/
        // PID->Output = PID->Proportion + PID->Integral;


        // /*========输出限幅=========*/
        // if (PID->Output > PID->duty_max) {
        //     PID->Output = PID->duty_max;
        // } else if (PID->Output < PID->duty_min) {
        //     PID->Output = PID->duty_min;
        // }

        // /*=======更新误差=========*/
        // PID->Last_Error = PID->New_Error;

        PID->Output = duty;
        /*=======输出=========*/
        HRTIM_change_Duty(PID->Output);


        // PID_Output(PID);
}


// void PID_output(PID_t *PID) {
//     uint16_t duty = (uint16_t)(PID->Output / 30.0f * 4095);
//
//     HRTIM_change_Duty(duty);
//
// }