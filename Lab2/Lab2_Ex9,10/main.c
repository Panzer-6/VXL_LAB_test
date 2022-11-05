/* USER CODE BEGIN Header */
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
#define COUNTER_DUR 	25
#define DOT_DUR			100
#define DOT_ON			0
#define DOT_OFF			1
#define ENABLE 			0
#define DISABLE 		1
#define FLAG_ON			1
#define FLAG_OFF		0
#define SEVEN_SEG_1		0
#define SEVEN_SEG_2		1
#define SEVEN_SEG_3		2
#define SEVEN_SEG_4		3
#define TIMEOUT			0
#define ONE_MIN			60
#define ONE_HOUR		60
#define UPDATE_EN0()	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, en0)
#define UPDATE_EN1()	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, en1)
#define UPDATE_EN2()	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, en2)
#define UPDATE_EN3()	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, en3)
#define TOGGLE_LED()	HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin)
#define TOGGLE_DOT()	HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin)
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
int timer0_counter = 0;
int timer1_counter = 0;
int timer0_flag = 0;
int timer1_flag = 0;
int TIMER_CYCLE = 10;
GPIO_TypeDef* ENM_PortControl[8] = {ENM0_GPIO_Port, ENM1_GPIO_Port, ENM2_GPIO_Port, ENM3_GPIO_Port,
								ENM4_GPIO_Port, ENM5_GPIO_Port, ENM6_GPIO_Port, ENM7_GPIO_Port};
GPIO_TypeDef* ROW_PortControl[8] = {ROW0_GPIO_Port, ROW1_GPIO_Port, ROW2_GPIO_Port, ROW3_GPIO_Port,
								ROW4_GPIO_Port, ROW5_GPIO_Port, ROW6_GPIO_Port, ROW7_GPIO_Port};
uint16_t ENM_PinControl[8] = {ENM0_Pin, ENM1_Pin, ENM2_Pin, ENM3_Pin, ENM4_Pin, ENM5_Pin, ENM6_Pin, ENM7_Pin,};
uint16_t ROW_PinControl[8] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin, ROW5_Pin, ROW6_Pin, ROW7_Pin,};
void enableLedMatrix(int index)
{
	for (int i = 0; i < 8; i++)
	{
		if (i == index) HAL_GPIO_WritePin(ENM_PortControl[i], ENM_PinControl[i], ENABLE);
		else HAL_GPIO_WritePin(ENM_PortControl[i], ENM_PinControl[i], DISABLE);
	}
}

void setTimer0(int duration)
{
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = FLAG_OFF;
}

void setTimer1(int duration)
{
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = FLAG_OFF;
}

void timer_run()
{
	if (timer0_counter > TIMEOUT)
	{
		timer0_counter--;
		if (timer0_counter == TIMEOUT)
		{
			timer0_flag = FLAG_ON;
		}
	}
	if (timer1_counter > TIMEOUT)
	{
		timer1_counter--;
		if (timer1_counter == TIMEOUT)
		{
			timer1_flag = FLAG_ON;
		}
	}
}

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};
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

void update7SEG(int index)
{
	switch(index)
	{
	case 0:
		//Display the first 7 SEG with led_buffer[0]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, ENABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, DISABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, DISABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, DISABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 1:
		//Display the second 7 SEG with led_buffer[1]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, DISABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, ENABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, DISABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, DISABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 2:
		//Display the third 7 SEG with led_buffer[2]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, DISABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, DISABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, ENABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, DISABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 3:
		//Display the forth 7 SEG with led_buffer[3]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, DISABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, DISABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, DISABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, ENABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	}
}

void updateClockBuffer(int hour, int minute)
{
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
int animated_led_matrix_row = 0;
uint8_t matrix_buffer[8] = {0xff, 0xc0, 0x80, 0x37, 0x37, 0x80, 0xc0, 0xff};
uint8_t animated_matrix_buffer[16][8] = {{0xff, 0xc0, 0x80, 0x37, 0x37, 0x80, 0xc0, 0xff},
									   {0xc0, 0x80, 0x37, 0x37, 0x80, 0xc0, 0xff, 0xff},
									   {0x80, 0x37, 0x37, 0x80, 0xc0, 0xff, 0xff, 0xff},
									   {0x37, 0x37, 0x80, 0xc0, 0xff, 0xff, 0xff, 0xff},
									   {0x37, 0x80, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff},
									   {0x80, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
									   {0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
									   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
									   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
									   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
									   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0},
									   {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x80},
									   {0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x80, 0x37},
									   {0xff, 0xff, 0xff, 0xff, 0xc0, 0x80, 0x37, 0x37},
									   {0xff, 0xff, 0xff, 0xc0, 0x80, 0x37, 0x37, 0x80},
									   {0xff, 0xff, 0xc0, 0x80, 0x37, 0x37, 0x80, 0xc0}};

void displayLedMatrix(int col)
{
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(ROW_PortControl[i], ROW_PinControl[i], (matrix_buffer[col] >> i)&0x01 );
	}
}

void displayAnimatedLedMatrix(int row, int col)
{
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(ROW_PortControl[i], ROW_PinControl[i], (animated_matrix_buffer[row][col] >> i)&0x01 );
	}
}

void updateLedMatrix(int index)
{
	enableLedMatrix(index);
	displayLedMatrix(index);
}

void updateAnimatedLedMatrix(int row, int index)
{
	enableLedMatrix(index);
	displayAnimatedLedMatrix(row, index);
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
  int hour = 15;
    int minute = 8;
    int second = 50;
    setTimer0(10);
    setTimer1(10);
    while (1)
    {
  	  if (timer0_flag == FLAG_ON)
  	  {
  		  TOGGLE_LED();
  		  TOGGLE_DOT();
  		  if (second >= ONE_MIN)
  		  {
  			  second = 0;
  			  minute++;
  		  }
  		  if (minute >= ONE_HOUR)
  		  {
  			  minute = 0;
  			  hour++;
  		  }
  		  if (hour >= 24)
  		  {
  			  hour = 0;
  		  }
  		  updateClockBuffer(hour, minute);
  		  second++;
  		  setTimer0(1000);
  	  }
  	  if (timer1_flag == FLAG_ON)
  	  {
  		  //if (index_led > SEVEN_SEG_4) index_led = SEVEN_SEG_1;
  		  //update7SEG(index_led++);

  		  //if (index_led_matrix > 7) index_led_matrix = 0;
  		  //updateLedMatrix(index_led_matrix++);

  		  if (animated_led_matrix_row >= 16) animated_led_matrix_row = 0;
  		  if (index_led_matrix > 7)
		  {
			  animated_led_matrix_row++;
			  index_led_matrix = 0;
		  }
  		  updateAnimatedLedMatrix(animated_led_matrix_row, index_led_matrix++);

  		  setTimer1(10);
  	  }
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
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|RED_LED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_a_Pin|SEVEN_SEG_b_Pin|SEVEN_SEG_c_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEVEN_SEG_d_Pin|SEVEN_SEG_e_Pin|SEVEN_SEG_f_Pin
                          |SEVEN_SEG_g_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin RED_LED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|RED_LED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEVEN_SEG_a_Pin SEVEN_SEG_b_Pin SEVEN_SEG_c_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEVEN_SEG_d_Pin SEVEN_SEG_e_Pin SEVEN_SEG_f_Pin
                           SEVEN_SEG_g_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEVEN_SEG_a_Pin|SEVEN_SEG_b_Pin|SEVEN_SEG_c_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEVEN_SEG_d_Pin|SEVEN_SEG_e_Pin|SEVEN_SEG_f_Pin
                          |SEVEN_SEG_g_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	timer_run();
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
