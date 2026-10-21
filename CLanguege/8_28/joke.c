#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//int game()
//{
//	int num = 0;
//	srand((unsigned int)time(NULL));
//	int random = rand() % 100 + 1;
//	printf("Please guess a number in 180 seconds.--range(1,100)\n");
//	scanf("%d", &num);
//	while (num != random)
//	{
//
//		if (num < random)
//		{
//			printf("It is bigger than yours,\n");
//		}
//		else
//		{
//			printf("It is smaller than yours,\n");
//		}
//
//		scanf("%d", &num);
//	}
//	printf("You Win!");
//	system("shutdown -a");
//	return 0;
//}
//
//
//int main()
//{
//	printf("您的电脑将在3分钟后关机，请猜对数字以取消\n");
//	Sleep(2000);
//	system("shutdown -s -t 180");
//		game();
//	
//	return 0;
//}