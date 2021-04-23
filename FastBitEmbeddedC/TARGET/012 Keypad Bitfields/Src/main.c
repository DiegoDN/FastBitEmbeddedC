//datasheet DS dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics 



#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include <stdint.h>
#include "main.h"

//GLOBAL VARIABLES
uint8_t colC1Status = 1;
uint8_t colC2Status = 1;
uint8_t colC3Status = 1;
uint8_t colC4Status = 1;

//PERIPHERALS REGISTERS ADDRESS
RCC_AHB1ENR_t volatile *const pClockCtrlReg = (RCC_AHB1ENR_t *)  0x40023830;
GPIOx_MODER_t volatile *const pPortAModeReg = (GPIOx_MODER_t *)  0x40020000;
GPIOx_MODER_t volatile *const pPortBModeReg = (GPIOx_MODER_t *)  0x40020400;
GPIOx_ODR_t   volatile *const pPortAOutReg  = (GPIOx_ODR_t *)   (0x40020000 + 0x14);
GPIOx_IDR_t   volatile *const pPortBInReg   = (GPIOx_IDR_t *)   (0x40020400 + 0x10);
GPIOx_PUPDR_t volatile *const pPortBPUPDReg = (GPIOx_PUPDR_t *) (0x40020400 + 0x0C);

//FUNCTIONS PROTOTYPES
void delay(void);
void ledblink(void);


int main(void)
{

	//1. Enable the clock for GPIOA and GPIOB peripherals on AHB1ENR
	pClockCtrlReg->gpioa_en = 1;
	pClockCtrlReg->gpiob_en = 1;

	//2. configure the mode of the IO pin as outputs. First Clear then configure  DS-PAGE 187
	//clear
	pPortAModeReg->pin_5 = 0;  //pa5 led
	pPortAModeReg->pin_9 = 0;  //pa9
	pPortAModeReg->pin_7 = 0;  //pa7
	pPortAModeReg->pin_10 = 0; //pa10
	pPortAModeReg->pin_8 = 0;  //pa8
	//configure
	pPortAModeReg->pin_5 = 1;  //pa5
	pPortAModeReg->pin_9 = 1;  //pa9
	pPortAModeReg->pin_7 = 1;  //pa7
	pPortAModeReg->pin_10 = 1; //pa10
	pPortAModeReg->pin_8 = 1;  //pa8
	
	//3. configure the mode of the IO pin as inputs. DS-PAGE 187
	//clear
	pPortBModeReg->pin_3 = 0;  //pb3
	pPortBModeReg->pin_5 = 0;  //pb5
	pPortBModeReg->pin_4 = 0;  //pb4
	pPortBModeReg->pin_10 = 0; //pb10
	
	//4. configure the internal pull up registors for the inputs DS-PAGE 189
	//clear
	pPortBPUPDReg->pin_3 = 0;
	pPortBPUPDReg->pin_5 = 0;
	pPortBPUPDReg->pin_4 = 0;
	pPortBPUPDReg->pin_10 = 0;
	//configure
	pPortBPUPDReg->pin_3 = 1;
	pPortBPUPDReg->pin_5 = 1;
	pPortBPUPDReg->pin_4 = 1;
	pPortBPUPDReg->pin_10 = 1;

	//5. Set all outputs as High
	pPortAOutReg->pin_9 = 1;  //pa9
	pPortAOutReg->pin_7 = 1;  //pa7
	pPortAOutReg->pin_10 = 1; //pa10
	pPortAOutReg->pin_8 = 1;  //pa8

	while(1)
	{

		pPortAOutReg->pin_9 = 0;  //R1 LOW
		colC1Status = pPortBInReg->pin_3;
		colC2Status = pPortBInReg->pin_5;
		colC3Status = pPortBInReg->pin_4;
		colC4Status = pPortBInReg->pin_10;

		if(!colC1Status)
		{
			delay();
			printf("1");
			ledblink();
		}

		else if(!colC2Status)
		{
			delay();
			printf("2");
			ledblink();
		}

		else if(!colC3Status)
		{
			delay();
			printf("3");
			ledblink();
		}

		else if(!colC4Status)
		{
			delay();
			printf("A");
			ledblink();
		}

		pPortAOutReg->pin_9 = 1;  //R1 HIGH
		pPortAOutReg->pin_7 = 0;  //R2 LOW

		colC1Status = pPortBInReg->pin_3;
		colC2Status = pPortBInReg->pin_5;
		colC3Status = pPortBInReg->pin_4;
		colC4Status = pPortBInReg->pin_10;

		if(!colC1Status)
		{
			delay();
			printf("4");
			ledblink();
		}

		else if(!colC2Status)
		{
			delay();
			printf("5");
			ledblink();
		}

		else if(!colC3Status)
		{
			delay();
			printf("6");
			ledblink();
		}

		else if(!colC4Status)
		{
			delay();
			printf("B");
			ledblink();
		}

		pPortAOutReg->pin_7 = 1;  //R2 HIGH
		pPortAOutReg->pin_10 = 0;  //R3 LOW

		colC1Status = pPortBInReg->pin_3;
		colC2Status = pPortBInReg->pin_5;
		colC3Status = pPortBInReg->pin_4;
		colC4Status = pPortBInReg->pin_10;

		if(!colC1Status)
		{
			delay();
			printf("7");
			ledblink();
		}

		else if(!colC2Status)
		{
			delay();
			printf("8");
			ledblink();
		}

		else if(!colC3Status)
		{
			delay();
			printf("9");
			ledblink();
		}

		else if(!colC4Status)
		{
			delay();
			printf("C");
			ledblink();
		}

		pPortAOutReg->pin_10 = 1;  //R3 HIGH
		pPortAOutReg->pin_8 = 0;  //R4 LOW

		colC1Status = pPortBInReg->pin_3;
		colC2Status = pPortBInReg->pin_5;
		colC3Status = pPortBInReg->pin_4;
		colC4Status = pPortBInReg->pin_10;

		if(!colC1Status)
		{
			delay();
			printf("*");
			ledblink();
		}

		else if(!colC2Status)
		{
			delay();
			printf("0");
			ledblink();
		}

		else if(!colC3Status)
		{
			delay();
			printf("#");
			ledblink();
		}

		else if(!colC4Status)
		{
			delay();
			printf("D");
			ledblink();
		}

		pPortAOutReg->pin_8 = 1;  //R4 HIGH

	}
}

void delay(void)
{
	for(uint32_t i =0 ; i < 300000 ; i++);
}

void ledblink(void)
{
	pPortAOutReg->pin_5 = 1;
	for (uint32_t i = 0; i < 100000; i++); //Small human observable delay
	pPortAOutReg->pin_5 = 0;//led off
	for (uint32_t i = 0; i < 100000; i++); //Small human observable delay
	printf("Hello World4!\n");
}