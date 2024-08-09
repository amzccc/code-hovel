// 据 逆波兰表示法，求该后缀表达式的计算结果。

// 有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

#include <vector>
#include <string>
#include <stack>
using namespace std;

int evalRPN(vector<string>& tokens) {
    stack<int> res;
    int a, b;
    for(string &s: tokens) {
        if(s == "+") {
            b = res.top();
            res.pop();
            a = res.top();
            res.pop();
            res.push(a + b);
        }
        else if(s == "-") {
            b = res.top();
            res.pop();
            a = res.top();
            res.pop();
            res.push(a - b);
        }
        else if(s == "*") {
            b = res.top();
            res.pop();
            a = res.top();
            res.pop();
            res.push(a * b);
        }
        else if(s == "/") {
            b = res.top();
            res.pop();
            a = res.top();
            res.pop();
            res.push(a / b);
        }
        else {
            res.push(stoi(s));
        }
    }
    return res.top();
}