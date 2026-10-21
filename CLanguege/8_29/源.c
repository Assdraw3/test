#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int prime_number_check(int x)
{
	int answer = 1;
	for (int i = 2; i <=sqrt(x); i++)
	{
		answer = x % i != 0;
		if (answer == 0)
		{
			break;
		}
	}

	return answer;
}

int main()
{
	for (int i = 101; i <= 200; i+=2)
	{
		if (prime_number_check(i))
		{
			printf("%d\n", i);
		}

	}



	return 0;
}