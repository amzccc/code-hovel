// 给定两个 非空链表 l1和 l2 来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

// 可以假设除了数字 0 之外，这两个数字都不会以零开头。

#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    vector<ListNode*> v1;
    vector<ListNode*> v2;
    while(l1 != nullptr) {
        v1.push_back(l1);
        l1 = l1->next;
    }
    while(l2 != nullptr) {
        v2.push_back(l2);
        l2 = l2->next;
    }
    auto it1 = v1.rbegin();
    auto it2 = v2.rbegin();
    unsigned flag = 0;
    int sum;
    while(it1 != v1.rend() && it2 != v2.rend()) {
        sum = (*it1)->val + (*it2)->val + flag;
        (*it1)->val = sum % 10;
        flag = sum / 10;
        it1++;
        it2++;
    }
    if(it1 == v1.rend()) {
        if(it2 == v2.rend()) {
            if(flag == 0)
                return v1[0];
            else {
                ListNode* head = new ListNode(1, v1[0]);
                return head;
            }
        }
        else {
            (*it2)->next = (*(--it1));
            while(it2 != v2.rend()) {
                sum = (*it2)->val + flag;
                (*it2)->val = sum % 10;
                flag = sum / 10;
                it2++;
            }
            if(flag == 0)
                return v2[0];
            else {
                ListNode* head = new ListNode(1, v2[0]);
                return head;
            }
        }
    }
    else {
        while(it1 != v1.rend()) {
            sum = (*it1)->val + flag;
            (*it1)->val = sum % 10;
            flag = sum /10;
            it1++;
        }
        if(flag == 1) {
            ListNode* head = new ListNode(1, v1[0]);
            return head;
        }
    }
    return v1[0];
}