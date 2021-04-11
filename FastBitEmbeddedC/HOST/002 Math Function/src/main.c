#include <stdio.h>
#include "math.h"

int main(void)
{

	printf("Add : %X\n", math_add(0x0FFF1111, 0x0FFF1111));
	printf("subs : %X\n", math_subs(0x0FFF1111, 0x00001111));
	printf("Mul : %X\n", math_mult(0x0FFF1111, 0x0FFF1111));
	printf("Div : %0.2f\n", math_div(100, 8));

	return 0;

}
