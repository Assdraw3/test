//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include "test.h"
//
//int main()
//{
//	int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//	SeqList <int>list (tab, sizeof(tab)/sizeof(tab[0]));//建立一个顺序表，初始长度为10
//	int delElem;
//	list.initList(&list);
//	printf("初始化成功，目前长度为%d\n", list.length);
//	cout << "初始化后的表为：";
//	list.listElem();//初始化的顺序表
//
//	for (int i = 11; i <= 20; i++)
//	{
//		list.appendElem(i);
//	}//在尾部依次添加元素
//	cout << "添加元素后的线性表：";
//	list.listElem();//添加后的顺序表
//
//	list.insertElem(2, 47);//在第二个位置插入数值为47的元素
//	cout << "在位置2插入47后的线性表：";
//	list.listElem();
//
//	delElem = list.deleteElem(5);//删除5位置的元素
//	cout << "删除元素" << delElem << "后的线性表是：";
//	list.listElem();
//
//	cout << "元素8的位置是：" <<list.findElem(8) << endl;//查找元素8的位置并输出
//
//
//	list.reverseList();
//	cout << "逆置后的线性表为:";
//	list.listElem();
//
//	list.sordList();
//	cout << "冒泡排序后的线性表:";
//	list.listElem();
//
//	return 0;
//}