#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Min(int tab[],short n1,short n2)
{
	int co = tab[n1];
	for (int i = n1; i < n2; i++)
	{

		if (co > tab[i])
			co = tab[i];
	}
	return co;
}

double average(int tab[],int n1,int n2)
{
	double sum = 0;
	for (int i = n1; i < n2; i++)
	{
		sum = tab[i] + sum;
		

	}
	return ((sum-Min(tab,n1,n2)) / (n2  - n1-1));
}

int main()
{
	
	printf("n=?\n");
	int n = 0;
	int arr[1000] = {0};
	double max = 0;
	double con = 0;
	scanf("%d",&n );
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
		

	}
	for (int i = 0; i < n-1; i++)
	{
		con = average(arr, i,n);
		printf("average=%lf,eat = %d\n", con, i);
		if (max < con)
		{
			max = con;
		}

	}
	for (int i = 0; i < n - 1; i++)
	{
		con = average(arr, i, n);
		if (con == max)
		{
			printf("%d\n",i);
		}

	}
	int over = 0;
	scanf("%d",&over);
	return 0;
}