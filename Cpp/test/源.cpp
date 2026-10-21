#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

class son
{
	
public:
	int age;
	char sex;
public:
	int get_age()
	{
		return age;
	}
	~son()
	{
		cout << "over";
	}
};
class Point
{

	son p1;
	
};
son a;

son math()
{
	return a;
}
int main()
{

	son p1;
	math();

	cout << &a << endl;
	cout << &p1 << endl;
	//int& p = p1.get_age();
	int b = 50;
	int c = 60;
	//a = 0;
	for (int i = 0; i < 20; i++)
	//cout << p1 << endl;
	



	return 0;
}