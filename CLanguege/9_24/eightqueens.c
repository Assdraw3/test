#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int a = 0;
void B_print(char tab[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf(" %c", tab[i][j]);
			if (j == 7)
			{
				printf("\n");
			}
		}
		if (i == 7)
		{
			printf(" - - - - - - - -%d\n",++a);
		}
	}


}
int check(int pos[2][8],int num)
{ 
	int ans = 1;
		for (int j = num-1; j != -1; j--)
		{
			ans = ans && (pos[1][num] != pos[1][j]);
			if (!ans)
			{
				break;
			}
			ans = ans && (((pos[1][num] - pos[1][j]) != (pos[0][num] - pos[0][j]))) && (((pos[1][num] - pos[1][j]) != (pos[0][j] - pos[0][num])));
		}


	return ans;
}
void loop(char tab[8][8],int pos[2][8] ,int num)
{
	//printf("%d %d\n", ++a,num);
	for (int i = 0; i < 8; i++)
	{
		pos[1][num] = i;
		tab[num][i] = 'Q';
		if (!(check(pos,num)))
		{
			pos[1][num] = 0;
			tab[num][i] = '*';
			continue;
		}
		if (num >= 7)
		{
			B_print(tab);
		}
		else
		{
			loop(tab, pos, num + 1);
		}
		tab[num][i] = '*';
		pos[1][num] = 0;
	}
	

}

int main()
{
	char board[8][8] = {0};
	int pos[2][8] = { { 0,1,2,3,4,5,6,7} ,{0,0,0,0,0,0,0,0} };
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = '*';
		}
	}
	loop(board,pos,0);
	return 0;
}