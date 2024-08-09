// 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，
// 本题从1开始计数，即链表的尾节点是倒数第1个节点。

// 例如，一个链表有 6 个节点，从头节点开始，
// 它们的值依次是 1、2、3、4、5、6。
// 这个链表的倒数第 3 个节点是值为 4 的节点。

#include <iostream>
#include <unordered_map>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next = nullptr;
};


ListNode* getKthFromEnd(ListNode* head, int k)
{
    ListNode *temp = head;
    unordered_map<int, ListNode*> mp;
    int count = 0;
    while(temp != nullptr)
    {
        mp.insert(make_pair(count,temp));
        count++;
        temp = temp->next;
    }
    return mp[mp.size() - k];
}