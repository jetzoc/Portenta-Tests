/*
 *  Test to access lower libaries directly from ST and ARM on Arduino platform
 *
 *  Required technologies/tools (2 Libraries): 
 *  - CMSIS (Cortex Microcontroller Software Inteface Standard)
 *    - Definitions for various registers in the Cortex-M and Cortex-A family
 *    - Closest to the metal
 *    - Defined by ARM
 *    - Vendor independent
 *  - STM32 HAL drivers (Hardware Abstraction Layer for STM32)
 *    - Embedded libraries for maximizing portability across STM32 MCUs
 *    - Available for all the hardware peripherals
 *      - .c file
 *      - .h file
 *        - example: 
 *          - stm32h7xx_hal_gpio.h 
 *          - stm32h7xx_hal_gpio.c
 *    - Defined by ST Microelectronics
 *
 *  Goal/Purpose of app: 
 *  Blinky on Blue LED
 *
 *  Notes:
 *  - LEDs on Portenta board are active LOW
 *    - RED LED = PK5
 *    - GREEN LED = PK6
 *    - BLUE LED = PK7
 *
 * Repo link: https://github.com/jetzoc/Portenta-Tests.git
 *  
 *  February 28, 2021
*/

/* Include libraries needed */ 
//#include <stdlib.h>
#include <stm32h7xx.h>

/* Function prototypes */ 
void stm32_hal_main(void);

/* Arduino main setup */ 
void setup() {


}

/* Arduino main loop */ 
void loop() {

  stm32_hal_main(); 
 
}

/* STM32 HAL driver main */ 
void stm32_hal_main(void) 
{
  /* Enable GPIO clk */
  __HAL_RCC_GPIOK_CLK_ENABLE();

  /* Define GPIO port and pin in one place */
  typedef struct gpio_pp 
  {

    GPIO_TypeDef* port;    // ports are pointers hence addresses
    uint16_t pin;

  } gpio_pp;
  
  /* Use newly created structure for one blue LED Port and Pin */ 
  gpio_pp led_b = { GPIOK, GPIO_PIN_7 };    // portenta blue led on PK7 (STM32 port/pin)

  /* Settings for GPIO pin */ 
  GPIO_InitTypeDef led_b_init = 
  {
    .Pin = led_b.pin,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW
    
  };
  
  /* Initialize the GPIO pin */ 
  HAL_GPIO_Init(led_b.port, &led_b_init);
  
  while (1) 
  {
    /* Blink the light */
    HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_RESET);  // turn on LED
    HAL_Delay(1000);      // 1s; delay slowed down enough for us to see

    HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_SET);  // turn off LED
    HAL_Delay(1000);
  }

}

