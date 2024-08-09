// 多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，可能指向单独的双向链表。
// 这些子列表也可能会有一个或多个自己的子项，依此类推，生成多级数据结构，如下面的示例所示。
// 给定位于列表第一级的头节点，请扁平化列表，即将这样的多级双向链表展平成普通的双向链表，使所有结点出现在单级双链表中。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/Qv1Da2
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <stack>
#include <iostream>
#include <vector>
using namespace std;


class Node 
{
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

Node* flatten(Node* head) {
    stack<Node*> store;
    Node* res = head;
    while(head != nullptr) {
        if(head->child != nullptr) {
            if (head->next != nullptr)
                store.push(head->next);
            head->next = head->child;
            head->child = nullptr;
            head->next->prev = head;
        }
        if(head->next == nullptr) {
            if (!store.empty()) {
                head->next = store.top();
                store.pop();
                head->next->prev = head;
            }
        }
        head = head->next;
    }
    return res;
}

int main()
{
    vector<Node*> vec;
    Node* temp;
    temp->val = 42;
    temp->next = nullptr;
    temp->prev = nullptr;
    temp->child = nullptr;
    for(int i = 0; i < 12; i++) {
        vec.push_back(temp);
    }
    for(auto it = vec.begin(); it != vec.end(); it++) {
        if(it != vec.begin()) {
            (*it)->prev = *(it - 1);
        }
        if(it != (vec.end() - 1)) {
            (*it)->next = *(it + 1);
        }
    }
    vec[2]->child = vec[7];
    vec[7]->child = vec[10];
    vec[5]->next = nullptr;
    vec[6]->prev = nullptr;
    vec[9]->next = nullptr;
    vec[10]->prev = nullptr;
    flatten(vec[0]);
}