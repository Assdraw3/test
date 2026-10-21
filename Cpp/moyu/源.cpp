#include <iostream>
using namespace std;

// 定义循环链表节点结构
struct Node {
    int data;
    Node* next;
};

// 定义循环链队列类
class CircularQueue {
private:
    Node* rear; // 队尾指针

public:
    CircularQueue() : rear(nullptr) {} // 构造函数初始化队尾指针为nullptr

    // 判断队列是否为空
    bool isEmpty() const {
        return rear == nullptr;
    }

    // 入队操作
    void enqueue(int value) {
        Node* newNode = new Node;
        newNode->data = value;

        if (isEmpty()) {
            newNode->next = newNode; // 只有一个节点时，指向自己
            rear = newNode;
        }
        else {
            newNode->next = rear->next; // 新节点指向队头
            rear->next = newNode; // 队尾指向新节点
            rear = newNode; // 更新队尾指针
        }
    }

    // 出队操作
    int dequeue() {
        if (isEmpty()) {
            cout << "队列为空，无法出队！" << endl;
            return -1; // 返回一个错误标志
        }

        Node* front = rear->next; // 队头节点
        int value = front->data;

        if (rear == front) {
            // 队列中只有一个节点
            rear = nullptr;
        }
        else {
            rear->next = front->next; // 队尾指向新的队头
        }

        delete front;
        return value;
    }
    //打印队列
    void print()//按照顺序打印链表
    {
        Node* p = rear->next;
        
        do{
            cout << p->data << endl;
            p = p->next;

        } while (p != rear->next);
    }

    // 销毁队列
    ~CircularQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// 主函数
int main() {
    CircularQueue queue;
    int choice, value;

    cout << "循环链队列操作菜单：" << endl;
    cout << "1. 入队" << endl;
    cout << "2. 出队" << endl;
    cout << "3. 打印" << endl;
    cout << "4. 退出" << endl;

    while (true) {
        cout << "请输入操作选项：";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "请输入要入队的元素：";
            cin >> value;
            queue.enqueue(value);
            break;
        case 2:
            if (!queue.isEmpty()) {
                cout << "出队元素：" << queue.dequeue() << endl;
            }
            else {
                cout << "队列为空，无法出队！" << endl;
            }
            break;
        case 3:
            queue.print();
            break;
        case 4:
            cout << "退出程序。" << endl;
            return 0;
        default:
            cout << "无效选项，请重新输入！" << endl;
        }
    }

    return 0;
}
