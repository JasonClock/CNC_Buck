//
// Created by 18032 on 2026/5/4.
//

#ifndef CNC_BUCK_DAC_H
#define CNC_BUCK_DAC_H
#include <stdint.h>
#include <main.h>
#include "PID.h"

typedef struct {
    DAC_ChannelConfTypeDef* hdac;
    uint32_t Channel;
}DAC_Struction;

/*=======DAC变量=========*/
DAC_Struction DAC_Volt = {hadc1};
DAC_Struction DAC_Current;

/*=======外设启动========*/
void DAC_Start();

void Set_DAC_Voltage(float volt, DAC_HandleTypeDef* hdac, uint32_t Channel);


#endif //CNC_BUCK_DAC_H
