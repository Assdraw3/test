#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//void step(int n0,int n,int *count)
//{
//	for (int i = 1;i<= 2;i++)
//	{
//		int x = n + i;
//		if (x < n0)
//		{
//			step(n0, x,count);
//		}
//		else if (x == n0)
//		{
//			(*count)++;
//		}
//		else
//		{
//			break;
//		}
//	}
//	
//}
void judge(int num[100][4], int n)
{
	int max = 0;
	for (int i = 0,sum = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			sum = sum + num[j][4] - num[j][3];
			if (sum > max)
			{
				max = sum;
			}
		}
	}
	printf("%d\n", max);

}

void range(int num [100][4],int clone[100][4],int n)
{
	for (int i = 0; i < n; i++)
	{
		int min = num[i][1] < num[i][2] ? num[i][1] : num[i][2];



	}

}
int main()
{
	int m = 0;
	int n = 0;
	int i = 0;
	int xi = 0;
	int yi = 0;
	scanf("%d %d", &n, &m);
	int num[100][4] = {0};
	int clone[100][4] = { 0 };
	for (i = 0; i < n - 1; i++)
	{
		scanf("%d", &num[i][0]);
		scanf("%d", &num[i][1]);
		scanf("%d", &num[i][2]);
		scanf("%d", &num[i][3]);

	}
	range(num,clone,n);
	judge(clone,n);
	for (i = 0; i < m; i++)
	{
		scanf("%d", &xi);
			
		scanf("%d", &yi);
		num[xi - 1][3] = yi;
		judge(clone,n);
	}
	return 0;
} 