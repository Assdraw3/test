#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>

int Max(int num,...)
{
	int k = 0;
	va_list con;
	va_start(con, num);
	int sum = va_arg(con, int);
	for (int i = 1; i < num; i++)
	{
		
		k = va_arg(con, int);
		printf("test == %d\n",k);
		sum =  k > sum ? k : sum;

	}
	va_end(con);
	return sum;
}






int main()
{
	/*int n = 0;
	printf("How many numbers do you want to compare?\n");
	scanf("%d",&n);
	printf("%d\n", Max(10, 87,29,89,36,54,66,12,2,1,7));*/
	for (int i = 1; i < 10; i++)
	{
		printf("\n");
		for (int j = 1; j <10; j++)
		{
			printf("%2d ",i*j);

		}

	}

	return 0;
}