#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	/*char ch ;
	while (1)
	{
		scanf("%c", &ch);
		if (ch < 97)
		{
			printf("%c\n",(int)(ch+32));
		}
		else
		{
			printf("%c\n",(int)(ch-32));

		}
		getchar();
	}*/
	int a = 100;
	int* pa = &a;
	int** ppa = &pa;
	int*** pppa = &ppa;
	printf("%d",***pppa);


	return 0;
}