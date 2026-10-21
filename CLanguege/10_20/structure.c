#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
struct Person {
	char name[20];
	int age;
	char gender[10];
};
int main()
{

	struct Person p1 = { "Alpha",20,"Male"};
	struct Person p2 = { "Beta",25,"Female" };
	struct Person p3 = { "Theta",30,"Secret" };
	//memcpy(p1.name,"Apple",strlen("Apple"));
	strcpy(p1.name, "Apple");
	printf("%s\n", p1.name);
	int num1 = 0;
	int num2 = 0;
	short count = 0;
	scanf("%d %d", &num1,&num2);
	int num = num1 ^ num2;
	for (int i = 0; i < sizeof(num) * 8; i++)
	{
		count += (num >> i) & 1;
	}
	printf("%d\n",count);


	return 0;
}