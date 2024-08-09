// 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。


#include <iostream>
#include<unordered_map>
using namespace std;

class ListNode
{
public:
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr){};
};
/*无脑哈希表，主要建表太费时间和空间
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    unordered_map<int, ListNode*> mp;
    ListNode* l1_ptr = l1;
    ListNode* l2_ptr = l2;
    int num = 0;
    while ((l1_ptr != nullptr) && (l2_ptr != nullptr))
    {
        if(l1_ptr->val <= l2_ptr->val)
        {    
            mp.insert(make_pair(num++, l1_ptr));
            l1_ptr = l1_ptr->next;
        }
        else
        {
            mp.insert(make_pair(num++, l2_ptr));
            l2_ptr = l2_ptr->next;
        }
    }
    while(l1_ptr != nullptr)
    {
        mp.insert(make_pair(num++, l1_ptr));
        l1_ptr = l1_ptr->next;
    }
    while(l2_ptr != nullptr)
    {
        mp[num++] = l2_ptr;
        l2_ptr = l2_ptr->next;
    }
    for(int i = 0; i < mp.size() - 1; i++)
        mp[i]->next = mp[i + 1];
    return mp[0];
}
*/

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode *res = new ListNode(0), *p = res;
        while(l1 && l2 )
        {
            l1->val < l2->val ? (p->next = l1,l1 = l1->next) : (p->next = l2, l2 = l2->next);
            p = p->next;              
        }
        p->next = l1 ? l1 : l2;
        return res->next;
}