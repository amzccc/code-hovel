// 定义栈的数据结构，
// 请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，
// 调用 min、push 及 pop 的时间复杂度都是 O(1)。
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.min();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.min();   --> 返回 -2.

/*
准备两个栈，一个正常存储数据，另一个存储最小值，当存入的数据比当前的栈顶小时就同时放入两个栈，
弹出时若和最小值的栈栈顶相同就一起弹出
*/
#include <stack>

using namespace std;

class MinStack {
public:
    stack<int> mstk;
    stack<int> substk;
    /** initialize your data structure here. */
    MinStack() {
    
    }
    
    void push(int x) {
        mstk.push(x);
        if(substk.empty() || x <= substk.top())
            substk.push(x);
    }
    
    void pop() {
        if(mstk.top() == substk.top())
            substk.pop();
        mstk.pop();
    }
    
    int top() {
        return mstk.top();
    }
    
    int min() {
        return substk.top();
    }
};