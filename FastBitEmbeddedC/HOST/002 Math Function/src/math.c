#include <stdio.h>

int math_add (int a, int b);
int math_subs (int a, int b);
long long int math_mult (int a, int b);
float math_div (int a, int b);


int math_add (int a, int b)
{
	int result;
	result = a + b;
	return result;
}

int math_subs (int a, int b)
{
	int result;
	result = a - b;
	return result;
}

long long int math_mult (int a, int b)
{
	int result;
	result =  a * b;
	return (long long int) result;
}

float math_div (int a, int b)
{
	float resultDivision;
	resultDivision = a % b;
	return resultDivision;
}
