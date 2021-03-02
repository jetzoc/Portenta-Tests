/*
 * Goal: 
 * Write one-bit to one GPIO pin 
 *    - once high and once low
 *    - time it
 *
 * Hardware: 
 * A1 = analog input on Portenta
 *    - STM32 MCU H7 pin: PA1_C 
 * 
 * 
 * Notes: 
 * Try out one of the three functions at a time; comment out the others
 *    1) sendHigh
 *    2) sendLow
 *    3) sendHighLow
 * 
 * Repo link: https://github.com/jetzoc/Portenta-Tests.git
 * 
 * March 2, 2021
 */

/* Include libraries needed */
#include <stm32h7xx.h>

/* Prototype for new 'main' function */
void stm32_hal_main(void); 

/* Define GPIO port and pin in one place (global) */
typedef struct gpio_pp 
{
  GPIO_TypeDef* port;    // ports are pointers hence addresses
  uint16_t pin;

} Gpio_pp;

/* Function prototypes for high and low toggling */ 
void sendHigh(Gpio_pp* gpio);
void sendLow(Gpio_pp* gpio);
void sendHighLow(Gpio_pp * gpio);

/* Arduino main setup */ 
void setup() {

}

/* Arduino main loop */ 
void loop() {

  stm32_hal_main(); 

}

/**
 * @brief STM32 HAL driver main 
 */ 
void stm32_hal_main(void)
{
  /* Enable GPIO port clk */ 
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Create one gpio pin/port structure */
  Gpio_pp a_out = { GPIOC, GPIO_PIN_2 };
  
  /* Settings for the gpio pin */
  GPIO_InitTypeDef a_out_init = 
  {
    .Pin = a_out.pin,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLDOWN,
    .Speed = GPIO_SPEED_FREQ_LOW

  };

  /* Initialize the GPIO pin */
  HAL_GPIO_Init(a_out.port, &a_out_init);

  while(1)
  {
    /* Set gpio high */
    //sendHigh(&a_out);
    
    /* Set gpio low */
    //sendLow(&a_out);

    /* Toggle gpio pin */ 
    sendHighLow(&a_out);    // toggles @ 150ns or 6.67 MHz
  }
}

/**
 * @brief Writes logic high to a pin
 * @param[in] gpio    pointer to gpio port and pin structure
 */
void sendHigh(Gpio_pp* gpio) 
{
  HAL_GPIO_WritePin(gpio->port, gpio->pin, GPIO_PIN_SET);
}

/** 
 * @brief Writes logic low to a pin
 * @param[in] gpio    pointer to gpio port and pin structure
 */
void sendLow(Gpio_pp* gpio) 
{
  HAL_GPIO_WritePin(gpio->port, gpio->pin, GPIO_PIN_RESET);
}

/**
 * @brief Toggle a pin high and low
 * @param[in] gpio    pointer to gpio port and pin structure
 */
void sendHighLow(Gpio_pp * gpio)
{
  HAL_GPIO_TogglePin(gpio->port, gpio->pin);
}