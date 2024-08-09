// 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
// 假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，
// 序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，
// 但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stack>
using namespace std;

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    if(pushed.empty() || pushed.size() < 3)
        return true;
    unordered_map<int, int> mp;
    int index = 0;
    int push_pos = 0;
    for(int i = 0; i < pushed.size(); i++) {
        //second记录压入的顺序
        mp.insert(make_pair(pushed[i], i));
    }
    //index表示当前弹出的数之前已经弹出了多少数,也就是弹出顺序
    while(index < popped.size()) {
        push_pos = mp.find(popped[index])->second;
        //表示当前数弹出之后应该有多少数的压入顺序是必须逆序排列的，等于当前数的位置-已经弹出的个数   
        while(index < push_pos) {
            if(mp.find(popped[index + 1])->second > push_pos) {
                break;
            }
            else if(mp.find(popped[index])->second < mp.find(popped[index + 1])->second)
                return false;
            else 
                index++;
        }
        index++;
    }
    return true;
}


//模拟法
bool VSS(vector<int>& pushed, vector<int>& popped) {
    stack<int>  stk;
    int ptr1 = 0;
    int ptr2 = 0;
    while(ptr1 < pushed.size()) {
        stk.push(pushed[ptr1]);
        ptr1++;
        while(!stk.empty() && stk.top() == popped[ptr2]) {
            stk.pop();
            ptr2++;
        }
    }
    return stk.empty();
}

int main()
{   
    vector<int> v1{2,1,0};
    vector<int> v2{1,2,0};
    cout << validateStackSequences(v1, v2);
}