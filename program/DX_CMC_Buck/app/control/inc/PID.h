//
// Created by 18032 on 2026/5/4.
//

#ifndef CNC_BUCK_PID_H
#define CNC_BUCK_PID_H

/*========PID结构体=========*/
typedef struct
{
    float Kp;          //比例系数
    float Ki;          //积分系数
    float Kd;          //微分系数

    float Target;    //目标值
    float Input;       //输入值
    float Output;      //输出值

    float max;  //输出最大值
    float min;  //输出最小值

    float max_Peak; //输出峰值


    float Proportion;   //比例项
    float Differentiation; //微分项
    float Integral;    //积分项

    float Last_Error;  //上一次误差
} PID_t;


/*=========静态变量=========*/
// PID_t PID_volt;
// PID_t PID_Current;



/*===========PID=========*/
void PID_Init(PID_t *PID);

void PID_SetTarget(PID_t *PID, float Target);
void PID_limit(PID_t *PID, float max, float min);

void PID_control(PID_t *PID);





#endif //CNC_BUCK_PID_H
