/* 
 * Goal: 
 * To modify the frequency of a STM32 hardware timer 
 * on board the Portenta H7 
 * 
 * Hardware: 
 *  - TIM3 on STM32H7 MCU
 *  - D6 = Digital output (Ch. 1 on scope)
 *
 * Notes:
 * Using STM32 HAL drivers because Arduino nor Mbed libraries 
 * support hardware timers thus far.
 * 
 * Using basic Arduino setup for timing pin and debug LED 
 * for simplicity. 
 *
 * If LEDR is not ON, no HAL_ERROR occured in each STM32 HAL function.
 * 
 * Adjust the .Period member of the TIM_Base_InitTypeDef structure
 *    .Period = 0xFFFF results in 3 KHz TIMER overflow (328 us)
 *    .Period = 0x7FFF results in 6 KHz TIMER overflow (164 us)
 *    .Period = 0x1 results in 3.4 MHz TIMER overflow (290 ns)
 * 
 * For 1 KHz TIMER
 *    .Prescaler = 0x2 or 0x5
 *    .Period = 0xFFFF or 0x7FFF
 * 
 * For 610 Hz TIMER (609.7)
 *    .Prescaler = 0x4 
 *    .Period = 0xFFFF 
 * 
 * For 600 Hz TIMER (602.4 Hz)
 *    .Prescaler = 0x05
 *    .Period = 0xD555
 * 
 * Repo link: 
 * https://github.com/jetzoc/Portenta-Tests
 * 
 * March 7, 2021
 */

/* Include the STM32 HAL driver */ 
#include <stm32h7xx.h>

/* Arduino main setup */ 
void setup() {

  /* Digital output for timing purposes and keep it low */ 
  pinMode(6, OUTPUT);     // pin D6
  digitalWrite(6, HIGH);  // idle high

  /* Set up the red LED and turn it off */ 
  pinMode(LEDR, OUTPUT);   
  digitalWrite(LEDR, HIGH);   

}

/* Arduino main loop */ 
void loop() {

  stm32_hal_main(); 
 
}

/* STM32 HAL driver main */ 
void stm32_hal_main(void) 
{
  /************** Setup TIMER ********************/ 
  /* Declare an instance of the TIM3 peripheral */
  TIM_HandleTypeDef tim;

  /* Fill in structure members */ 
  tim.Instance = TIM3;      
  tim.State = HAL_TIM_STATE_RESET; 
  
  TIM_Base_InitTypeDef tim_init =
  {
    .Prescaler = 0x4,      // up to 0xFFFF
    .CounterMode = TIM_COUNTERMODE_UP,
    .Period = 0xFFFF,      // up to 0xFFFF
    .ClockDivision = TIM_CLOCKDIVISION_DIV1,
    .RepetitionCounter = 0x00,
    .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE
  };

  tim.Init = tim_init;        // fill in the init member
  
  /* Optional: Specify timer src clk.
   * Default: Internal clk of MCU */
  // TIM_ClockConfigTypeDef tim_clk = 
  // {
  //   .ClockSource = TIM_CLOCKSOURCE_INTERNAL,
  //   .ClockPolarity = TIM_CLOCKPOLARITY_RISING,
  //   .ClockPrescaler = TIM_CLOCKPRESCALER_DIV1,
  //   .ClockFilter = 0x0
  // }; 
  
  /* Enable TIM3 clock */ 
  __HAL_RCC_TIM3_CLK_ENABLE(); 

  /* Function status placeholder for STM32 driver */ 
  HAL_StatusTypeDef status; 
  
  // /* Configure clock source to be used */
  // status = HAL_TIM_ConfigClockSource(&tim, &tim_clk);
  
  // /* Error check */ 
  // if (status != HAL_OK)
  // {
  //   digitalWrite(LEDR, LOW); 
  // }
  
  /* Desired functionality: generate a time base on TIM3 */
  /* Initialize timer with all given parameters */ 
  status = HAL_TIM_Base_Init(&tim); 

  /* Error check */ 
  if (status != HAL_OK)
  {
    digitalWrite(LEDR, LOW); 
  }
  
  /* Start the timer */
  status = HAL_TIM_Base_Start(&tim); 

  /* Error check */ 
  if (status != HAL_OK)
  {
    digitalWrite(LEDR, LOW); 
  }
  
  /* Toggle state tracker */ 
  bool toggle = false; 

  /***************** Main loop ********************/
  while(1)
  {
    /* If timer counts has update event pending...
     * UIF = Update Interrupt Flag 
     * UIF == 1 in the status register lets us know
     * timer count overflowed! */ 
    if((tim.Instance->SR & TIM_SR_UIF) == TIM_SR_UIF) 
    {

      /* Toggling using Arduino setup: D6 */ 
      if(!toggle)       // previously high; haven't toggled yet
      {
        toggle = true;              // going to toggle now
        digitalWrite(6, LOW);       // change to low
      }
      
      else              
      {
        toggle = false;             // we have toggled before
        digitalWrite(6, HIGH);      // change to high again
      }

      /* Clear UIF bit for the next count overflow */ 
      tim.Instance->SR &= ~TIM_SR_UIF;   // TIM_SR_UIF == 0x01

    } // end if statement
    
  };  // end while(1)

}

/*
 * Results:
 *    .Period = 0xFFFF => 3KHz
 *    .Period = 0x7FFF => 6KHz
 *    .Period = 0x1 => 3.4 MHz
 */
