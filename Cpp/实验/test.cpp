#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "test.h"
using namespace std;

int main()
{
	Stack list(NULL,0);
	int value;
	while (1)
	{

		cin >> value;
		if (value != -1)
		{
			list.push(value);
			
		}
		else if(list.top-> next != NULL)
		{
			list.pop();
		}
		else
		{
			cout << "已经为空无法执行出栈操作\n";
			continue;
		}
		cout << "\n目前栈中元素有：" << endl;
		cout << "------------------------------------------" << endl;
		list.print();
		cout << "------------------------------------------\n" << endl;
	};



	return 0;
}