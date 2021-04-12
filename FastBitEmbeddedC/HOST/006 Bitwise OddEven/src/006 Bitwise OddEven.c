#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{

	int32_t num1;
	int32_t temp;

	printf("Enter a number: ");
	scanf("%d", &num1);

	temp = num1 & 1;

	if (temp)
	{
		printf("The number is odd");
	}
	else
	{
		printf("The number is even");
	}

	return EXIT_SUCCESS;
}
