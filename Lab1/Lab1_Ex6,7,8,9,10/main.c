/* USER CODE BEGIN Header */
/*MAIN.C FOR EX6, 7, 8, 9, 10 LAB1*/
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
#define ONE_MIN 	60
#define ONE_HOUR 	60
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void clearAllClock()
{
	HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, RESET);
	HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, RESET);
	HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, RESET);
	HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, RESET);
	HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, RESET);
	HAL_GPIO_WritePin(LED_5_GPIO_Port, LED_5_Pin, RESET);
	HAL_GPIO_WritePin(LED_6_GPIO_Port, LED_6_Pin, RESET);
	HAL_GPIO_WritePin(LED_7_GPIO_Port, LED_7_Pin, RESET);
	HAL_GPIO_WritePin(LED_8_GPIO_Port, LED_8_Pin, RESET);
	HAL_GPIO_WritePin(LED_9_GPIO_Port, LED_9_Pin, RESET);
	HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
	HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);
}
void setNumberOnClock(int num)
{
	switch (num) {
		case 0:
			HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, SET);
			break;
		case 1:
			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, SET);
			break;
		case 2:
			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, SET);
			break;
		case 3:
			HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, SET);
			break;
		case 4:
			HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, SET);
			break;
		case 5:
			HAL_GPIO_WritePin(LED_5_GPIO_Port, LED_5_Pin, SET);
			break;
		case 6:
			HAL_GPIO_WritePin(LED_6_GPIO_Port, LED_6_Pin, SET);
			break;
		case 7:
			HAL_GPIO_WritePin(LED_7_GPIO_Port, LED_7_Pin, SET);
			break;
		case 8:
			HAL_GPIO_WritePin(LED_8_GPIO_Port, LED_8_Pin, SET);
			break;
		case 9:
			HAL_GPIO_WritePin(LED_9_GPIO_Port, LED_9_Pin, SET);
			break;
		case 10:
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, SET);
			break;
		case 11:
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, SET);
			break;
		default:
			break;
	}
}
void clearNumberOnClock(int num)
{
	switch (num) {
		case 0:
			HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(LED_5_GPIO_Port, LED_5_Pin, RESET);
			break;
		case 6:
			HAL_GPIO_WritePin(LED_6_GPIO_Port, LED_6_Pin, RESET);
			break;
		case 7:
			HAL_GPIO_WritePin(LED_7_GPIO_Port, LED_7_Pin, RESET);
			break;
		case 8:
			HAL_GPIO_WritePin(LED_8_GPIO_Port, LED_8_Pin, RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(LED_9_GPIO_Port, LED_9_Pin, RESET);
			break;
		case 10:
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
			break;
		case 11:
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);
			break;
		default:
			break;
	}
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int sec = 0;
  int min = 0;
  int hour = 0;
  //int LED_state[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  //clearAllClock();
  while (1)
  {
	  // sec-min-hour conversion
	  if (sec == ONE_MIN)
	  {
		  sec = 0;
		  min += 1;
	  }
	  if (min == ONE_HOUR)
	  {
		  min = 0;
		  hour += 1;
	  }
	  if (hour == 12)
	  {
		  hour = 0;
	  }
	  // turn on the LED and turn off the previous LED
	  // if the current sec-min-hour value is not there
	  // the state of the LEDs are recorded in an array
	  clearAllClock();
	  setNumberOnClock(sec/5);
	  setNumberOnClock(min/5);
	  setNumberOnClock(hour);
	  /*
	  LED_state[(sec / 5) % 12] = 1; // turn on sec LED
	  if (((sec / 5) % 12) - 1 < 0) // if prev LED is not of min or hour, turn off
	  {
		  if (((min / 5) % 12) != 11 && (hour % 12) != 11) LED_state[11] = 0;
	  }
	  else if (((min / 5) % 12) != (((sec / 5) % 12) - 1) && (hour % 12) != (((sec / 5) % 12) - 1))
		  LED_state[((sec / 5) % 12) - 1] = 0;

	  LED_state[(min / 5) % 12] = 1; // turn on min LED
	  if (((min / 5) % 12) - 1 < 0) // if prev LED is not of sec or hour, turn off
	  {
		  if ((sec / 5) % 12 != 11 && (hour % 12) != 11) LED_state[11] = 0;
	  }
	  else if ((sec / 5) % 12 != (((min / 5) % 12) - 1) && (hour % 12) != (((min / 5) % 12) - 1))
		  LED_state[((min / 5) % 12) - 1] = 0;

	  LED_state[hour % 12] = 1; // turn on hour LED
	  if ((hour % 12) - 1 < 0) // if prev LED is not of sec or min, turn off
	  {
		  if ((sec / 5) % 12 != 11 && ((min / 5) % 12) != 11) LED_state[11] = 0;
	  }
	  else if ((sec / 5) % 12 != ((hour % 12) - 1) && ((min / 5) % 12) != ((hour % 12) - 1))
		  LED_state[(hour % 12) - 1] = 0;
		  */


	  /*
	  if ((sec / 5) % 12 == 0 || (min / 5) % 12 == 0 || hour % 12 == 0)
	  {
		  if ((sec / 5) % 12 != 11 && (min / 5) % 12 != 11 && hour % 12 != 11) LED_state[11] = 0;
		  LED_state[0] = 1;
	  }
	  if ((sec / 5) % 12 == 1 || (min / 5) % 12 == 1 || hour % 12 == 1)
	  {
		  if ((sec / 5) % 12 != 0 && (min / 5) % 12 != 0 && hour % 12 != 0) LED_state[0] = 0;
		  LED_state[1] = 1;
	  }
	  if ((sec / 5) % 12 == 2 || (min / 5) % 12 == 2 || hour % 12 == 2)
	  {
		  if ((sec / 5) % 12 != 1 && (min / 5) % 12 != 1 && hour % 12 != 1) LED_state[1] = 0;
		  LED_state[2] = 1;
	  }
	  if ((sec / 5) % 12 == 3 || (min / 5) % 12 == 3 || hour % 12 == 3)
	  {
		  if ((sec / 5) % 12 != 2 && (min / 5) % 12 != 2 && hour % 12 != 2) LED_state[2] = 0;
		  LED_state[3] = 1;
	  }
	  if ((sec / 5) % 12 == 4 || (min / 5) % 12 == 4 || hour % 12 == 4)
	  {
		  if ((sec / 5) % 12 != 3 && (min / 5) % 12 != 3 && hour % 12 != 3) LED_state[3] = 0;
		  LED_state[4] = 1;
	  }
	  if ((sec / 5) % 12 == 5 || (min / 5) % 12 == 5 || hour % 12 == 5)
	  {
		  if ((sec / 5) % 12 != 4 && (min / 5) % 12 != 4 && hour % 12 != 4) LED_state[4] = 0;
		  LED_state[5] = 1;
	  }
	  if ((sec / 5) % 12 == 6 || (min / 5) % 12 == 6 || hour % 12 == 6)
	  {
		  if ((sec / 5) % 12 != 5 && (min / 5) % 12 != 5 && hour % 12 != 5) LED_state[5] = 0;
		  LED_state[6] = 1;
	  }
	  if ((sec / 5) % 12 == 7 || (min / 5) % 12 == 7 || hour % 12 == 7)
	  {
		  if ((sec / 5) % 12 != 6 && (min / 5) % 12 != 6 && hour % 12 != 6) LED_state[6] = 0;
		  LED_state[7] = 1;
	  }
	  if ((sec / 5) % 12 == 8 || (min / 5) % 12 == 8 || hour % 12 == 8)
	  {
		  if ((sec / 5) % 12 != 7 && (min / 5) % 12 != 7 && hour % 12 != 7) LED_state[7] = 0;
		  LED_state[8] = 1;
	  }
	  if ((sec / 5) % 12 == 9 || (min / 5) % 12 == 9 || hour % 12 == 9)
	  {
		  if ((sec / 5) % 12 != 8 && (min / 5) % 12 != 8 && hour % 12 != 8) LED_state[8] = 0;
		  LED_state[9] = 1;
	  }
	  if ((sec / 5) % 12 == 10 || (min / 5) % 12 == 10 || hour % 12 == 10)
	  {
		  if ((sec / 5) % 12 != 9 && (min / 5) % 12 != 9 && hour % 12 != 9) LED_state[9] = 0;
		  LED_state[10] = 1;
	  }
	  if ((sec / 5) % 12 == 11 || (min / 5) % 12 == 11 || hour % 12 == 11)
	  {
		  if ((sec / 5) % 12 != 10 && (min / 5) % 12 != 10 && hour % 12 != 10) LED_state[10] = 0;
		  LED_state[11] = 1;
	  }
	  */
	  /*
	  for (int i = 0; i < 12; i++) // loop through the state array, turn on LED i if array[i] is 1
	  {								// if array[i] is 0, turn off LED i
		  if (LED_state[i] == 1) setNumberOnClock(i);
		  if (LED_state[i] == 0) clearNumberOnClock(i);
	  }*/
	  sec++;
	  HAL_Delay(1000);
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin|LED_7_Pin
                          |LED_8_Pin|LED_9_Pin|LED_10_Pin|LED_11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_0_Pin LED_1_Pin LED_2_Pin LED_3_Pin
                           LED_4_Pin LED_5_Pin LED_6_Pin LED_7_Pin
                           LED_8_Pin LED_9_Pin LED_10_Pin LED_11_Pin */
  GPIO_InitStruct.Pin = LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin|LED_7_Pin
                          |LED_8_Pin|LED_9_Pin|LED_10_Pin|LED_11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
