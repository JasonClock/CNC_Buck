//
// Created by 18032 on 2026/5/12.
//

#include "../inc/BSP_Uart.h"

#include <stdlib.h>

static volatile uint8_t uart3_dma_tx_busy = 0;
static uint8_t uart3_tx_buf[64];
void BSP_UART_SendString(const uint8_t* data, uint16_t len) {
    if (uart3_dma_tx_busy) {
        // 如果DMA传输正在进行，可以选择等待或者直接返回
        return; // 这里选择直接返回，避免阻塞
    }

    uart3_dma_tx_busy = 1; // 设置DMA传输忙标志

    // 启动DMA传输，如果启动失败就会重新设置空闲标志，使它可以重新
    if (HAL_UART_Transmit_DMA(&huart3, data, len) != HAL_OK) {
        uart3_dma_tx_busy = 0;
    };

}

void Send_Buck_Volt_date(uint16_t voltage_v) {

    uint32_t voltage = (uint32_t)voltage_v * 33000 /4095;
    int len = snprintf((char *)uart3_tx_buf,
                          sizeof(uart3_tx_buf),
                          "%u.%03u\r\n",
                          (uint16_t)(voltage / 1000),
                          (uint16_t)(voltage % 1000));

    if (len <= 0)
    {
        return;
    }

    if (len >= sizeof(uart3_tx_buf))
    {
        len = sizeof(uart3_tx_buf) - 1;
    }

    BSP_UART_SendString(uart3_tx_buf, (uint16_t)len);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        uart3_dma_tx_busy = 0;
    }
}