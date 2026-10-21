#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void show(char *tab)
{
	char tmp = *tab;
	int len = strlen(tab);
	*tab = *(tab + len - 1);
	*(tab + len - 1 )= '\0';
	if (strlen(tab + 1) >= 2)
	{
		show(tab + 1);
	}
	*(tab + len - 1) = tmp;
}
void reverse(char tab[])
{
	int n = 0;
	int left = 0;
	int right = 0;
	int container = 0;
	while (tab[n] != '\0')
	{
		n++;
	}
	right = n - 1;
	while (left < right)
	{
		container = tab[left];
		tab[left] = tab[right];
		tab[right] = container;
		left++;
		right--;
	}


}

int psum(int num)
{
	int sum = num % 10;
	if ((num / 10) != 0)
	{
		sum = psum(num / 10) + sum;

	}
	
	return sum;
}

double Pow(int n,int k)
{
	int sum = n;
	if (k == 0)
	{
		return 1;
	}
	else if (k < 0)
	{

		return (1.0 / Pow(n, -k));
	}
	if (k > 1)
	{
		sum = sum * Pow(n, k - 1);


	}
	return sum;
}

int main()
{
	/*char arr[] = "akasama";
	reverse(arr);
	printf("%s\n",arr);
	show(arr);
	printf("%s\n", arr);*/
	printf("%lf", Pow(2,-3));
	return 0;
}