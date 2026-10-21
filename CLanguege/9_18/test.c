#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void game()
{
	char Tab[ROW][COL] = { 0 };
	board(Tab, ROW, COL);
	B_print(Tab, ROW, COL);
	while (1)
	{
		int x = 0;
		int y = 0;
		int Ans = 0;
		printf("Please input the position.\n");
		scanf("%d %d", &x, &y);
		person(Tab,x-1,y-1);
		B_print(Tab, ROW, COL);
		Ans = Just(Tab);
		if (Ans)
		{
			printf("You win.\n");
			break;
		}
		printf("Computer moves.\n");
		computer(Tab);
		B_print(Tab, ROW, COL);
		Ans = Just(Tab);
		if (Ans)
		{
			printf("You lose.\n");
			break;
		}
		/*if (just())
		{

			break;
		}*/
	}
}


int main()
{
	printf("Do you want to play a game?\n");
	int answer = 0;
	scanf("%d", &answer);
	if (answer)
	{
		game();
	}
	else
	{
		printf("Over.");
	}

	return 0;
}