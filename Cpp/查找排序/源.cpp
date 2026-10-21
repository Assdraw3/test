#include <iostream>
using namespace std;

/*-------------------------------------------
  单链表结点
-------------------------------------------*/
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// 在链表尾部插入
void Append(Node*& head, int x) {
    Node* p = new Node(x);
    if (!head) {
        head = p;
        return;
    }
    Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = p;
}

// 打印链表
void Print(Node* head) {
    for (Node* p = head; p; p = p->next)
        cout << p->data << " ";
    cout << endl;
}

/*-------------------------------------------
  直接插入排序（链表）
-------------------------------------------*/
Node* InsertSort(Node* head) {
    if (!head || !head->next) return head;

    Node* sorted = nullptr;      // 新的有序链表

    while (head) {
        Node* p = head;          // 取下一个节点
        head = head->next;

        if (!sorted || p->data < sorted->data) {
            p->next = sorted;
            sorted = p;
        }
        else {
            Node* cur = sorted;
            while (cur->next && cur->next->data < p->data)
                cur = cur->next;
            p->next = cur->next;
            cur->next = p;
        }
    }
    return sorted;
}

/*-------------------------------------------
  简单选择排序（链表）
-------------------------------------------*/
Node* SelectSort(Node* head) {
    if (!head) return head;

    Node* sorted = nullptr;
    Node* tail = nullptr;

    while (head) {
        Node* minPrev = nullptr;
        Node* minNode = head;

        Node* prev = head;
        Node* cur = head->next;
        while (cur) {
            if (cur->data < minNode->data) {
                minNode = cur;
                minPrev = prev;
            }
            prev = cur;
            cur = cur->next;
        }

        // 从原链表断开 minNode
        if (minPrev) minPrev->next = minNode->next;
        else head = head->next;

        minNode->next = nullptr;

        // 加到排序链表
        if (!sorted) {
            sorted = minNode;
            tail = minNode;
        }
        else {
            tail->next = minNode;
            tail = minNode;
        }
    }

    return sorted;
}

int main() {
    cout << "===== 单链表排序 =====\n";
    int n;
    cout << "输入链表长度: ";
    cin >> n;

    Node* head = nullptr;
    cout << "输入链表元素:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        Append(head, x);
    }

    cout << "原链表：";
    Print(head);
    while (1)
    {

        int op;
        cout << "1. 直接插入排序\n2. 简单选择排序\n选择操作: ";
        cin >> op;

        if (op == 1) {
            head = InsertSort(head);
            cout << "插入排序结果：";
        }
        else {
            head = SelectSort(head);
            cout << "选择排序结果：";
        }

        Print(head);
    }
    return 0;
}