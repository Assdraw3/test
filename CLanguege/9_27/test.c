#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
//#define MINE 10
//#define LENGTH 9
//#define WIDTH 9
//void B_print(char tab[LENGTH][WIDTH])
//{
//	printf("   1.2.3.4.5.6.7.8.9.\n");
//	printf("---------------------\n");
//	for (int i = 0; i < LENGTH; i++)
//	{
//		printf("%d.|", i+1);
//		for (int j = 0; j < WIDTH; j++)
//		{
//			printf("%c ", tab[i][j]);
//			if (j == WIDTH-1)
//			{
//				printf("\n");
//			}
//		}
//	}
//	printf("\n");
//
//}
//void check(char tab1[LENGTH][WIDTH],char tab2[LENGTH][WIDTH], int x, int y)
//{
//	int pos[2][8];
//	//将0周围格子打印，遇到0重复该流程
//	pos[0][0] = x - 1;
//	pos[0][1] = x - 1;
//	pos[0][2] = x - 1;
//	pos[0][3] = x;
//	pos[0][4] = x;
//	pos[0][5] = x + 1;
//	pos[0][6] = x + 1;
//	pos[0][7] = x + 1;
//	pos[1][0] = y - 1;
//	pos[1][1] = y;
//	pos[1][2] = y + 1;
//	pos[1][3] = y - 1;
//	pos[1][4] = y + 1;
//	pos[1][5] = y - 1;
//	pos[1][6] = y;
//	pos[1][7] = y + 1;
//	for (int i = 0; i < 8; i++)
//	{
//		if ( pos[0][i] >= 0 && pos[0][i] <= 8 && pos[1][i] >= 0 && pos[1][i] <= 8 && tab1[pos[0][i]][pos[1][i]] != '0')
//		{
//			tab1[pos[0][i]][pos[1][i]] = tab2[pos[0][i]][pos[1][i]];
//			if(tab2[pos[0][i]][pos[1][i]] == '0')
//				check(tab1, tab2, pos[0][i], pos[1][i]);
//		}
//	}
//}
//void num_of_landmine(char tab[LENGTH][WIDTH], int x, int y)
//{
//	int pos[2][8];
//	//周围坐标
//	pos[0][0] = x-1;
//	pos[0][1] = x-1;
//	pos[0][2] = x-1;
//	pos[0][3] = x;
//	pos[0][4] = x;
//	pos[0][5] = x+1;
//	pos[0][6] = x+1;
//	pos[0][7] = x+1;
//	pos[1][0] = y-1;
//	pos[1][1] = y;
//	pos[1][2] = y+1;
//	pos[1][3] = y-1;
//	pos[1][4] = y+1;
//	pos[1][5] = y-1;
//	pos[1][6] = y;
//	pos[1][7] = y+1;
//	for (int i = 0; i < 8; i++)
//	{
//		if (tab[pos[0][i]][pos[1][i]] != '#' && pos[0][i] >= 0 && pos[0][i] <= 8 && pos[1][i] >= 0 && pos[1][i] <= 8)
//		{
//			tab[pos[0][i]][pos[1][i]] = tab[pos[0][i]][pos[1][i]]+1;
//		}
//	}
//}
//void game(char board[LENGTH][WIDTH])
//{
//	int count = 0;
//	int n = 0;
//	int num = 0;
//	char landmine[LENGTH][WIDTH] = { 0 };
//	int pos[2][MINE] = { 0 };
//	int px = 0;
//	int py = 0;
//	for (int i = 0; i < LENGTH; i++)
//	{
//		for (int j = 0; j < WIDTH; j++)
//		{
//			landmine[i][j] = '0';
//		}
//	}
//	int random_x = 0;
//	int random_y = 0;
//	for (int i = 0; i < MINE ; i++)
//	{
//		do
//		{
//			
//			n++;
//			srand(time(NULL)/n);
//			n++;
//			random_x = rand()% LENGTH;
//			srand(time(NULL)/n);
//			random_y = rand()% WIDTH;
//		} while (landmine[random_x][random_y] == '#');
//		landmine[random_x][random_y] = '#';
//		pos[0][count] = random_x;
//		pos[1][count] = random_y;
//		count++;
//	}
//	//num_of_landmine
//	for (int i = 0; i < MINE; i++)
//	{
//		num_of_landmine(landmine, pos[0][i], pos[1][i]);
//	}
//	//player
//	B_print(landmine);/*for test*/
//	printf("答案测试用\n");
//	printf("---------------------\n");
//	printf("------分割线---------\n");
//	printf("---------------------\n");
//	printf("------分割线---------\n");
//	printf("---------------------\n");
//	printf("------分割线---------\n");
//	B_print(board);
//	printf("If you want to mark a position,\nplease input a position which is bigger than ten.\n");
//	while (1)
//	{
//		printf("Please input the position.(x y)\n");
//		scanf("%d %d",&px,&py);
//		px -= 1;
//		py -= 1;
//		if (px < 0 || px > 8 || py < 0 || py > 8)
//		{
//			printf("You mark a possible point.\n");
//			board[px%10%LENGTH][py%10%WIDTH] = 'f';
//			B_print(board);
//			continue;
//		}
//		board[px][py] = landmine[px][py];
//		
//		
//		if (landmine[px][py] == '#')
//		{
//			printf("Boom!You lose.\n");
//			break;
//		}
//		//autoprint
//		else if (landmine[px][py] == '0')
//		{
//			check(board,landmine,px,py);
//			B_print(board);
//			continue;
//		}
//		B_print(board);
//		//Judge the result
//		for (int i = 0; i < LENGTH; i++)
//		{
//			for (int j = 0; j < WIDTH; j++)
//			{
//				if (board[i][j] == '*' || board[i][j] == 'f')
//					num++;
//			}
//		}
//		if (num <= 10)
//		{
//			printf("You Win!\n");
//			break;
//		}
//		else
//		{
//			num = 0;
//		}
//		
//	}
//
//}
//
//int main()
//{
//
//	char board[LENGTH][WIDTH] = { 0 };
//	int ans = 1;
//	while (ans)
//	{
//		//Initialize the board
//	
//		printf("Do you want to play a game?(1/0)\n");
//		scanf("%d", &ans);
//		if (ans)
//		{
//			for (int i = 0; i < LENGTH; i++)
//			{
//				for (int j = 0; j < WIDTH; j++)
//				{
//					board[i][j] = '*';
//				}
//			}
//			game(board);
//		}
//
//	}
//	printf("Game Over.\n");
//	Sleep(5000);
//
//
//	return 0;
//}
int main()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", rand());
	}

	return 0;
}