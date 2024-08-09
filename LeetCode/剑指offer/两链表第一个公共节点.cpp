// 输入两个链表，找出它们的第一个公共节点。

#include <unordered_set>
using namespace std;

class ListNode
{   
public:
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(nullptr){};
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{   
    if(headA ==nullptr || headB == nullptr)
        return nullptr;
    ListNode* A_ptr = headA;
    ListNode* B_ptr = headB;
    unordered_set<ListNode*> myset;
    while(A_ptr != nullptr)
    {
        if(myset.find(A_ptr) != myset.end())
            break;
        myset.insert(A_ptr);
        A_ptr = A_ptr->next;
    }
    while(B_ptr != nullptr)
    {
        if(myset.find(B_ptr) != myset.end())
            return B_ptr;
        B_ptr = B_ptr->next;
    }
    return nullptr;
}


//利用双指针空间复杂度降到O(1)
ListNode *getInter_sectionNode(ListNode *headA, ListNode *headB)
{
    if(headA ==nullptr || headB == nullptr)
        return nullptr;
    ListNode* A_ptr = headA;
    ListNode* B_ptr = headB;
    while(A_ptr != B_ptr)
    {
        A_ptr = A_ptr->next;
        B_ptr = B_ptr->next;
        if(A_ptr == nullptr && B_ptr == nullptr)
            break;
        if(A_ptr == nullptr && B_ptr != nullptr)
            A_ptr = headB;
        if(A_ptr != nullptr && B_ptr == nullptr)
            B_ptr =headA;
    }
    return A_ptr;
}