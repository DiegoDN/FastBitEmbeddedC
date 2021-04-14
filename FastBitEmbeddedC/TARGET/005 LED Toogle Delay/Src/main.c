/*
*	Procedure to turn on the Leds : Summary
*	1) Identify the GPIO port (a peripheral) used to connect the led
*	2) Identify the GPIO pin there the led is connected
*	3) Activate the GPIO peripheral (enable the clock)
*	4) Configure the GPIO pin mode as output
*	5) Write to the GPIO Pin
*
*   BOARD: Nucleo NUCLEO-F446RE - STM32F446RE = LED2 on PA5
*	BLOCK DIAGRAM: stm32f446re.pdf  PAGE 16
*	RCC BASE ADDRESS:  0x4002 3800 - 0x4002 3BFF     dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 57
*	AHB1ENR = RCC BASE + 0x30 = 0x4002 3830          dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 144
*	GPIOA BASE ADDRESS:  0x4002 0000 - 0x4002 03FF   dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 57
*	GPIOA MODE REGISTER:  0x4002 0000 + 0X00 = 0x4002 0000
*	GPIOA OUTPUT DATA: 0x4002 0000 + 0X14 = 0x4002 0014
*/


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include <stdint.h>

int main(void)
{
	
	uint32_t *pClockCtrlReg = (uint32_t *) 0x40023830;
	uint32_t *pPortAModeReg = (uint32_t *) 0x40020000;
	uint32_t *pPortAOutReg  = (uint32_t *) 0x40020014;
	
	//1. Enable the clock for GPIOA peripheral on AHB1ENR
	*pClockCtrlReg |= ( 1 << 0 ); //0x00000001

	//2. configure the mode of the IO pin as output
	//a. clear the  11 and 10 positions  dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 187
	//*pPortAModeReg &= ~( 3 <<10 ); //or you can write like this because 3 = 1 1
	*pPortAModeReg &= ~( 1 << 10 ); //0xFFFFF7FF
	*pPortAModeReg &= ~( 1 << 11 ); //0xFFFFF7FF

	//b. set 10 position as 1.
	*pPortAModeReg |= (1 << 10); //0x00000400

	//3. Set 5th bit of the output data register to make IO pin5 high dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 190
	*pPortAOutReg |= (1 << 5); //0x00000020

	while(1)
	{
		for (uint32_t i = 0; i < 100000; i++); //Small human observable delay
		*pPortAOutReg &= ~( 1 << 5 );//led off
		for (uint32_t i = 0; i < 100000; i++); //Small human observable delay
		*pPortAOutReg |= (1 << 5); //led on
	}

}
