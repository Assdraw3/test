#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
void person(char tab[ROW][COL],int x,int y)
{
	tab[x][y] = 'x';
}
void computer(char tab[ROW][COL])
{
	int n1 = 0;
	int n2 = 0;
	do
	{
		
		srand(time(NULL));
		n1 = rand() % 3;
		n2 = rand() % 3;
		if (tab[n1][n2] != 'x' && tab[n1][n2] != 'o')
		{
			tab[n1][n2] = 'o';
			break;
		}
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{

				if (tab[i][j] != 'x' && tab[i][j] != 'o')
				{
					tab[i][j] = 'o';
					goto a;
				}

			}

		}
		Sleep(60000);
	
	} while (1);
a: printf("");

	
}
short Just(char tab[ROW][COL])
{
	short r = 0;
	for (int i = 0; i < 3; i++)
	{
		if ((tab[i][1] == tab[i][2] && tab[i][1] == tab[i][0] && tab[i][1] != ' ') || (tab[1][i] == tab[2][i] && tab[1][i] == tab[0][i] && tab[1][i] != ' ') || (tab[0][0]==tab[1][1]&&tab[0][0]==tab[2][2]&&tab[0][0]!=' ')||(tab[2][0] == tab[1][1] && tab[0][2] == tab[1][1] && tab[1][1] != ' '))
		{
			r = 1;
		}
	}

	return r;

}
void B_print(char tab[ROW][COL], int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			printf(" %c ", tab[i][j]);
			//printf("%d\n",(int)tab[i][j]);
			if (j < y - 1)
			{
				printf("|");
			}
			else
			{
				printf("\n");
			}
		}
		if (i < x - 1)
		{
			printf("---|---|---\n");
		}
	}
}
void board(char tab[ROW][COL], int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			tab[i][j] = ' ';


		}

	}
}
