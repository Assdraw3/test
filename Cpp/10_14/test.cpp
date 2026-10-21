#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//µİ¹éÇóÎ¨Ò»Â·¾¶
int count = 0;
int route(int num[100][4],int n,int x,int y)
{
	for (int i = 0; i < n-1; i++)
	{
		for (int j = i+1;j<n;j++)
		{
			if (num[i][1] == num[j][1] || num[i][0] == num[j][0] || num[i][0] == num[j][1] || num[i][1] == num[j][0])
			{
				route(num, n, num[j][0], num[j][1]);
			}
		}
	}
	return 0;
}
int main()
{
	int num1 = 0;
	std::cin >> num1;
	//yi == x(i+1)


	return 0;
}
//count of line