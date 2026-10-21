#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main()
{
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	for (int i = 100; i < 1000; i++)
	{
		n1 = i % 10;
		n2 = i / 10 % 10;
		n3 = i / 100 % 10;
		if (pow(n1, 3) + pow(n2, 3) + pow(n3, 3) == i)
			printf("%d ",i);

	}
	return 0;
}