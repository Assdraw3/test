#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	//narcissu
	for (int i = 100; i < 1000; i++)
	{
		int x = i;
		int n1 = x % 10;
		x /= 10;
		int n2 = x % 10;
		x /= 10;
		int n3 = x % 10;
		/*cout << (2^3) << endl;
		cout << n2 << endl;
		cout << n3 << endl;
		cout << i << endl;*/
		if ((pow(n1, 3) + pow(n2, 3) + pow(n3, 3)) == i)
		{
			cout << i << endl;
		}

	}

	return 0;
}