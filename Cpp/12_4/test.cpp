#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

//汉诺塔问题
//void print(char start, char end)
//{
//	printf("%c --> %c\n", start, end);
//}
//void move(int n, char start, char temp, char end)
//{
//	if (n == 1)
//	{
//		print(start, end);
//	}
//	else
//	{
//		move(n - 1, start, end, temp);
//		print(start, end);
//		move(n - 1, temp, start, end);
//	}
//}
//int main()
//{
//	move(5, 'A', 'B', 'C');
//	return 0;
//}

//百钱百鸡问题
//int main()
//{
//	int money = 100;
//	int Rooster = 0;
//	int Hen = 0;
//	int Chick = 0;
//	for (Rooster = 0; Rooster < 100/5; Rooster++)
//	{
//		money = 100 - Rooster * 5;
//		for (Hen = 0; Hen < money / 3; Hen++)
//		{
//			Chick = (money - Hen * 3) * 3;
//			if (Chick + Hen + Rooster == 100)
//				printf("Rooster: %d Hen: %d Chick:%d\n", Rooster, Hen, Chick);
//		}
//	}
//	return 0;
//}

//渔夫打鱼晒网问题
//int get_days(int year, int month, int day)
//{
//	int M[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//	int count = 0;
//	for (int i = 2011; i <= year; i++)
//	{
//		for (int j = 0; j < 12; j++)
//		{
//			for (int k = 1; k <= M[j] + (is_leap_year(i) && (j == 1)); k++)
//			{
//				
//				if (year == i && month == j + 1 && day == k)
//					return count;
//				count++;
//			}
//		}
//	}
//	return count;
//}
//int is_leap_year(int year)
//{
//	if (((year % 4 == 0) && (year % 100) != 0) || (year % 400 == 0) )
//		return 1;
//	else
//		return 0;
//}
//int main()
//{
//	int year = 0;
//	int month = 0;
//	int day = 0;
//	int count = 0;
//	scanf("%d%d%d", &year, &month, &day);
//	count = get_days(year, month, day);
//	printf("经过了%d天（不包括当天）\n", count);
//
//	if ((count % 5) < 3)
//		printf("%d天打鱼\n", count % 5 + 1);
//	else
//		printf("%d天晒网\n", count % 5 + 1);
//
//	return 0;
//}

//日期差值计算
//int is_leap_year(int year)
//{
//	if (((year % 4 == 0) && (year % 100) != 0) || (year % 400 == 0) )
//		return 1;
//	else
//		return 0;
//}
//int calculate_days(int syear, int smonth, int sday, int eyear, int emonth, int eday)
//{
//	int M[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//	int count = 0;
//	for (int i = syear; i <= eyear; i++)
//	{
//		for (int j = smonth-1; j < 12; j++)
//		{
//			for (int k = sday; k <= M[j] + (is_leap_year(i) && (j == 1)); k++)
//			{
//
//				if (eyear == i && emonth == j + 1 && eday == k)
//					return count;
//				count++;
//			}
//		}
//	}
//	return count;
//}
//int main()
//{
//	while (1)
//	{
//		int syear = 0;
//		int smonth = 0;
//		int sday = 0;
//		int eyear = 0;
//		int emonth = 0;
//		int eday = 0;
//		int count = 0;
//		scanf("%d%d%d%d%d%d", &syear, &smonth, &sday, &eyear, &emonth, &eday);
//		count = calculate_days(syear, smonth, sday, eyear, emonth, eday);
//		printf("经过了%d天（不包括当天）\n", count);
//	}
//	return 0;
//}

//猴子吃桃子问题
//int main()
//{
//	int peach = 1;
//	for (int i = 9; i >= 1; i--)
//	{
//		peach += 1;
//		peach *= 2;
//	}
//	printf("%d", peach);
//	return 0;
//}

//字母表菱形
//#include <math.h>
//char Alpha[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//void alpha_print(int n)
//{
//	//char tab[51][51] = { 0 };
//	for (int i = -(n - 1); i <= (n - 1); i++)
//	{
//		for (int j = 1; j < (2 * n); j++)
//		{
//			int k = n - abs(i);
//			if (j <= abs(n - k))
//			{
//				printf(" ");
//			}
//			else
//			{
//				printf("%c", Alpha[k - abs(n-j)]);
//			}
//			
//		}
//		printf("\n");
//	}
//	/*for (int i = -(n - 1); i <= (n - 1); i++)
//	{
//		for (int j = 1; j < (2 * n); j++)
//		{
//			int k = n - abs(i);
//			if (j <= n - k)
//			{
//				printf(" ");
//			}
//			else if(j >= k - n)
//			{
//				printf("%c", Alpha[k - abs(n - j)]);
//			}
//
//		}
//		printf("\n");
//	}*/
//}
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	
//	alpha_print(n);
//}
#include <iostream>
using namespace std;

class Person
{
	friend int operator+ (const Person& p1, const Person& p2);
	friend int operator++ (Person& p1);
	friend ostream& operator<< (ostream& cout, Person& p1);
private:
	int age;
public:
	

	Person(int n)
	{
		this->age = n;
		printf("There is a person whose age is %d");
	}
	~Person()
	{
		cout << "Delete" << endl;
	}
	int get_age()
	{
		return age;
	}
	int operator++ (int)
	{
		this->age++;
		return this->age-1;
	}
};

int operator+ (const Person& p1, const Person& p2)
{

	return p1.age + p2.age;
}
int operator++ (Person& p1)
{
	p1.age++;
	return p1.age;
}
ostream& operator<< (ostream& cout, Person& p1)
{
	cout << p1.age << endl;
	return cout;
}

int main()
{
	Person p1(10);
	Person p2(18);
	cout << p1++ << endl;
	cout << ++p1 << endl;
	cout << p1 << endl;

}