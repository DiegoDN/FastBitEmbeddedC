#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{

	uint32_t num1, num2;
	uint32_t temp;

	printf("Enter 2 numbers (give space between nos): ");
	scanf("%d %d", &num1, &num2);

	temp = num1 & num2;
	printf("Bitwise AND (&): %d\n", temp);
	temp = num1 | num2;
	printf("Bitwise OR  (|): %d\n", temp);
	temp = num1 ^ num2;
	printf("Bitwise XOR (^): %d\n", temp);
	temp = ~num1;
	printf("Bitwise NOT (~): %d\n", temp);
	
	return EXIT_SUCCESS;
}
