#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;

typedef struct node
{
	ElemType data;
	struct node* next;
}Node;

Node* initList()
{
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}

int insertHead(Node* L, ElemType e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
}

void listNode(Node* L)
{
	Node* p = L->next;
	while (p != NULL)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}
int searchNode(Node* L, ElemType e)
{
	Node* p = L;
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

void appendNode(Node* L, ElemType e)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* p = L;
	while (p->next != NULL)
	{
		
		p = p->next;
	}
	p->next = temp;
	temp->data = e;
	temp->next = NULL;
}

int main()
{
	Node* list = initList();
	insertHead(list, 10);
	insertHead(list, 20);
	appendNode(list, 50);
	
	printf("%d\n",searchNode(list, 20));
	listNode(list);
	free(list);


	return 0;
}