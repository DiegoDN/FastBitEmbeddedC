#include <stdio.h>
#include <stdlib.h>

int main(void) {

	char a1 = 'A';
	/*
	char a2 = 'p';
	char a3 = 'p';
	char a4 = 'l';
	char a5 = 'e';
	char a6 = ':';
	//char a7 = ')';


	printf("Address of variable a1 = %p\n", &a1);
	printf("Address of variable a1 = %p\n", &a2);
	printf("Address of variable a1 = %p\n", &a3);
	printf("Address of variable a1 = %p\n", &a4);
	printf("Address of variable a1 = %p\n", &a5);
	printf("Address of variable a1 = %p\n", &a6);

	*/

	unsigned long long int addressOfa1 = ( unsigned long int ) &a1;

	printf("Address of variable a1 = %I64X\n", addressOfa1);

	return 0;
}
