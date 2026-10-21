#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int ban[10] = { 0 };
int check(int x)
{
	if (x == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			ban[i] = 0;
		}
	}
	else
	{
		if (ban[x] == 0)
		{
			ban[x] = 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;

}
int Max(int tab[][10], int n, int root)//路径，大小，当前检查点
{
	int rest;
	ban[root] = 1;
	for (int j =1; j < n; j++)
	{
		if (tab[root][j] != 0 && check(root))
		{
		
			rest = tab[root][j];
			rest += Max(tab, n, j);
			
			
		}
		
	}
	ban[root] = 0;
	return rest;
}
int main()
{
	int pos[10][4] = {0};
	int count = 0;
	int n;//星系数量
	int m;//星系爆发次数
	int x, y;
	int w, b;
	int trail[10][10] = {0};//星系间路径图
	scanf("%d", &n);
	scanf("%d", &m);
	for (int i = 0; i < n - 1; i++)
	{
		
		

		scanf("%d", &x);
		scanf("%d", &y);
		scanf("%d", &w);
		scanf("%d", &b);
		trail[x][y] = b - w;
		trail[y][x] = b - w;
		count++;
		pos[count][0] = x;
		pos[count][1] = y;
		pos[count][2] = w;
		pos[count][3] = b - w;
	}//存放路径和损耗
	int temp = 0;//计算每次剩余物资
	int max = 0;//求最大物资
	for (int i = 1; i <= n; i++)
	{
		temp = Max(trail, n, i);
		if (max < temp)
		{
			max = temp;
			printf("%d\n",temp);
		}
	}
	printf("%d\n", max);
	for (int i = 0; i < m; i++)
	{
		
		scanf("%d", &count);
		scanf("%d", &w);
		trail[pos[count][0]][pos[count][1]] += pos[count][2] - w;
		trail[pos[count][1]][pos[count][0]] += pos[count][2] - w;
		for (int i = 1; i <= n; i++)
		{
			temp = Max(trail, n, i);
			if (max < temp)
			{
				max = temp;
				printf("%d\n", temp);
			}
		}
		printf("%d\n", max);
		trail[pos[count][0]][pos[count][1]] = pos[count][3];
		trail[pos[count][1]][pos[count][0]] = pos[count][3];
	}


	return 0;
}