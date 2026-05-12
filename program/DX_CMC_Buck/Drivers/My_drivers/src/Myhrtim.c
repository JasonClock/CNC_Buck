//
// Created by 18032 on 2026/5/4.
//

#include "../inc/Myhrtim.h"

void HRTIM_Start(void) {

    HAL_HRTIM_WaveformCountStart_DMA(&hhrtim1, HRTIM_TIMERID_TIMER_A);
    HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2);;


}

void HRTIM_Change_Duty(uint16_t Duty) {
    uint16_t Duty_Half = Duty / 2;
    uint16_t Duty_Half_Value = Duty_Half * HRTIM_PERIOD;

    uint16_t Duty_Compare_1 = HRTIM_PERIOD_Half - Duty_Half_Value;
    uint16_t Duty_Compare_3 = HRTIM_PERIOD_Half + Duty_Half_Value;

    __HAL_HRTIM_SetCompare(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, Duty_Compare_1);
    __HAL_HRTIM_SetCompare(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_3, Duty_Compare_3);
}
