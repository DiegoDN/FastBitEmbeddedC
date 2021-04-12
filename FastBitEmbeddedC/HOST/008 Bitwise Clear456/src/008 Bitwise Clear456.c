#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{

	int32_t num1;
	int32_t temp;
	int32_t mask1 = 0b10001111; //0x8F
	int32_t mask2 = 0b01110000; 

	printf("Enter a number: ");
	scanf("%d", &num1);

	temp = num1 & mask1; //use bitwise OR to set the bits

	printf("[input]  [output] : 0x%X 0x%X\n", num1, temp);

	temp = num1 & ~mask2; //use bitwise OR to set the bits

	printf("[input]  [output] : 0x%X 0x%X\n", num1, temp);

	return EXIT_SUCCESS;
}

