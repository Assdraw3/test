#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print(float* f)
{
	unsigned char* c = (unsigned char*)f;
	for (int i = 3; i >= 0; i--)
	{
		printf("%.2x", *(c + i));
	}
}

int main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int len = sizeof(array) / sizeof(array[0]);
	
	int left = 0;
	int right = len - 1;
	int temp;
	while (left < right)
	{
		while ((left < right) && array[left] % 2 != 0)
		{
			left++;
			
		}
		while ((left < right) && array[right] % 2 != 1)
		{
			right--;

		}
		temp = array[left];
		array[left] = array[right];
		array[right] = temp;


		left++;
		right--;
	}
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", array[i]);
	}
	float f1 = -22.5f;
	float f2 = 3.1415926;
	int n = 0xC1B40000;
	float* pf = (float*)&n;
	print(&f2);
	printf("%f", f2);
	int n = 0xc1b40000;
	float* pf = (float*) &n;

	if (f1 == *pf)
	{
		printf("yes");

	}
	else
	{
		printf("no");
	}
	

	return 0;
}