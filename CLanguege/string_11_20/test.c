#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define AB 12;
#define CD AB+1;
//#include "use.c"
extern a;
int main()
{

	/*int arr[5][4] =
	{
		{1, 2, 3, 4,},
		{5, 6, 7, 8,},
		{9, 10 ,11, 12}
	};
	int (*parr)[4] = arr;
	printf("%d", *(*(parr+1)+2));*/
	int a = AB + CD;
	printf("%d", a);
	return 0;
}
