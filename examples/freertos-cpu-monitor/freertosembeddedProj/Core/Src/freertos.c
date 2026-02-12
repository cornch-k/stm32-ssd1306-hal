/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "ssd1306_font.h"
#include "makeqrcode.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CPU_MEASURE_PERIOD_MS 500
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
volatile uint32_t idleCount = 0;
volatile uint32_t idleCountMax = 0;
volatile float cpuUsage = 0.0f;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  char msg[] = "Boot Complete.\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  SSD1306_Init();
  SSD1306_Fill(0);
  SSD1306_SetCursor(0, 0);
  SSD1306_UpdateScreen();
  osDelay(100);
  
  idleCount = 0;
  osDelay(CPU_MEASURE_PERIOD_MS);
  idleCountMax = idleCount;
  idleCount = 0;
  
  char buff[32];
  uint32_t prevTick = osKernelGetTickCount();
  
  createQR();
  renderQR(20, 0);
  SSD1306_UpdateScreen();
  /* Infinite loop */
  for(;;)
  {
    // idleCount = 0;

    // SSD1306_Fill(0);
    // sprintf(buff, "CPU: %.1f %%", cpuUsage);
    // SSD1306_SetCursor(0, 0);
    // SSD1306_WriteString(buff, 1);

    // sprintf(buff, "Max: %lu", idleCountMax);
    // SSD1306_SetCursor(0, 20);
    // SSD1306_WriteString(buff, 1);

    // SSD1306_UpdateScreen();

    // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    // prevTick += CPU_MEASURE_PERIOD_MS;
    // osDelayUntil(prevTick);

    // if(idleCountMax > 0)
    // {
    //   cpuUsage = 100.0f - ((float)idleCount / (float)idleCountMax * 100.0f);
    //   if(cpuUsage < 0) cpuUsage = 0;
    // }
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vApplicationIdleHook(void)
{
  if(idleCount < UINT32_MAX- 1000) idleCount++;
}
/* USER CODE END Application */

