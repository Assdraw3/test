#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool leap_year(int x)
{
	
	if ((x % 4 == 0) && (x % 100 != 0) || x % 400 == 0)
		return true;

	return false;
}

int Binary_Search(int tab[], int sz, int num)
{
	
	int left  = 0;
	int right = sz-1;
	
	
	while (left<= right)
	{
		int mid = left + (right - left) / 2;
		if (num > tab[mid])
		{
			right = right;
			left = mid+1;

		}
		else if (num < tab[mid])
		{
			left = left;
			right = mid-1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int main()
{
	for (int i = 1000; i <= 2024; i+=4)
	{
		if (leap_year(i))
			printf("%d\n", i);
	}
	int t[] = { 1,2,3,4,5,6,7,8,9,10,11 };
	for (int i = 1; i <= 12; i++)
	{
		printf("%d\n", Binary_Search(t, 11,i));

	}

	return 0;
}