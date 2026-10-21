//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#define MAXSIZE 100
//typedef int ElemType;
//
//typedef struct
//{
//	ElemType* data;
//	int length;
//
//}SeqList;
//
//SeqList* initList()
//{
//	SeqList* L = (SeqList*)malloc(sizeof(SeqList));
//	L->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
//	L->length = 0;
//	return L;
//}
//
//int appendElem(SeqList* L, ElemType e)
//{
//	if (L->length >= MAXSIZE)
//	{
//		printf("Full\n");
//		return 0;
//	}
//	L->data[L->length] = e;
//	L->length++;
//	return 1;
//}
//
//void listElem(SeqList* L)
//{
//	for (int i = 0; i < L->length; i++)
//	{
//		printf("%d ", L->data[i]);
//	}
//	printf("\n");
//}
//
//void insertElem(SeqList* L, int pos, ElemType e)
//{
//	if (pos <= L->length && L->length < MAXSIZE - 1)
//	{
//		for (int i = L->length - 1; i >= pos - 1; i--)
//		{
//			L->data[i + 1] = L->data[i];
//		}
//		L->data[pos - 1] = e;
//		L->length++;
//		return 1;
//	}
//	return 0;
//}
//int deleteElem(SeqList* L, int pos, ElemType* e)
//{
//	*e = L->data[pos - 1];
//	if (pos <= L->length)
//	{
//		for (int i = pos - 1; i < L->length - 1; i++)
//		{
//			L->data[i] = L->data[i + 1];
//		}
//
//		L->length--;
//		return 1;
//	}
//	return 0;
//}
//int findElem(SeqList* L, ElemType e)
//{
//
//	for (int i = 0; i < L->length - 1; i++)
//	{
//		if (L->data[i] == e)
//		{
//			return i + 1;
//		}
//	}
//
//
//	return 0;
//}
//int main()
//{
//	SeqList* list;
//	list = initList();
//	printf("初始化成功，目前长度占用%d\n", list->length);
//	printf("目前的内存占用为%zu字节\n", sizeof(list->data));
//	for (int i = 0; i <= 10; i++)
//	{
//		appendElem(list, i);
//	}
//	insertElem(list, 2, -1);
//	ElemType deldata = 0;
//	deleteElem(list, 5, &deldata);
//	printf("%d has been deleted.\n", deldata);
//	listElem(list);
//	printf("%d\n", findElem(list, 8));
//	free(list);
//	return 0;
//}