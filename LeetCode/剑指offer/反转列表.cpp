// 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

#include <iostream>
#include <unordered_map>
using namespace std;

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){};
};

ListNode* reverseList(ListNode* head)
{
    ListNode *temp = head;
    unordered_map<int, ListNode*> mp; 
    int i = 0;
    while(temp != nullptr)
    {
        mp.insert(make_pair(i++, temp));
        temp = temp->next;
    }
    temp = mp[i - 1];
    while(i >= 0)
    {
        i--;
        
        if(i == 0)
            mp[i]->next = nullptr;
        else if((mp[i] != nullptr) && (mp[i - 1] != nullptr))
        {
            mp[i]->next = mp[i - 1];
        }
    }
    return temp;
} //不好，map需要O(N)的额外空间复杂度，时间复杂度也是O(N)

//利用双指针暂存前一个节点
ListNode* reverse_List(ListNode* head)
{
    ListNode *cur = head, *pre = nullptr;
    while(cur != nullptr) 
    {
        ListNode* tmp = cur->next; // 暂存后继节点 cur.next
        cur->next = pre;           // 修改 next 引用指向
        pre = cur;                 // pre 暂存 cur
        cur = tmp;                 // cur 访问下一节点
    }
    return pre;
}