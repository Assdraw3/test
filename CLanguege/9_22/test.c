#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int des[1000] = {0};
void pos(char arr[],int size)
{
	des[0] = 1;
	int x = 1;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == ' ')
			des[x++] = i+1;

	}



}
int main()
{
	int n = 0;
	char ch[10000] = "";
	int* arr = (int*)malloc(n * sizeof(int));
	
	scanf("%d",&n);
	getchar();
	gets(ch);
	pos(ch,n);
	for (int i = 0; i < n; i++)
	{
		char lin[5] = { 0 };
		memcpy(lin,ch+des[i], des[i+1]-des[i]);
		arr[i] = atoi(lin);
		printf("%d", arr[i]);
		
	}
	
	//free(arr);
	
	return 0;
}