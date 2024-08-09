//输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）
// 输入：head = [1,3,2]
// 输出：[2,3,1]
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class ListNode
{   
public:
    int value;
    ListNode *next;
    ListNode(int x): value(x),next(nullptr){};
};

class Solution
{
public:
    vector<int> reversePrint(ListNode* head)
    {
        stack<int> mystk;
        do
        {
            mystk.push(head->value);
            head = head->next;
        }
        while(head != nullptr);
        vector<int> vec;
        while(!mystk.empty())
        {
            vec.push_back(mystk.top());
            mystk.pop();
        }
        return vec;
    }
};

int main()
{
    ListNode l1(1), l2(3), l3(2), l0(0);
    l1.next = &l2;
    l2.next = &l3;
    l0.next = &l1;
    Solution s;
    vector<int> vec1;
    vec1 = s.reversePrint(l0.next);
    for (auto it: vec1)
        cout << it << " ";
    cout << endl;
}