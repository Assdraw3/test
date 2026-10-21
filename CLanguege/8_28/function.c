#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void exchange(int *x,int *y)
{
	int z = *x;
	*x = *y;
	*y = z;

}
int main()
{
	int num1 = 0;
	int num2 = 0;
	scanf("%d %d",&num1,&num2);
	exchange(&num1, &num2);
	printf("num1 == %d,num2 == %d",num1,num2);
	return 0;
}