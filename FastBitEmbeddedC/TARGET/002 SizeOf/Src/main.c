/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>

int main(void)
{
	printf("Hello World!\n");
	printf("Size of char data type is: %u\n", sizeof(char));
	printf("Size of short data type is: %u\n", sizeof(short));
	printf("Size of int data type is: %u\n", sizeof(int));
	printf("Size of long data type is: %u\n", sizeof(long));
	printf("Size of long long data type is: %u\n", sizeof(long long));
	printf("Size of float data type is: %u\n", sizeof(float));
	printf("Size of double data type is: %u\n", sizeof(double));

	for(;;);
}
