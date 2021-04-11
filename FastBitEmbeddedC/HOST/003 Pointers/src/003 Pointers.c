#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	
	char data = 100;
	printf("Value of char variable: %u\n", data);	
	printf("Address of char: %p\n", &data);

	char* pAddress = &data;
	char value = *pAddress;

	printf("Read of pointer variable: %u\n", value);

	*pAddress = 65;
	printf("Value of pointer variable: %u\n", *pAddress);	
	printf("Value of char variable: %u\n", data);

	return EXIT_SUCCESS;
}
