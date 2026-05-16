//
// Created by 18032 on 2026/5/12.
//

#ifndef DX_CMC_BUCK_MYUART_H
#define DX_CMC_BUCK_MYUART_H

#include <main.h>
#include <string.h>
#include <usart.h>
#include <stdio.h>

/*============*/

// typedef struct {
//     uint8_t *Tx_Buffer;
//     uint16_t Tx_Buffer_Size;
//     volatile uint8_t Tx_Busy_Flag;
// } UART_DMA_ConfigTypeDef;

/*============静态变量==========*/
static volatile uint8_t uart3_dma_tx_busy = 0;
static uint8_t uart3_tx_buf[16];
static volatile uint8_t uart3_rx_byte = 0;
static volatile char uart3_rx_buf[16];


void BSP_UART_SendString(const uint8_t *data, uint16_t len);
void Send_Buck_Volt_date(uint16_t ADC_voltage);




#endif //DX_CMC_BUCK_MYUART_H
