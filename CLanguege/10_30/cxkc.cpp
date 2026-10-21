#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main()
{
	while (1)
	{
		int n = 0;
		scanf("%d", &n);
		int mid = (n + 1) / 2;
		int count = -1;
		for (int i = 0; i < n; i++)
		{
			i < mid ? count++ : count--;
			for (int j = 1; j <= n; j++)
			{

				if (abs(j - mid) <= count)
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}

			}

			//printf("%d\n", count);
			printf("\n");
		}

	}
	



	return 0;
}