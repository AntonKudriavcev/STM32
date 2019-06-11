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

	init_GPIO();

	init_RCC();

	SystemCoreClockUpdate();

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

	RCC -> CR |= RCC_CR_HSEON;                              // Enable HSE
	while(!(RCC -> CR & RCC_CR_HSERDY)){};                  // Waiting for ready start HSE

	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;                      // Set  AHB  Prescaler to 1 AHB  = SYSCLK/1
	RCC -> CFGR |= RCC_CFGR_PPRE1_DIV4;                     // Set  AHB1 Prescaler to 4 APB1 = HCLK/4
	RCC -> CFGR |= RCC_CFGR_PPRE2_DIV2;                     // Set  AHB2 Prescaler to 2 APB2 = HCLK/2

	RCC -> PLLCFGR &= ~RCC_PLLCFGR_PLLM_4;                  // Clear M prescaler
	RCC -> PLLCFGR &= ~RCC_PLLCFGR_PLLN_8;                  // Clear N multiplication
	RCC -> PLLCFGR &= ~RCC_PLLCFGR_PLLP_0;                  // Clear P prescaler

	RCC -> PLLCFGR |= RCC_PLLCFGR_PLLM_4;                   // Set M prescaler to 16
	RCC -> PLLCFGR |= RCC_PLLCFGR_PLLN_8;                   // Set N multiplication to 256
	RCC -> PLLCFGR |= RCC_PLLCFGR_PLLP_0;                   // Set P prescaler to 2

	RCC -> CR |= RCC_CR_PLLON;                              // enable PLL
	while(!(RCC -> CR & RCC_CR_PLLRDY)){};                  // wait till PLL is ready

	FLASH->ACR|=FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS | FLASH_ACR_PRFTEN;

	RCC -> CFGR &= ~RCC_CFGR_SW;                            // clear SW bits
	RCC -> CFGR |= RCC_CFGR_SW_PLL;                         // select source SYSCLK = PLL
	while((RCC -> CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1){};// wait till PLL is used

}

//=============================================================================
//
//=============================================================================

void init_GPIO(void){

	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;

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

