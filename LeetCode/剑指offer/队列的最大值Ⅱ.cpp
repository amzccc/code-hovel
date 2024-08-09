// 请定义一个队列并实现函数 max_value 得到队列里的最大值，
// 要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。

// 若队列为空，pop_front 和 max_value 需要返回 -1
#include <queue>
#include <deque>
using namespace std;

class MaxQueue {
public:
    MaxQueue() {
    }
    
    int max_value() {
        if(q.empty())
            return -1;
        else 
            return max.front();
    }
    
    void push_back(int value) {
            q.push(value);
            while(!max.empty() && max.back() < value) {
                max.pop_back();
            }
            max.push_back(value);
    }

    int pop_front() {
        if(q.empty())
            return -1;
        else {
            if(max.front() == q.front())
                max.pop_front();
            int temp = q.front();
            q.pop();
            return temp;
        }
    }
private:
    queue<int> q;
    deque<int> max;
};