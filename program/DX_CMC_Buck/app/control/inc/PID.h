//
// Created by 18032 on 2026/5/4.
//

#ifndef CNC_BUCK_PID_H
#define CNC_BUCK_PID_H
#include <main.h>
#include <Myhrtim.h>
/*========PID结构体=========*/
typedef struct
{
    float Kp;          //比例系数
    float Ki;          //积分系数

    float Target;    //目标值
    float Real;       //实际值
    float Output;   //输出值
    float Feedback;      //输出值
    

    float duty_max;  //输出最大值
    float duty_min;  //输出最小值

    // float max_Peak; //输出峰值

    float Integral_max;       //积分限幅

    float Proportion;   //比例项
    float Integral;    //积分项

    float Last_Error;  //上一次误差
    float New_Error;    //当前误差

    volatile uint8_t PID_Flag;   //PID控制标志位
} PID_t;


/*=========变量=========*/
extern PID_t PID_volt;
extern PID_t PID_Current;


/*===========PID=========*/
void PID_Init(PID_t *PID);

void PID_SetTarget(PID_t *PID, float Target);
void PID_limit(PID_t *PID, float max, float min);

void PID_control_volt(PID_t *PID);

// void PID_Output(PID_t *PID);



#endif //CNC_BUCK_PID_H
