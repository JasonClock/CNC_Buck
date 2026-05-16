//
// Created by 18032 on 2026/5/12.
//

#include "../inc/BSP_Uart.h"
#include <PID.h>
#include <stdlib.h>

uint8_t uart3_rx_index = 0;

/*============函数============*/
/**
 * function: BSP_UART_SendString
 * description: 通过UART3发送字符串数据，使用DMA进行传输
 * input: const uint8_t* data - 要发送的数据指针
 *        uint16_t len - 要发送的数据长度
 */
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

/**
 * function:Send_Buck_Volt_date
 * description: 将Buck电压数据转换为字符串格式并通过UART3发送
 * input: uint16_t voltage_v - Buck电压的原始ADC值
 * @param voltage_v
 */
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

/**
 * function: HAL_UART_TxCpltCallback
 * description: UART传输完成回调函数，当UART3的DMA传输完成时被调用，重置DMA传输忙标志
 * input: UART_HandleTypeDef *huart - UART句柄指针
 * @param huart
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        uart3_dma_tx_busy = 0;
    }
}

//
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     if (huart->Instance == USART3)
//     {
//         if (uart3_rx_byte == '\n' || uart3_rx_byte == '\r')
//         {
//             uart3_rx_buf[uart3_rx_index] = '\0';
//
//             PID_volt.Kp = (float)atof(uart3_rx_buf);
//
//             uart3_rx_index = 0;
//         }
//         else
//         {
//             if (uart3_rx_index < sizeof(uart3_rx_buf) - 1)
//             {
//                 uart3_rx_buf[uart3_rx_index++] = uart3_rx_byte;
//             }
//             else
//             {
//                 uart3_rx_index = 0;
//             }
//         }
//
//         HAL_UART_Receive_IT(&huart3, (uint8_t*)&uart3_rx_byte, 1);
//     }
// }