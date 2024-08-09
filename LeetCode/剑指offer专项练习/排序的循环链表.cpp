// 给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal ，使这个列表仍然是循环升序的。

// 给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。

// 如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。

// 如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/4ueAj6
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <limits>
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

Node* insert(Node* head, int insertVal) {
    Node* ins = new Node(insertVal);
    if(head == nullptr) {
        ins->next = ins;
        return ins;
    }
    else {
        Node* cur = head->next;
        Node* min = head;
        Node* max = head;
        while(cur != head) {
            if(cur->val < min->val)
                min = cur;
            if(cur->val >= max->val)
                max = cur;
            cur = cur->next;
        }
        if(min == max) {
            ins->next = head->next;
            head->next = ins;
        }
        else if(min->val >= insertVal) {
            ins->next = min;
            max->next = ins;
        }
        else if(max->val <= insertVal){
            ins->next = min;
            max->next = ins;
        }
        else {
            cur = min;
            while(cur != max) {
                if(cur->next->val > insertVal) {
                    ins->next = cur->next;
                    cur->next = ins;
                    break;
                }
                cur = cur->next;
            }
        }
    }
    return head;
}
