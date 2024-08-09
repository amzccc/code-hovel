// 给定一个单链表 L 的头节点 head ，单链表 L 表示为：

//  L0 → L1 → … → Ln-1 → Ln 
// 请将其重新排列后变为：

// L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …

// 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换.

#include <stack>
#include <queue>
using namespace std;

struct ListNode {
int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void reorderList(ListNode* head) {
    queue<ListNode*> q;
    stack<ListNode*> st;
    while(head != nullptr) {
        q.push(head);
        st.push(head);
        head = head->next;
    }
    bool flag = 0;
    while(q.front() != st.top()) {
        if(flag == 0) {
            q.front()->next = st.top();
            q.pop();
            flag = 1;
        }
        else {
            st.top()->next = q.front();
            st.pop();
            flag = 0;
        }
    }
    q.front()->next = nullptr;
}