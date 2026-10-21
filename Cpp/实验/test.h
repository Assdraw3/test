#pragma once
#include <iostream>
using namespace std;
typedef int ElemType;
#define MAXSIZE 100
class Stack
{
public:
	ElemType data;
	Stack* next;
	Stack* top = this;
	Stack(ElemType x[] = NULL, int L = 0)//按照题目要求实现初始化
	{

		this->data = 0;
		this->next = NULL;
		Stack* p = this;
		for (int i = 0; i < L; i++)
		{
			Stack* temp = (Stack*)malloc(sizeof(Stack));
			p->next = temp;
			p = p->next;
			p->data = x[i];

		}
		p->next = NULL;

	}//对链表进行初始化

	~Stack()
	{
		Stack* p = this->next;
		Stack* q;
		while (p != NULL)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}//通过接力传递挨个释放内存

	void print()//按照顺序打印链表
	{
		Stack* p = this->next;
		while (p != NULL)
		{
			cout << p->data << endl;
			p = p->next;

		}
	}

	
	void push(ElemType e)//头插法添加元素
	{
		
		Stack* p = (Stack*)malloc(sizeof(Stack));
		p->data = e;
		p->next = this->next;
		this->next = p;
	}

	ElemType pop(int pos = 1)//删除指定位置的元素并释放内存,栈中默认为第一个
	{
		Stack* p = this;
		int count = -1;
		while (p != NULL)
		{
			count++;
			if (count == pos - 1)
			{

				Stack* q = p->next;
				ElemType temp = q->data;
				p->next = q->next;

				free(q);
				return temp;
			}
			p = p->next;
		}
	}
	int searchStack(ElemType e)//检索元素位置并输出，0表示未找到
	{
		Stack* p = this;
		int count = 0;
		while (p->next != NULL)
		{
			p = p->next;
			count++;
			if (p->data == e)
			{
				return count;
			}
			printf("%d\n", count);
		}
		return 0;
	}

	void sortStack()//转化为顺序表再冒泡排序实现排序
	{
		ElemType x[MAXSIZE] = { 0 };
		int count = 0;
		Stack* p = this->next;
		while (p != NULL)
		{
			x[count++] = p->data;
			p = p->next;
		}
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count - i - 1; j++)
			{
				if (x[j] > x[j + 1])
				{
					int temp = x[j];
					x[j] = x[j + 1];
					x[j + 1] = temp;
				}
			}
		}
		p = this->next;
		count = 0;
		while (p != NULL)
		{
			p->data = x[count++];
			p = p->next;
		}

	}



	//	void reverseStack()//先转化为顺序表再逆序元素最后按序覆盖原链表实现
	//	{
	//		ElemType x[MAXSIZE] = { 0 };
	//		int count = 0;
	//		Stack* p = this->next;
	//		while (p != NULL)
	//		{
	//			x[count++] = p->data;
	//			p = p->next;
	//		}
	//    
	//        ElemType temp = 0;
	//        for (int i = 0; i < count / 2; i++)
	//        {
	//            temp = x[i];
	//            x[i] = x[count - i - 1];
	//            x[count - i - 1] = temp;
	//        }
	//    
	//		p = this->next;
	//		count = 0;
	//		while (p != NULL)
	//		{
	//			p->data = x[count++];
	//			p = p->next;
	//		}
	//
	//	}
	//};
	void reverseStack()//利用双指针定位逆序
	{
		int count = 0;
		Stack* p = this->next;
		Stack* start = this->next;
		while (p != NULL)
		{
			count++;
			p = p->next;
		}

		ElemType temp = 0;
		for (int i = 0; i < count / 2; i++)
		{
			p = this;
			int tick = 0;


			do
			{
				p = p->next;
				tick++;
			} while (tick < count - i);


			temp = p->data;
			p->data = start->data;
			start->data = temp;
			start = start->next;
		}

	}

	void delSame()//利用数组存储已有元素来排查重复项
	{
		ElemType check[MAXSIZE];
		Stack* p = this->next;
		Stack* fast = this->next;
		int count = 0;
		while (p != NULL)
		{
			check[count++] = p->data;
			int flag = 0;
			do {
				fast = p->next;
				if (fast == NULL)
				{
					break;
				}
				flag = 0;
				for (int i = 0; i < count; i++)
				{
					if (fast->data == check[i])
					{
						flag = 1;
					}
				}
				if (flag)
				{
					Stack* q = fast;
					ElemType temp = q->data;
					p->next = q->next;

					free(q);
				}
			} while (flag);
			p = p->next;
		}


	}
};

Stack* initList(ElemType x[] = NULL, int L = 0)
{
	Stack* head = (Stack*)malloc(sizeof(Stack));
	head->data = 0;
	head->next = NULL;
	Stack* p = head;
	for (int i = 0; i < L; i++)
	{
		Stack* temp = (Stack*)malloc(sizeof(Stack));
		p->next = temp;
		p = p->next;
		p->data = x[i];

	}
	p->next = NULL;
	return head;
}