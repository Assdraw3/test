//#pragma once
//#include <iostream>
//using namespace std;
//
//#define MAXSIZE 100
////typedef int ElemType;
//template <typename ElemType>
//class SeqList {
//public:
//    ElemType data[MAXSIZE];
//    int length;
//
//    // 初始化列表
//    SeqList(ElemType x[] = NULL,int L = 0) {
//        length = L;
//        for (int i = 0; i < L; i++)
//        {
//            data[i] = x[i];
//        }
//    }
//
//    ~SeqList() {
//        
//    }//静态对象无需手动释放内存
//
//    void initList(SeqList* L) { L->length = 0; }//原始初始化
//
//    // 向后增加元素
//    bool appendElem(ElemType e) {
//        if (length >= MAXSIZE) {
//            cout << "Full" << endl;
//            return false;
//        }
//        data[length++] = e;
//        return true;
//    }
//
//    // 打印表
//    void listElem() const {
//        for (int i = 0; i < length; i++) {
//            cout << data[i] << " ";
//        }
//        cout << endl;
//    }
//
//    // 在第pos个位置（下标为pos-1）插入元素e
//    bool insertElem(int pos, ElemType e) {
//        if (pos <= length + 1 && length < MAXSIZE) {
//            for (int i = length; i >= pos; i--) {
//                data[i] = data[i - 1];
//            }
//            data[pos - 1] = e;
//            length++;
//            return true;
//        }
//        return false;
//    }
//
//    // 删除pos位置的元素并返回该元素的值 ps：0代表删除失败
//    ElemType deleteElem(int pos) {
//        if (pos <= length && pos >= 1) {
//            ElemType e = data[pos - 1];
//            for (int i = pos - 1; i < length - 1; i++) {
//                data[i] = data[i + 1];
//            }
//            length--;
//            return e;
//        }
//        return 0;
//    }
//
//    //顺序查找元素e的位置
//    int findElem(ElemType e) const {
//        for (int i = 0; i < length; i++) {
//            if (data[i] == e) {
//                return i + 1;
//            }
//        }
//        return 0; // not found
//    }
//    //逆序该表
//    void reverseList()
//    {
//        ElemType temp = 0;
//        for (int i = 0; i < length / 2; i++)
//        {
//            temp = data[i];
//            data[i] = data[length - i - 1];
//            data[length - i - 1] = temp;
//        }
//    }
//    //获取表长
//    int listLength()
//    {
//        return length;
//    }
//    //从小到大排序表
//    void sordList()
//    {
//        ElemType temp = 0;
//        for (int i = 0; i < length; i++)
//        {
//            for (int j = 0; j < length - i -1; j++)
//            {
//                if (data[j] > data[j + 1])
//                {
//                    temp = data[j];
//                    data[j] = data[j + 1];
//                    data[j + 1] = temp;
//                }
//            }
//        }
//    }
//};
