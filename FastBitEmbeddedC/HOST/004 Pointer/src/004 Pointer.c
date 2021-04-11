#include <stdio.h>
#include <stdlib.h>

long long int g_data = 0xFFFEABCD11112345;


int main(void) 
{
	printf("Value of Original data is: %I64x\n", g_data);
 	
	char *pAddress1;
	pAddress1 = (char *) &g_data;
	printf("Value at address %p is : %x\n", pAddress1, *pAddress1);

	short *pAddress2;
	pAddress2 = (short *) &g_data;
	printf("Value at address %p is : %x\n", pAddress2, *pAddress2);

	int *pAddress3;
	pAddress3 = (int *) &g_data;
	printf("Value at address %p is : %x\n", pAddress3, *pAddress3);

	long long int *pAddress4;
	pAddress4 = (long long int *) &g_data;
	printf("Value at address %p is : %I64x\n", pAddress4, *pAddress4);

	return EXIT_SUCCESS;
}
