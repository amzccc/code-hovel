// 请根据每日 气温 列表 temperatures ，重新生成一个列表，要求其对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/iIQa4I
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int size = temperatures.size();
    vector<int> res(size, 0);
    stack<int> tem;
    for(int i = 0; i < size; i++) {
        while(!tem.empty() && temperatures[i] > temperatures[tem.top()]) {
            res[tem.top()] = i - tem.top();
            tem.pop();
        }
        tem.push(i);
    }
    return res;
}