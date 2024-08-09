// 用两个栈实现一个队列。队列的声明如下，
// 请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。
// (若队列中没有元素，deleteHead 操作返回 -1 )
// 输入：
// ["CQueue","appendTail","deleteHead","deleteHead"]
// [[],[3],[],[]]
// 输出：[null,null,3,-1]

#include <stack>
using namespace std;

class CQueue {
public:
    stack<int> stk1;
    stack<int> stk2;
    CQueue() {

    }
    
    void appendTail(int value) {
        stk1.push(value);
    }
    
    int deleteHead() {
            if(stk2.empty())
            {
                while(!stk1.empty())
                {
                    stk2.push(stk1.top());
                    stk1.pop();
                }
            }
            if(stk2.empty())
                return -1;
            else
            {
                int result = -1;
                result = stk2.top();
                stk2.pop();
                return result;
            }
    }
};