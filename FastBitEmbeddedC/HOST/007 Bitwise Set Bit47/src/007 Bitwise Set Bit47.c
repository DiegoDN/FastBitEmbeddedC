#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{

	int32_t num1;
	int32_t temp;
	int32_t mask = 0b10010000; //0x90

	printf("Enter a number: ");
	scanf("%d", &num1);

	temp = num1 | mask; //use bitwise OR to set the bits

	printf("[input]  [output] : 0x%X 0x%X\n", num1, temp);

	return EXIT_SUCCESS;
}
