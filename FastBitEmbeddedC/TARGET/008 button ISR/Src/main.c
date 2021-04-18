#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include <stdint.h>


//global shared variable between main code and ISR
uint8_t volatile g_button_pressed = 0;
uint8_t volatile ledStatus = 1;
uint32_t g_button_press_count = 0;

//registers mapping
uint32_t volatile *pClockCtrlRegAHB1	    = (uint32_t *) (0x40023800 + 0x30);
uint32_t volatile *pClockCtrlRegAPB2        = (uint32_t *) (0x40023800 + 0x44);

uint32_t volatile *pEXTIMaskReg 			= (uint32_t *) (0x40013C00 + 0x00);
uint32_t volatile *pEXTTIEdgeCtrlReg		= (uint32_t *) (0x40013C00 + 0x08); //datasheet 197
uint32_t volatile *pEXTTIPendReg			= (uint32_t *) (0x40013C00 + 0x14); //datasheet 199

uint32_t volatile *pNVICISER1	 			= (uint32_t *) (0xE000E100 + 0x04);
uint32_t volatile *pNVICEXTICR4	 			= (uint32_t *) (0x40013800 + 0x14);

uint32_t volatile *pPortAModeReg    	    = (uint32_t *) (0x40020000 + 0x00);
uint32_t volatile *pPortAOutReg    			= (uint32_t *) (0x40020000 + 0x14);


//function prototype
void button_init(void);
void led_init(void);


int main(void)
{
	button_init();
	led_init();

	while(1)
	{
		//Disable interrupt
		*pEXTIMaskReg &= ~( 1 << 13 );

		if(g_button_pressed)
		{
			//Some delay until button debouncing gets over
			for(uint32_t volatile i = 0; i < 500000; i++);

			g_button_press_count++;
			
			printf("Button is pressed : %lu\n",g_button_press_count);

			if(ledStatus)
			{
				*pPortAOutReg |= ( 1 << 5 );//led on
				ledStatus = 0;
			}
			else
			{
				*pPortAOutReg &= ~( 1 << 5 );//led off
				ledStatus = 1;
			}
			

			g_button_pressed = 0;
		}

		//Enable interrupt
		*pEXTIMaskReg |= ( 1 << 13  );
	}
}


void button_init(void)
{

  // Button is connected on PC13 on NUCLEO446RE - GPIOC port 13
  *pClockCtrlRegAHB1 |= ( 1 << 2 );

  //Led is connected on PA5 on NUCLEO446RE - GPIOA port 5
  *pClockCtrlRegAHB1 |= ( 1 << 0 );

  //ENABLE APB2 - SYSCFG EN
  *pClockCtrlRegAPB2 |= ( 1 << 14 );

  //SETTING UP PORT EXTI 15_10 FOR PC13
  *pNVICEXTICR4 &= ~( 0x2 << 4 );   //datasheet pg 199
  *pNVICEXTICR4 |= ( 1 << 5 );      //datasheet pg 199

  *pEXTTIEdgeCtrlReg |= ( 1 << 13 ); //0010 PC 13
  *pEXTIMaskReg      |= ( 1 << 13 );

  //IRQ CONFIG
  *pNVICISER1 |= (1 << (8)); //EXTI2 Lin2 2 interrupt datasheet pg 239

}


void led_init(void)
{
	//Configure the mode of the IO pin as output - PA5
	//clear the  11 and 10 positions  dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics PAGE 187
	*pPortAModeReg &= ~( 1 << 10 ); //0xFFFFF7FF
	*pPortAModeReg &= ~( 1 << 11 ); //0xFFFFF7FF

	//configure PA5 as output: set 10 position as 1.
	*pPortAModeReg |= ( 1 << 10 ); //0x00000400
}


/* This is button interrupt handler*/
void EXTI15_10_IRQHandler(void)
{

	if( *pEXTTIPendReg & (1 << 13))
	{
		*pEXTTIPendReg |= ( 1 << 13  );
	}

	g_button_pressed = 1;

}
