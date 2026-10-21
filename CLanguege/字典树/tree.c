#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int tree[1001][26] = { 0 };
int Node[1001] = { 0 };
int id = 0;
void add_word(char str[])
{
	int len = strlen(str);
	int p = 0;
	for (int i = 0; i < len; i++)
	{
		int x = str[i] - 'a';
		if (tree[p][x] == 0)
		{
			tree[p][x] = ++id;
		}
		p = tree[p][x];
	}
	Node[p]++;
}
int search_word(char str[])
{
	int len = strlen(str);
	int p = 0;
	for (int i = 0; i < len; i++)
	{
		int x = str[i] - 'a';
		if (tree[p][x] == 0)
		{
			return 0;
		}
		p = tree[p][x];
	}
	return Node[p];
}
int main()
{
	printf("想要输入单词的个数：");
	int n;
	scanf("%d", &n);
	char arr[10] = { 0 };
	printf("输入单词\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%s", &arr);
		add_word(arr);
	}
	printf("查找单词\n");
	while (1)
	{
		scanf("%s", &arr);
		if (arr[0] != '0' && arr[0] != '\0')
		{
			printf("出现%d次\n", search_word(arr));
		}
		else
		{
			break;
		}
	}
	



	return 0;
}