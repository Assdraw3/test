#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int game()
{
	int num = 0;
	srand((unsigned int)time(NULL));
	int random = rand() % 100 + 1;
	printf("Please guess a number.--range(1,100)\n");
	scanf("%d", &num);
	while (num != random)
	{
		
		if (num < random)
		{
			printf("It is bigger than yours,\n");
		}
		else
		{
			printf("It is smaller than yours,\n");
		}

		scanf("%d", &num);
	}
	printf("You Win!");
	return 0;
}


int main() 
{
	int justice = 0;
	
	printf("***************************\n");
	printf("***************************\n");
	printf("Do you want to play a game?\n");
	printf("***************************\n");
	printf("***************************\n");

	scanf("%d", &justice);
	if (justice == 1)
	{
		game();
	}
	else
	{
		printf("game over\n");
	}

	return 0;
}