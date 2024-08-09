// 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。
// 要求不能创建任何新的节点，只能调整树中节点指针的指向。

#include <vector>
#include <stack>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

Node* treeToDoublyList(Node* root) {
    if(root == nullptr)
        return nullptr;
    vector<Node*> q;
    stack<Node*> path;
    path.push(root);
    Node* cur;
    while(!path.empty()) {
        cur = path.top();
        path.pop();
        if(cur->left) {
            path.push(cur);
            path.push(cur->left);
            cur->left = nullptr;
        }
        else {
            q.push_back(cur);
            if(cur->right) {
                path.push(cur->right);
            }
        }
    }
    for(int i = 0; i < q.size(); i++) {
        if(i == 0) {
            q[i]->left = q.back();
        }
        else {
            q[i]->left = q[i - 1];
        }
        if(i == q.size() - 1)
            q[i]->right = q[0];
        else
            q[i]->right = q[i + 1];
    }
    return q[0];
}

