#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Node.h"


int main()
{
	//int x[] = { 1, 1, 3, 3, 2, 2, 4, 4, 5};
	int x[] = { 1, 1, 1, 1, 15, 16, 16, 27};
	//Node *list = initList(x, 5);
	
	/*list->print();

	list->insertHead(47);
	list->appendElem(28);
	list->print();*/
	//42
	Node list(x, sizeof(x)/sizeof(x[0]));
	cout << "初始化后链表为：\n";
	list.print();

	//list.insertHead(47);
	//cout << "头结点后插入元素47后链表为：\n";
	//list.print();

	//list.appendElem(28);
	//cout << "尾结点后插入元素28后链表为：\n";
	//list.print();

	//list.sortNode();
	//cout << "冒泡排序后链表为：\n";
	//list.print();
	list.delSame();
	cout << "删除重复后链表为：\n";
	list.print();
	list.reverseNode();
	cout << "逆转后链表为：\n";
	list.print();

	/*list.insertNode(2, 10);
	cout << "在2号位置插入元素10后链表为：\n";
	list.print();
	cout <<"删除了3号位置元素" << list.delNode(3)<< "后链表为：" << endl;
	list.print();
	*/
	return 0;
}