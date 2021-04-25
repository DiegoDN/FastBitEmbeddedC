#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include <stdint.h>
#include "main.h"

int main(void)
{
	RCC_AHB1ENR_t volatile *const pClockCtrlReg = ADDR_REG_AHB1ENR;
	GPIOx_MODER_t volatile *const pPortAModeReg = ADDR_REG_GPIOA_MODE;
	GPIOx_ODR_t volatile *const pPortAOutReg    = ADDR_REG_GPIOA_OD;
	

	//1. Enable the clock for GPIOA peripheral on AHB1ENR
	pClockCtrlReg->gpioa_en = CLOCK_ENABLE;

	//2. configure the mode of the IO pin as output
	//a. clear the  11 and 10 positions  dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 187
	pPortAModeReg->pin_5 = 0;

	//b. set 10 position as 1.
	pPortAModeReg->pin_5 = MODE_CONF_OUTPUT;

	//3. Set 5th bit of the output data register to make IO pin5 high dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 190
	pPortAOutReg->pin_5 = PIN_STATE_HIGH;


	while(1)
	{
		for (uint32_t i = 0; i < DELAY_COUNT; i++); //Small human observable delay
		pPortAOutReg->pin_5 = PIN_STATE_LOW;//led off
		for (uint32_t i = 0; i < DELAY_COUNT; i++); //Small human observable delay
		pPortAOutReg->pin_5 = PIN_STATE_LOW;//led on
	}

}
