#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MINE 10
#define LENGTH 9
#define WIDTH 9
#define LENGTHS (LENGTH+2)
#define WIDTHS (WIDTH+2)

int is_win(char tab[LENGTH][WIDTH])
{
	int num = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (tab[i][j] == '*' || tab[i][j] == 'f')
				num++;
		}
	}
	if (num <= MINE)
		return 1;
	else
		return 0;

}

void B_print(char tab[LENGTH][WIDTH])
{
	printf("x |");
	for (int j = 1; j <= WIDTH; j++)
	{
		printf("%d.", j);
	}
	
	printf("\n--|-------------------\n");
	for (int i = 0; i < LENGTH; i++)
	{
		printf("%d.|", i + 1);
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%c ", tab[i][j]);
			if (j == WIDTH - 1)
			{
				printf("\n");
			}
		}
	}
	printf("\n");

}

void M_print(char tab[LENGTHS][WIDTHS])
{
	printf("x |");
	for (int j = 1; j <= WIDTH; j++)
	{
		printf("%d.", j);
	}

	printf("\n--|-------------------\n");
	for (int i = 1; i < LENGTH+1; i++)
	{
		printf("%d.|", i);
		for (int j = 1; j < WIDTH+1; j++)
		{
			printf("%c ", tab[i][j]);
			if (j == WIDTH)
			{
				printf("\n");
			}
		}
	}
	printf("\n");

}

void check(char tab1[LENGTH][WIDTH], char tab2[LENGTHS][WIDTHS], int x, int y)
{
	//将0周围格子打印，遇到0重复该流程
	for (int xi = x-1; xi <= x+1; xi++)
	{
		for (int yi = y-1; yi <= y+1; yi++)
		{
			if ((x != xi || y != yi) && xi >= 1 && xi <= LENGTH && yi >= 1 && yi <= WIDTH)
			{
				if(tab1[xi-1][yi-1] == '*' || tab1[xi - 1][yi - 1] == 'f')
				{
					tab1[xi-1][yi-1] = tab2[xi][yi];
					if (tab2[xi][yi] == '0' )
					{
						check(tab1, tab2, xi, yi);
					}
				}
			}
		}

	}
}
void num_of_landmine(char tab[LENGTHS][WIDTHS], int x, int y)
{
	//周围坐标
	for (int xi = x - 1; xi <= x + 1; xi++)
	{
		for (int yi = y - 1; yi <= y + 1; yi++)
		{
			if (x != xi || y != yi)
			{
				if (tab[xi][yi] != '#')
				{
					tab[xi][yi]++;
				}
			}
		}

	}
}
void game(char board[LENGTH][WIDTH])
{
	srand(time(NULL));
	int count = 0;
	int judge = 0;
	char landmine[LENGTHS][WIDTHS] = { 0 };
	//储存地雷坐标
	int pos[2][MINE] = { 0 };
	int px = 0;
	int py = 0;
	for (int i = 0; i < LENGTHS; i++)
	{
		for (int j = 0; j < WIDTHS; j++)
		{
			landmine[i][j] = '0';
		}
	}
	int random_x = 0;
	int random_y = 0;
	for (int i = 0; i < MINE; i++)
	{
		do
		{
			random_x = (rand() % LENGTH)+1;
			random_y = (rand() % WIDTH)+1;
		}
		while (landmine[random_x][random_y] == '#');

		landmine[random_x][random_y] = '#';
		pos[0][count] = random_x;
		pos[1][count] = random_y;
		count++;
	}
	//num_of_landmine
	for (int i = 0; i < MINE; i++)
	{
		num_of_landmine(landmine, pos[0][i], pos[1][i]);
	}
	//player
	M_print(landmine);/*for test*/
	printf("答案测试用\n");
	printf("---------------------\n");
	printf("------分割线---------\n");
	printf("---------------------\n");
	printf("------分割线---------\n");
	printf("---------------------\n");
	printf("------分割线---------\n");
	B_print(board);
	while (1)
	{
		printf("Please input the position.(x y)\n");
		scanf("%d %d", &px, &py);
		if (px < 1 || px > 9 || py < 1 || py > 9)
		{
			printf("Position is wrong.Do you want to mark a area or retry?(1/0)\n");
			scanf("%d", &judge);
			if (judge)
			{
				printf("Please input the position which you want to mark.(x y)\n");
				scanf("%d %d", &px, &py);
				printf("You mark a possible point.\n");
				board[px % 10 % (LENGTH + 1) - 1][py % 10 % (WIDTH + 1) - 1] = 'f';
				B_print(board);
			}
			continue;
		}
		board[px-1][py-1] = landmine[px][py];


		if (landmine[px][py] == '#')
		{
			printf("Boom!You lose.\n");
			break;
		}
		//autoprint
		else if (landmine[px][py] == '0')
		{
			check(board, landmine, px, py);
			B_print(board);
			continue;
		}
		B_print(board);
		//Judge the result
		if (is_win(board))
		{
			printf("You Win!\n");
			break;
		}
	}

}

int main()
{

	char board[LENGTH][WIDTH] = { 0 };
	int ans = 1;
	while (ans)
	{
		//Initialize the board

		printf("Do you want to play a game?(1/0)\n");
		scanf("%d", &ans);
		if (ans)
		{
			for (int i = 0; i < LENGTH; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					board[i][j] = '*';
				}
			}
			game(board);
		}

	}
	printf("Game Over.\n");
	Sleep(5000);


	return 0;
}