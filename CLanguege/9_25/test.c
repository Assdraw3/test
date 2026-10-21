#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void str_ex(char tab1[], char tab2[])
{
	char tmp = 0;
	int len = strlen(tab1);
	for (int i = 0; i < len; i++)
	{

		tmp = tab1[i];
		tab1[i] = tab2[i];
		tab2[i] = tmp;

	}

}

int main()
{
	char arr1[12] = "Hello World";
	char arr2[12] = "Hello Sekai";
	str_ex(arr1, arr2);
	printf("%s\n", arr1);
	printf("%s\n", arr2);

	return 0;
}