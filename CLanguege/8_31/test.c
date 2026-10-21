#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void plus(int* x)
{
	*x = *x + 1;



}



int main()
{

	int num = 1;

	for (int i = 1; i <= 10; i++)
	{
		plus(&num);

	}
	printf("The value of num is %d.", num);

	return 0;
}