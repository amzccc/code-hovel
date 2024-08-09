// 给定一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next; ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* removeNthFromEnd(ListNode* head, int n) {
    vector<ListNode*> path;
    while(head != nullptr) {
        path.push_back(head);
        head = head->next;
    }
    int del = path.size() - n;
    if(del == 0)
        return path[0]->next;
    else {
        path[del - 1]->next = path[del]->next;
    }
    return path[0];
}