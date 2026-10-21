#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void bubble(int arr[],int num)
{
	int container = 0;
	for (int j = 0; j < num - 1 ; j++)
	{
		for (int i = 0; i < num - 1 - j; i++)
		{

			if (arr[i] > arr[i + 1])
			{
				container = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = container;
			}


		}

	}
	


}

int main()
{
	
	/*int arr[4][4] = { {1,2,3,4},{11,12,13,14},{21,22,23,24},{31,32,33,34} };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <= 4; j++)
		{
			printf("%d\n", arr[i][j]);

		}

	}*/
	int tab[] = { 99,6,2,56,8,12,46,72,94 };
	bubble(tab,sizeof(tab)/sizeof(tab[0]));
	for (int i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
	{

		printf("%d\n", tab[i]);
	}
	return 0;
}