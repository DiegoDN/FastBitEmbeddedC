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
	
	uint32_t volatile *pClockCtrlReg = (uint32_t *) 0x40023830;
	uint32_t volatile *pPortAModeReg = (uint32_t *) 0x40020000;
	uint32_t volatile *pPortAOutReg  = (uint32_t *) 0x40020014;
	uint32_t volatile *pPortAInReg   = (uint32_t *) 0x40020010;

	//Enable the clock for GPIOA peripheral on AHB1ENR
	*pClockCtrlReg |= ( 1 << 0 ); //0x00000001

	//Configure the mode of the IO pin as output - PA5
	//clear the  11 and 10 positions  dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 187
	*pPortAModeReg &= ~( 1 << 10 ); //0xFFFFF7FF
	*pPortAModeReg &= ~( 1 << 11 ); //0xFFFFF7FF
	//configure PA5 as output: set 10 position as 1.
	*pPortAModeReg |= ( 1 << 10 ); //0x00000400

	//Configure the mode of the IO pin as input - PA1 //I choose PA1 because PA0 is not avaiable on Nucleo 446RE (its used as wakeup pin)
	//clear the 1st position  dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 187
	*pPortAModeReg &= ~( 1 << 2 );
	*pPortAModeReg &= ~( 1 << 3 );

	//configure PA1 as input// doesn't need to because reset state is 00.
	*pPortAModeReg &= ~( 1 << 2 );
	*pPortAModeReg &= ~( 1 << 3 );

	//read the pin status of PA1
	uint8_t pinStatus = (uint8_t)(*pPortAInReg & 0x2);

	while(1)
	{
		if (pinStatus)
		{
			*pPortAOutReg |= ( 1 << 5 );//led on
		}
		else
		{
			*pPortAOutReg &= ~( 1 << 5 );//led off
		}

		pinStatus = (uint8_t)(*pPortAInReg & 0x2);  //read again.

	}

}
