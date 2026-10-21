#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void outputf(int num)
{
	if (num >= 10)
	{
		outputf(num / 10);
	}

	printf("%d\n", num % 10);
	

}

int Mul(int x)
{
	if (x > 1)
	{
		x = x * Mul(x - 1);
	}
	else
	{
		x = 1;
	}
	return x;
}

void itazura()
{
	printf("Hello World\n");
	itazura();
}

int main()
{

	itazura();

	outputf(1256);
	
	return 0;
}