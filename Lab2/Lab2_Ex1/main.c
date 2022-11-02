/* USER CODE BEGIN Header */
/*MAIN.C FOR EX1 LAB2*/
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define COUNTER_DUR 	50
#define ENABLE 			0
#define DISABLE 		1
#define SEVEN_SEG_1		0
#define SEVEN_SEG_2		1
#define TIMEOUT			0
#define UPDATE_EN0()	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, en0)
#define UPDATE_EN1()	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, en1)
#define TOGGLE_LED()	HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num)
{
	int SEVEN_SEG_array[10][7] = {{0, 0, 0, 0, 0, 0, 1},
						   	   	  {1, 0, 0, 1, 1, 1, 1},
								  {0, 0, 1, 0, 0, 1, 0},
								  {0, 0, 0, 0, 1, 1, 0},
								  {1, 0, 0, 1, 1, 0, 0},
								  {0, 1, 0, 0, 1, 0, 0},
								  {0, 1, 0, 0, 0, 0, 0},
								  {0, 0, 0, 1, 1, 1, 1},
								  {0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 0, 0}};
	HAL_GPIO_WritePin(SEVEN_SEG_a_GPIO_Port, SEVEN_SEG_a_Pin, SEVEN_SEG_array[num][0]);
	HAL_GPIO_WritePin(SEVEN_SEG_b_GPIO_Port, SEVEN_SEG_b_Pin, SEVEN_SEG_array[num][1]);
	HAL_GPIO_WritePin(SEVEN_SEG_c_GPIO_Port, SEVEN_SEG_c_Pin, SEVEN_SEG_array[num][2]);
	HAL_GPIO_WritePin(SEVEN_SEG_d_GPIO_Port, SEVEN_SEG_d_Pin, SEVEN_SEG_array[num][3]);
	HAL_GPIO_WritePin(SEVEN_SEG_e_GPIO_Port, SEVEN_SEG_e_Pin, SEVEN_SEG_array[num][4]);
	HAL_GPIO_WritePin(SEVEN_SEG_f_GPIO_Port, SEVEN_SEG_f_Pin, SEVEN_SEG_array[num][5]);
	HAL_GPIO_WritePin(SEVEN_SEG_g_GPIO_Port, SEVEN_SEG_g_Pin, SEVEN_SEG_array[num][6]);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, 1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_LED_Pin|EN0_Pin|EN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_a_Pin|SEVEN_SEG_b_Pin|SEVEN_SEG_c_Pin|SEVEN_SEG_d_Pin
                          |SEVEN_SEG_e_Pin|SEVEN_SEG_f_Pin|SEVEN_SEG_g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_LED_Pin EN0_Pin EN1_Pin */
  GPIO_InitStruct.Pin = RED_LED_Pin|EN0_Pin|EN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEVEN_SEG_a_Pin SEVEN_SEG_b_Pin SEVEN_SEG_c_Pin SEVEN_SEG_d_Pin
                           SEVEN_SEG_e_Pin SEVEN_SEG_f_Pin SEVEN_SEG_g_Pin */
  GPIO_InitStruct.Pin = SEVEN_SEG_a_Pin|SEVEN_SEG_b_Pin|SEVEN_SEG_c_Pin|SEVEN_SEG_d_Pin
                          |SEVEN_SEG_e_Pin|SEVEN_SEG_f_Pin|SEVEN_SEG_g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int counter = COUNTER_DUR;
int en0 = ENABLE;
int en1 = DISABLE;
int led_buffer[2] = {1, 2};
int seven_seg_num = -1;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/*
	counter--;
	if( counter <= 0) {
	counter = 50;
	HAL_GPIO_TogglePin ( RED_LED_GPIO_Port , RED_LED_Pin ) ;
	}
	*/
	switch(seven_seg_num)
	{
	case -1:
		seven_seg_num = SEVEN_SEG_1;
		display7SEG(led_buffer[seven_seg_num]);
		seven_seg_num = SEVEN_SEG_2;
		break;
	case SEVEN_SEG_1:
		if (counter == TIMEOUT)
		{
			counter = COUNTER_DUR;
			TOGGLE_LED();
			en0 = ENABLE;
			en1 = DISABLE;
			display7SEG(led_buffer[seven_seg_num]);
			seven_seg_num = SEVEN_SEG_2;
		}
		break;
	case SEVEN_SEG_2:
		if (counter == TIMEOUT)
		{
			counter = COUNTER_DUR;
			TOGGLE_LED();
			en0 = DISABLE;
			en1 = ENABLE;
			display7SEG(led_buffer[seven_seg_num]);
			seven_seg_num = SEVEN_SEG_1;
		}
		break;
	default:
		break;
	}
	UPDATE_EN0();
	UPDATE_EN1();
	counter--;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
