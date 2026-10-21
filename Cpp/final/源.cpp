#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
//int main()
//{
//	double a, b, c;
//	double x;
//	cin >> a >> b >> c;
//	if (b * b < 4 * a * c)
//	{
//		cout << "Error\n";
//	}
//	else
//	{
//		x = sqrt(b * b - 4 * a * c);
//		cout << (x - b) / (2 * a) << " " << (-x - b) / (2 * a) << endl;
//	}
//
//
//	return 0;
//}

//int main()
//{
//	double left = 0;
//	double right = 1.57;
//	double accur = 1e-6;
//	double mid = (right - left) / 2 + left;
//	while (abs(mid - cos(mid)) > accur)
//	{
//		if (mid > cos(mid))
//		{
//			right = mid;
//			mid = (right - left) / 2 + left;
//		}
//		else
//		{
//			left = mid;
//			mid = (right - left) / 2 + left;
//		}
//	}
//	cout << mid;
//
//	return 0;
//}

//int GetMaxInColumn(int arr[4])
//{
//	int max = arr[0];
//	for (int i = 1; i < 4; i++)
//	{
//		if (max < arr[i])
//		{
//			max = arr[i];
//		}
//	}
//	return max;
//}
//int main()
//{
//	int arr1[3][4] = {
//		{1, 2, 3, 4},
//		{5, 6, 7, 8},
//		{9, 10, 11, 12}
//	};
//	int ans[3];
//	for (int i = 0; i < 3; i++)
//	{
//		ans[i] = GetMaxInColumn(arr1[i]);
//	}
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			cout << arr1[i][j] << " ";
//		}
//		cout << endl;
//	}
//	for (int i = 0; i < 3; i++)
//	{
//		cout << ans[i] << " ";
//	}
//}

//int MyStrlen(char* str)
//{
//	int count = 0;
//	while (*(str + count))
//	{
//		count++;
//	}
//	return count;
//}
////所有计算长度部分都可以用strlen或MyStrlen代替
//void MyStrcpy(char dest[], char src[])
//{
//	int len = 0;
//	while (*(dest + len) && *(src + len))
//	{
//		len++;
//	}
//	
//	
//	for (int i = 0; i < len; i++)
//	{
//		*(dest + i) = *(src + i);
//	}
//	*(dest + len) = '\0';
//}
//void MyStrcat(char dest[],const char* src)
//{
//	int len1 = 0;
//	while (*(dest + len1))
//	{
//		len1++;
//	}
//	int len2 = 0;
//	while (*(src + len2))
//	{
//		len2++;
//	}
//
//	for (int i = 0; i <= len2; i++)
//	{
//		*(dest + i + len1) = *(src + i);
//	}
//}
//
//int main()
//{
//	char str1[20] = "Hello ";
//	cout << MyStrlen(str1) << endl;
//	char str2[] = "World";
//	MyStrcpy(str1, str2);
//	cout << str1 << endl;
//	MyStrcat(str1, str2);
//	cout << str1 << endl;
//	return 0;
//}

//class STR
//{
//private:
//	char* s;
//	int n;
//public:
//	STR(int num)
//	{
//		n = num;
//		int count = 1;
//		while (num /= 10)
//		{
//			count++;
//		}
//		s = new char[count + 1];
//	}
//	void fun()
//	{
//		int i = 0;
//		int num = n;
//		do
//		{
//			*(s+i) = (num % 10 + '0');
//			num /= 10;
//			i++;
//		} while (num);
//		*(s+i) = '\0';
//	}
//	void print()
//	{
//		cout << s << endl;
//	}
//	~STR()
//	{
//		int count = 1;
//		while (n /= 10)
//		{
//			count++;
//		}
//		delete[count + 1] s;
//		cout << "Clean\n";
//	}
//};
//void test()
//{
//	STR arr1(212100);
//	arr1.fun();
//	arr1.print();
//}
//int main()
//{
//	test();
//}


    //char* trim(char* str);

    //int main()
    //{
    //    char s[1024];     // 定义存储字符串的一维字符数组
    //    // 输入一行字符，可以包含空格
    //    // 输入的字符串存入s中，最多读取个字符，后面自动加上'\0'
    //    cin.getline(s, 1024);
    //    cout << trim(s) << "TEST" << endl;     // 输出去掉首尾空格后的字符串
    //    return 0;
    //}
    //char* trim(char* str)
    //{
    //    int left = 0;
    //    int right = strlen(str) - 1;
    //    for (int i = 0; 1; i++)
    //    {
    //        if (*(str + i) == ' ')
    //        {
    //            left++;
    //        }
    //        else
    //        {
    //            break;
    //        }
    //    }
    //    for (int j = strlen(str)-1; 1; j--)
    //    {
    //        if (*(str + j) == ' ')
    //        {
    //            right--;
    //        }
    //        else
    //        {
    //            break;
    //        }
    //    }
    //    for (int k = 0; k <= right - left; k++)
    //    {
    //        *(str + k) = *(str + left + k);
    //    }
    //    *(str + right - left + 1) = 0;
    //    return str;
    //}


//void pswap(int* p, int* q);
//
//int main()
//{
//    int a, b;
//    cin >> a >> b;     // 输入两个整数
//    pswap(&a, &b);     // 调用pswap函数，交换a、b的值
//    cout << a << " " << b << endl;     // 输出a、b的值
//    return 0;
//}
//
////函数pswap：交换指针p和q指向的单元中的整数值
////参数：p,q-int类型指针，指向要交换的整数
//void pswap(int* p, int* q)
//{
//    int temp = *p;
//    *p = *q;
//    *q = temp;
//}

//void extractNum(char* str);
//
//int main()
//{
//    char s[1024];
//    cin.getline(s, 1024);     // 输入一行字符
//    extractNum(s);     // 调用extractNum函数，选出数字
//    cout << s << endl;     // 输出选出的数字
//    return 0;
//}
//
//// 函数extractNum：选出str指向的字符串中的数字，并写回str
//// 参数：str-指向字符串
//void extractNum(char* str)
//{
//    int post_index = 0;
//    for (int i = 0; *(str + i); i++)
//    {
//        if (*(str + i) >= '0' && *(str + i) <= '9')
//        {
//            *(str + post_index) = *(str + i);
//            post_index++;
//        }
//        else if (*(str + i) == '-' && post_index == 0)
//        {
//            *str = '-';
//            post_index++;
//        }
//    }
//    *(str + post_index) = '\0';
//
//
//
//
//}

//void toUp(char* str);
//
//int main()
//{
//    char s[1024];
//    cin.getline(s, 1024);     // 输入一行字符
//    toUp(s);     // 调用toUp函数，转换成大写字母
//    cout << s << endl;     // 输出变更后的新字符串
//    return 0;
//}
//
//// 函数toUp：将str指向的字符串中的小写字母变成对应的大写字母
//// 参数：str-指向字符串
//void toUp(char* str)
//{
//    for (int i = 0; *(str + i); i++)
//    {
//        if (*(str + i) >= 'a' && *(str + i) <= 'z')
//        {
//            *(str + i) -= 32;
//        }
//    }
//}

//int frequency(char* substr, char* str);
//
//int main()
//{
//    char sub[128], str[1024];
//    cin.getline(sub, 128);     // 输入子串
//    cin.getline(str, 1024);     // 输入长串
//    int n = frequency(sub, str);     // 调用frequency函数，计算子串在长串中出现的次数
//    cout << n << endl;     // 输出次数
//    return 0;
//}
//
//// 函数frequency：计算子串在长串中出现的次数
//// 参数：substr-指向子串，str-指向长串
//// 返回值：出现的次数
//int frequency(char* substr, char* str)
//{
//    int count = 0;
//    
//    for (int i = 0; i <= strlen(str) - strlen(substr); 1)
//    {
//        int flag = 1;
//        for (int j = 0; *(substr + j); j++)
//        {
//            if (*(str + i + j) != *(substr + j))
//            {
//                flag = 0;
//                break;
//            }
//        }
//
//        if (flag)
//        {
//            count++;
//            i += strlen(substr);
//        }
//        else
//        {
//            i++;
//        }
//    }
//
//    return count;
//}


int king(int a[], int n);
int main()
{
    int n, a[1000], i;     // 定义变量及数组，n-猴子数量，a-猴子数组
    cin >> n;     // 输入猴子数量，n>0

    // 初始化猴子数组,n 个猴子分别占据 n 个位置
    a[0] = 0; // 0号位置没有猴子
    for (i = 1;i <= n; i++)
        a[i] = i;

    // 选大王啦
    int x = king(a, n);
    cout << x << "号猴子是大王。" << endl;
    return 0;
}
int king(int a[], int n) {
    int time = 0;
    int bs = n;
    int gou = 1;
    while (bs > 1) {
        int num = 0;
        while (num < 3) {
            cout << time++ << endl;
            if (a[gou] != 0) {
                num++;
            }
            if (num ==3) {
                a[gou] = 0;
                bs--;
            }
            gou = (gou % n) + 1;
      }
        
    }
    int i;
    for (i = 1;i <= n;i++) {
        cout << time++ << endl;
        if (a[i] != 0) {
            return i;
        }
    }
}