#pragma once
#include <iostream>
using namespace std;
typedef int ElemType;
#define MAXSIZE 100
class Node
{
public:
	ElemType data;
	Node* next;
	
	Node(ElemType x[] = NULL, int L = 0)//按照题目要求实现初始化
	{
		
		this->data = 0;
		this->next = NULL;
		Node* p = this;
		for (int i = 0; i < L; i++)
		{
			Node* temp = (Node*)malloc(sizeof(Node));
			p->next = temp;
			p = p->next;
			p->data = x[i];

		}
		p->next = NULL;
		
	}//对链表进行初始化

	~Node()
	{
		Node* p = this->next;
		Node* q;
		while (p != NULL)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}//通过接力传递挨个释放内存

	void print()//按照顺序打印链表
	{
		Node* p = this->next;
		while (p != NULL)
		{
			cout << p->data << endl;
			p = p->next;
			
		}
	}

	void appendElem(ElemType e)//尾插法添加元素
	{
		
		Node* temp = (Node*)malloc(sizeof(Node));
		Node* p = this->next;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
		temp->data = e;
		temp->next = NULL;
	}

	void insertHead(ElemType e)//头插法添加元素
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = e;
		p->next = this->next;
		this->next = p;
	}

	int searchNode(ElemType e)//检索元素位置并输出，0表示未找到
	{
		Node* p = this;
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

	void sortNode()//转化为顺序表再冒泡排序实现排序
	{
		ElemType x[MAXSIZE] = { 0 };
		int count = 0;
		Node* p = this->next;
		while (p != NULL)
		{
			x[count++] = p->data;
			p = p->next;
		}
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count - i -1; j++)
			{
				if (x[j] > x[j + 1])
			    {
					int temp = x[j];
			        x[j] =x[j + 1];
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
	void insertNode(int pos, ElemType e)//向指定位置插入节点
	{
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->data = e;
		Node* p = this->next;
		int count = 1;
		while (p != NULL)
		{
			count++;
			if (count == pos)
			{
				temp->next = p->next;
				p->next = temp;
				return;
			}
			p = p->next;
		}
	}


	ElemType delNode(int pos)//删除指定位置的元素并释放内存
	{
		Node* p = this->next;
		int count = 0;
		while (p != NULL)
		{
			count++;
			if (count == pos-1)
			{
				
				Node* q = p->next;
				ElemType temp = q->data;
				p->next = q->next;
				
				free(q);
				return temp;
			}
			p = p->next;
		}
	}
//	void reverseNode()//先转化为顺序表再逆序元素最后按序覆盖原链表实现
//	{
//		ElemType x[MAXSIZE] = { 0 };
//		int count = 0;
//		Node* p = this->next;
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
	void reverseNode()//利用双指针定位逆序
	{
		int count = 0;
		Node* p = this->next;
		Node* start = this->next;
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
	Node* p = this->next;
	Node* fast = this->next;
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
				Node* q = fast;
				ElemType temp = q->data;
				p->next = q->next;

				free(q);
			}
		} while (flag);
		p = p->next;
	}

	
}
};

Node* initList(ElemType x[] = NULL, int L = 0)
{
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	Node* p = head;
	for (int i = 0; i < L; i++)
	{
		Node* temp = (Node*)malloc(sizeof(Node));
		p->next = temp;
		p = p->next;
		p->data = x[i];

	}
	p->next = NULL;
	return head;
}