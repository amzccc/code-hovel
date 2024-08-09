// 请实现 copyRandomList 函数，复制一个复杂链表。
// 在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，
// 还有一个 random 指针指向链表中的任意节点或者 null。

#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* copyRandomList(Node* head) {
    if(head == nullptr)
        return nullptr;
    unordered_map<Node*, Node*> mp;
    
    if(!mp.count(head)) {
        mp[head] = new Node (head->val);
        mp[head]->next = copyRandomList(head->next);
        mp[head]->random = copyRandomList(head->random);
    }
    return mp[head];
}