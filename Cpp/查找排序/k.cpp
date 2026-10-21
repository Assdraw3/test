//#include <iostream>
//#include <vector>
//using namespace std;
//
///*-------------------------------------------
//  顺序查找（哨兵设在低端）
//-------------------------------------------*/
//int SeqSearch(vector<int>& a, int key) {
//    int n = a.size() - 1;  // a[0] 为哨兵，实际数据从 a[1] 开始
//    a[0] = key;            // 设置哨兵
//
//    int i = n;
//    while (a[i] != key) {
//        i--;
//    }
//    return i;   // 若等于0则表示查找失败
//}
//
///*-------------------------------------------
//  二叉排序树（BST）
//-------------------------------------------*/
//struct Node {
//    int data;
//    Node* left;
//    Node* right;
//    Node(int d) : data(d), left(nullptr), right(nullptr) {}
//};
//
//void BST_Insert(Node*& root, int x) {
//    if (!root) {
//        root = new Node(x);
//        return;
//    }
//    if (x < root->data) BST_Insert(root->left, x);
//    else BST_Insert(root->right, x);
//}
//
//// 中序遍历输出所有 > x 的值（自动从小到大）
//void PrintGreater(Node* root, int x) {
//    if (!root) return;
//
//    PrintGreater(root->left, x);
//    if (root->data > x) cout << root->data << " ";
//    PrintGreater(root->right, x);
//}
//
//int main() {
//    cout << "===== 顺序查找（哨兵）=====\n";
//    int n;
//    cout << "输入元素个数: ";
//    cin >> n;
//
//    vector<int> a(n + 1);   // 多一个位置放哨兵
//    cout << "输入数组元素:\n";
//    for (int i = 1; i <= n; i++) cin >> a[i];
//
//    int key;
//    cout << "输入要查找的关键字: ";
//    cin >> key;
//
//    int pos = SeqSearch(a, key);
//    if (pos == 0) cout << "未找到\n";
//    else cout << "找到，位置：" << pos << endl;
//
//    cout << "\n===== 二叉排序树（输出 > x）=====\n";
//    int m;
//    cout << "输入 BST 节点个数: ";
//    cin >> m;
//
//    Node* root = nullptr;
//    cout << "输入 BST 的节点值:\n";
//    for (int i = 0; i < m; i++) {
//        int v;
//        cin >> v;
//        BST_Insert(root, v);
//    }
//
//    int x;
//    cout << "输入 x（输出所有大于 x 的值）: ";
//    cin >> x;
//
//    cout << "结果：";
//    PrintGreater(root, x);
//    cout << endl;
//
//    return 0;
//}