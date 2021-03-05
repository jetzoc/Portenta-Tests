/*
 * Goal: 
 * Write one-bit to one GPIO pin 
 *    - set output to HIGH
 *    - time it with another pin
 *
 * Hardware: 
 * A4 = analog input on Portenta (Ch 1. on scope)
 *    - STM32 MCU H7 pin: PC2
 * 
 * D6 = digital input on Portenta (Ch 2. on scope)
 *    - STM32 MCU H7 pin: PA8
 * 
 * Notes: 
 * Try out one of the two functions at a time; comment out the other
 *    1) sendHigh
 *    2) sendLow
 * 
 * Would like to measure the result again with a digital analyzer (another time)
 * 
 * Repo link: https://github.com/jetzoc/Portenta-Tests.git
 * 
 * Drafted: March 2, 2021
 * Revisited: March 3, 2021
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
  /**********************************************/
  /** Set-up for a single GPIO pin to write to **/ 
  /* Enable GPIO port clk */ 
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Create one gpio pin/port structure */
  Gpio_pp out = { GPIOC, GPIO_PIN_2 };      // PC2 on STM32
  
  /* Settings for the gpio pin */
  GPIO_InitTypeDef out_init = 
  {
    .Pin = out.pin,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLDOWN,
    .Speed = GPIO_SPEED_FREQ_LOW

  };

  /* Initialize the GPIO pin */
  HAL_GPIO_Init(out.port, &out_init);

  /***************************************************/
  /* Set-up for another GPIO pin for timing purposes */ 
  /* Enable GPIO port clk */ 
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Create one gpio pin/port structure */
  Gpio_pp tim = { GPIOA, GPIO_PIN_8 };      // PA8 on STM32
  
  /* Settings for the gpio pin */
  GPIO_InitTypeDef tim_init = 
  {
    .Pin = tim.pin,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLDOWN,
    .Speed = GPIO_SPEED_FREQ_LOW

  };

  /* Initialize the GPIO pin */
  HAL_GPIO_Init(tim.port, &tim_init);


  /************* Loop *****************/ 
  while(1)
  {
    /****** No wrapper functions ******/ 
    /* Set timing pin high */ 
    HAL_GPIO_WritePin(tim.port, tim.pin, GPIO_PIN_SET); 

    /* Set gpio high */     
    HAL_GPIO_WritePin(out.port, out.pin, GPIO_PIN_SET); 

    /* Set timing pin low */ 
    HAL_GPIO_WritePin(tim.port, tim.pin, GPIO_PIN_RESET); 


//    /****** With wrapper functions ******/
//    /* Set timing pin high */ 
//    sendHigh(&tim); 
//    
//    /* Set gpio high */     
//    sendHigh(&out);        
//    
//    /* Set timing pin low */ 
//    sendLow(&tim); 

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
