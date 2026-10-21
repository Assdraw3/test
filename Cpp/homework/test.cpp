//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <iostream>
//#include <string.h>
//#include <string>
//#include <stdlib.h>
//using namespace std;
//
//
//void game()
//{
//	int guess = 0;
//	int r = rand() % 100 + 1;
//	cout << "Please guess a number from one to one hundred\n";
//	cin >> guess;
//	while (guess != r)
//	{
//		if (guess > r)
//		{
//			cout << "Too big\n";
//		}
//		else if (guess < r)
//		{
//			cout << "Too small\n";
//		}
//		cin >> guess;
//	}
//	cout << "You Win\n";
//	
//}
//
//enum Sex
//{
//	MALE,
//	FEMALE,
//	NONE
//};
//
//class Person
//{
//private:
//	string name;
//	int age;
//	enum Sex sex;
//public:
//	string get_name()
//	{
//		return name;
//	}
//	int get_age()
//	{
//		return age;
//	}
//	void set_name(string str)
//	{
//		name = str;
//	}
//	void set_age(int str)
//	{
//		age = str;
//	}
//	void set_sex(Sex str)
//	{
//		sex = str;
//	}
//	Sex get_sex()
//	{
//		return sex;
//	}
//};
//int main()
//{
//	//冒泡排序
//	/*int arr[10] = { 0 };
//	int temp = 0;
//	scanf("%d%d%d", &arr[0], &arr[1], &arr[2]);
//	for (int i = 0; i < 3 - 1; i++)
//	{
//		for (int j = 0; j < 3 - 1 - i; j++)
//		{
//			if (arr[j] < arr[j + 1])
//			{
//				temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//		
//	}
//	for (int i = 0; i < 3; i++)
//	{
//		printf("%d ", arr[i]);
//	}*/
//	//New 和 Delete的使用
//	/*int n = 100;
//	int* arr = new int[n];
//	for (int i = 0; i < n; i++)
//	{
//		*(arr + i) = i;
//		printf("%d\n", * (arr + i));
//	}
//	delete[] arr;*/
//	//猜数字
//	/*srand((unsigned)time(NULL));
//	int judge = 0;
//	do
//	{
//		cout << "Do you want to play a game?(1.Yes/0.No)" << endl;
//		cin >> judge;
//		if (judge)
//		{
//			game();
//		}
//		else
//		{
//			break;
//		}
//
//	} while (1);*/
//
//	//变长数组
//	cout << sizeof(int[10]);
//	return 0;
//}
// 
#include <iostream>
#include <string>
using namespace std;
class StInfo
{
    /********* Begin *********/
    //在此处定义StInfo类
private:
    int ID;
    string name;
    string classname;
    string phonenumber;
public:
    int get_ID()
    {
        return ID;
    }
    string get_name()
    {
        return name;
    }
    string get_classname()
    {
        return classname;
    }
    string get_phonenumber()
    {
        return phonenumber;
    }
    void set_ID(int n)
    {
        ID = n;
    }
    void set_name(string n)
    {
        name = n;
    }
    void set_classname(string n)
    {
        classname = n;
    }
    void set_phonenumber(string n)
    {
        phonenumber = n;
    }

    /********* End *********/
};

int main()
{
    int Id;
    string Name;
    string ClassName;
    string PhoneNumber;
    cin >> Id >> Name >> ClassName >> PhoneNumber;
    StInfo std1;
    std1.set_ID(Id);
    std1.set_name(Name);
    std1.set_classname(ClassName);
    std1.set_phonenumber(PhoneNumber);
    cout << "学号：" << std1.get_ID() << endl;
    cout << "姓名：" << std1.get_name() << endl;
    cout << "班级：" << std1.get_classname() << endl;
    cout << "手机号：" << std1.get_phonenumber() << endl;
    return 0;
}