/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    comp.c
  * @brief   This file provides code for the configuration
  *          of the COMP instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "comp.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

COMP_HandleTypeDef hcomp4;
COMP_HandleTypeDef hcomp6;

/* COMP4 init function */
void MX_COMP4_Init(void)
{

  /* USER CODE BEGIN COMP4_Init 0 */

  /* USER CODE END COMP4_Init 0 */

  /* USER CODE BEGIN COMP4_Init 1 */

  /* USER CODE END COMP4_Init 1 */
  hcomp4.Instance = COMP4;
  hcomp4.Init.InvertingInput = COMP_INVERTINGINPUT_DAC1_CH2;
  hcomp4.Init.NonInvertingInput = COMP_NONINVERTINGINPUT_IO1;
  hcomp4.Init.Output = COMP_OUTPUT_NONE;
  hcomp4.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp4.Init.BlankingSrce = COMP_BLANKINGSRCE_NONE;
  hcomp4.Init.TriggerMode = COMP_TRIGGERMODE_IT_RISING;
  if (HAL_COMP_Init(&hcomp4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP4_Init 2 */

  /* USER CODE END COMP4_Init 2 */

}
/* COMP6 init function */
void MX_COMP6_Init(void)
{

  /* USER CODE BEGIN COMP6_Init 0 */

  /* USER CODE END COMP6_Init 0 */

  /* USER CODE BEGIN COMP6_Init 1 */

  /* USER CODE END COMP6_Init 1 */
  hcomp6.Instance = COMP6;
  hcomp6.Init.InvertingInput = COMP_INVERTINGINPUT_DAC2_CH1;
  hcomp6.Init.NonInvertingInput = COMP_NONINVERTINGINPUT_IO1;
  hcomp6.Init.Output = COMP_OUTPUT_NONE;
  hcomp6.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp6.Init.BlankingSrce = COMP_BLANKINGSRCE_NONE;
  hcomp6.Init.TriggerMode = COMP_TRIGGERMODE_IT_RISING;
  if (HAL_COMP_Init(&hcomp6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP6_Init 2 */

  /* USER CODE END COMP6_Init 2 */

}

void HAL_COMP_MspInit(COMP_HandleTypeDef* compHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(compHandle->Instance==COMP4)
  {
  /* USER CODE BEGIN COMP4_MspInit 0 */

  /* USER CODE END COMP4_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**COMP4 GPIO Configuration
    PB0     ------> COMP4_INP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* COMP4 interrupt Init */
    HAL_NVIC_SetPriority(COMP4_6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(COMP4_6_IRQn);
  /* USER CODE BEGIN COMP4_MspInit 1 */

  /* USER CODE END COMP4_MspInit 1 */
  }
  else if(compHandle->Instance==COMP6)
  {
  /* USER CODE BEGIN COMP6_MspInit 0 */

  /* USER CODE END COMP6_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**COMP6 GPIO Configuration
    PB11     ------> COMP6_INP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* COMP6 interrupt Init */
    HAL_NVIC_SetPriority(COMP4_6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(COMP4_6_IRQn);
  /* USER CODE BEGIN COMP6_MspInit 1 */

  /* USER CODE END COMP6_MspInit 1 */
  }
}

void HAL_COMP_MspDeInit(COMP_HandleTypeDef* compHandle)
{

  if(compHandle->Instance==COMP4)
  {
  /* USER CODE BEGIN COMP4_MspDeInit 0 */

  /* USER CODE END COMP4_MspDeInit 0 */

    /**COMP4 GPIO Configuration
    PB0     ------> COMP4_INP
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);

    /* COMP4 interrupt Deinit */
  /* USER CODE BEGIN COMP4:COMP4_6_IRQn disable */
    /**
    * Uncomment the line below to disable the "COMP4_6_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(COMP4_6_IRQn); */
  /* USER CODE END COMP4:COMP4_6_IRQn disable */

  /* USER CODE BEGIN COMP4_MspDeInit 1 */

  /* USER CODE END COMP4_MspDeInit 1 */
  }
  else if(compHandle->Instance==COMP6)
  {
  /* USER CODE BEGIN COMP6_MspDeInit 0 */

  /* USER CODE END COMP6_MspDeInit 0 */

    /**COMP6 GPIO Configuration
    PB11     ------> COMP6_INP
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11);

    /* COMP6 interrupt Deinit */
  /* USER CODE BEGIN COMP6:COMP4_6_IRQn disable */
    /**
    * Uncomment the line below to disable the "COMP4_6_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(COMP4_6_IRQn); */
  /* USER CODE END COMP6:COMP4_6_IRQn disable */

  /* USER CODE BEGIN COMP6_MspDeInit 1 */

  /* USER CODE END COMP6_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
