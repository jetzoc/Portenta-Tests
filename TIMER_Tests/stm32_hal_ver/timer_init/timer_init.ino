/* 
 * Goal: 
 * To initialize a STM32 hardware timer 
 * on board the Portenta H7 
 * 
 * Hardware: 
 * TIM3 on STM32H7 MCU
 * PK1 (D1) = Digital output (Ch. 1 on scope)
 * D6 = Digital output (Ch. 2 on scope)
 *
 * Notes:
 * Using STM32 HAL drivers because Arduino nor Mbed libraries 
 * support hardware timers thus far.
 * 
 * Repo link: 
 * https://github.com/jetzoc/Portenta-Tests
 * 
 * March 5, 2021
 */

/* Include the STM32 HAL driver */ 
#include <stm32h7xx.h>

/* Arduino main setup */ 
void setup() {

  /* Digital output for timing purposes and keep it low */ 
  pinMode(6, OUTPUT);     // pin D6
  digitalWrite(6, LOW); 

  /* Set up the red LED and turn it off */ 
  //pinMode(LEDR, OUTPUT);  
  //digitalWrite(LEDR, HIGH);   

}

/* Arduino main loop */ 
void loop() {

  stm32_hal_main(); 
 
}

/* STM32 HAL driver main */ 
void stm32_hal_main(void) 
{
  /******** Set up blue LED for debugging purposes ********/
  /* Enable GPIO clk */
  __HAL_RCC_GPIOK_CLK_ENABLE();

  /* Define GPIO port and pin in one place */
  typedef struct gpio_pp 
  {

    GPIO_TypeDef* port;    // ports are pointers hence addresses
    uint16_t pin;

  } gpio_pp;
  
  /* Use newly created structure for a GPIO pin */ 
  gpio_pp led_b = { GPIOK, GPIO_PIN_7 };    // portenta blue led on PK7 (STM32 port/pin)

  /* Settings for GPIO pin: led_b */ 
  GPIO_InitTypeDef led_b_init = 
  {
    .Pin = led_b.pin,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW
    
  };
  
  /* Initialize the GPIO pin */ 
  HAL_GPIO_Init(led_b.port, &led_b_init);

  HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_SET);  // turn off LED

  /******** Set up a GPIO pin to toggle it ********/
  /* Use newly created structure for a GPIO pin */ 
  gpio_pp togl = { GPIOK, GPIO_PIN_1 };    // PK1 is D1 on Portenta board
  /* Settings for GPIO pin: togl */ 
  GPIO_InitTypeDef togl_init = 
  {
    .Pin = togl.pin,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW
   
  };
  
  /* Initialize the GPIO pin */ 
  HAL_GPIO_Init(togl.port, &togl_init);
  
  HAL_GPIO_WritePin(togl.port, togl.pin, GPIO_PIN_SET);  // idles HIGH

  /************** Setup TIMER ********************/ 
  /* Declare an instance of the TIM3 peripheral */
  TIM_HandleTypeDef tim;

  /* Fill in structure members */ 
  tim.Instance = TIM3;      
  tim.State = HAL_TIM_STATE_RESET; 
  
  TIM_Base_InitTypeDef tim_init =
  {
    .Prescaler = 0x0000,      // up to 0xFFFF
    .CounterMode = TIM_COUNTERMODE_UP,
    .Period = 0xFFFF,         // up to 0xFFFF
    .ClockDivision = TIM_CLOCKDIVISION_DIV1,
    .RepetitionCounter = 0x00,
    .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE
  };

  tim.Init = tim_init;        // fill in the init member
  
//  TIM_ClockConfigTypeDef tim_clk = 
//  {
//    .ClockSource = TIM_CLOCKSOURCE_INTERNAL,
//    .ClockPolarity = TIM_CLOCKPOLARITY_RISING,
//    .ClockPrescaler = TIM_CLOCKPRESCALER_DIV1,
//    .ClockFilter = 0x0
//  };
   
  /* Enable TIM3 clock */ 
  __HAL_RCC_TIM3_CLK_ENABLE(); 

  /* Configure clock source to be used */
  //HAL_TIM_ConfigClockSource(&tim, &tim_clk);

  /* Desired functionality: generate a time base on TIM3 */
  HAL_StatusTypeDef status; 
  
  /* Initialize timer with all given parameters */ 
  status = HAL_TIM_Base_Init(&tim); 

  /* Error check */ 
  if (status != HAL_OK)
  {
    HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_RESET);  // turn on LED
  }
  
  /* Start the timer */
  status = HAL_TIM_Base_Start(&tim); 

  /* Error check */ 
  if (status != HAL_OK)
  {
    HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_RESET);  // turn on LED
  }
  
  bool toggle = false; 

  while(1)
  {
    /* If timer counts has update event pending...
     * UIF = Update Interrupt Flag 
     * UIF == 1 in the status register lets us know
     * timer count overflowed! */ 
    if((tim.Instance->SR & TIM_SR_UIF) == TIM_SR_UIF) 
    {
      //digitalWrite(6, HIGH);

      /* Toggling using STM32 setup: PK1 */ 
      HAL_GPIO_TogglePin(togl.port, togl.pin);  // turn on LED
      
      /* Toggling using Arduino setup: D6 */ 
      if(!toggle)     
      {
        toggle = true; 
        digitalWrite(6, LOW);      
      }
      
      else              
      {
        toggle = false; 
        digitalWrite(6, HIGH);      
      }

//      HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_RESET);  // turn on LED

      /* Clear UIF bit */ 
      tim.Instance->SR &= ~TIM_SR_UIF;   // TIM_SR_UIF == 0x01

//      HAL_Delay(50); 
//      HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_SET);  // turn off LED
//      HAL_Delay(50); 

    } // end if statement
    
//    else 
//    {
//      //digitalWrite(6, LOW); 
//      HAL_GPIO_WritePin(led_b.port, led_b.pin, GPIO_PIN_SET);  // turn off LED
//    }
    
  };  // end while(1)

}

//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
//{
//  UNUSED(htim); 
//}

/*
 * Results:
 *  328.0 us; timer set @ 3.05KHz
 *  when period set to 0xFFFF
 *  Counts all the way up; uses all 16-bits
 */
