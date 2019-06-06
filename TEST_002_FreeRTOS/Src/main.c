//=============================================================================
//
//=============================================================================

#include "main.h"
#include "cmsis_os.h"
#include "stm32f4xx.h"

//=============================================================================
//----------------function's prototype-----------------------------------------
//=============================================================================

void init_RCC(void);
void init_GPIO(void);

void task_switch_LED_GREEN(void *thread);
void task_switch_LED_ORANGE(void *thread);
void task_switch_LED_RED(void *thread);
void task_switch_LED_BLUE(void *thread);

//=============================================================================
//
//=============================================================================

int main(void){

	init_RCC();
	init_GPIO();

	xTaskCreate(task_switch_LED_GREEN, "blink_LED_GREEN",  128, NULL, 1, NULL);
	xTaskCreate(task_switch_LED_ORANGE,"blink_LED_ORANGE", 128, NULL, 1, NULL);
	xTaskCreate(task_switch_LED_RED,   "blink_LED_RED",    128, NULL, 1, NULL);
	xTaskCreate(task_switch_LED_BLUE,  "blink_LED_BLUE",   128, NULL, 1, NULL);
	vTaskStartScheduler();

  while (1){

	  GPIOD -> ODR |= GPIO_ODR_OD15;

  }
}

//=============================================================================
//
//=============================================================================

void init_RCC(void){

	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;

}

//=============================================================================
//
//=============================================================================

void init_GPIO(void){

	GPIOD -> MODER |= GPIO_MODER_MODER12_0;
	GPIOD -> MODER |= GPIO_MODER_MODER13_0;
	GPIOD -> MODER |= GPIO_MODER_MODER14_0;
	GPIOD -> MODER |= GPIO_MODER_MODER15_0;
}

//=============================================================================
//---------------------------tasks for FreeRTOS--------------------------------
//=============================================================================

void task_switch_LED_GREEN(void *thread){

	while (1){

		  GPIOD -> ODR |= GPIO_ODR_OD12;
		  vTaskDelay(500);
		  GPIOD -> ODR &= ~GPIO_ODR_OD12;
		  vTaskDelay(1500);
	}
}

//-----------------------------------------------------------------------------

void task_switch_LED_ORANGE(void *thread){

	while (1){

		  vTaskDelay(500);
		  GPIOD -> ODR |= GPIO_ODR_OD13;
		  vTaskDelay(500);
		  GPIOD -> ODR &= ~GPIO_ODR_OD13;
		  vTaskDelay(1000);
	}
}

//-----------------------------------------------------------------------------

void task_switch_LED_RED(void *thread){

	while (1){

		  vTaskDelay(1000);
		  GPIOD -> ODR |= GPIO_ODR_OD14;
		  vTaskDelay(500);
		  GPIOD -> ODR &= ~GPIO_ODR_OD14;
		  vTaskDelay(500);
	}
}

//-----------------------------------------------------------------------------

void task_switch_LED_BLUE(void *thread){

	while (1){

		vTaskDelay(1500);
		GPIOD -> ODR |= GPIO_ODR_OD15;
		vTaskDelay(500);
		GPIOD -> ODR &= ~GPIO_ODR_OD15;
	}
}




