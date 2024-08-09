// 给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

// 返回删除后的链表的头节点。
#include <iostream>
using namespace std;

struct ListNode
{
    int value;
    ListNode *next = nullptr;
};

ListNode* deleteNode(ListNode* head, int val)
{   
    if(head->value == val)
        head = head->next;
    ListNode *temp = head;
    while((temp != nullptr) && (temp->next != nullptr))  //要先判断当前指针是否为空，再判断next，否则可能编译不通过
    {
        if(temp->next->value == val)
            temp->next = temp->next->next;
        temp = temp->next;
    }
    return head;
}
