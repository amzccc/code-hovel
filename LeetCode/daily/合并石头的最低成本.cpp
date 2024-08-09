// 有 N 堆石头排成一排，第 i 堆中有 stones[i] 块石头。

// 每次移动（move）需要将连续的 K 堆石头合并为一堆，而这个移动的成本为这 K 堆石头的总数。

// 找出把所有石头合并成一堆的最低成本。如果不可能，返回 -1 。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/minimum-cost-to-merge-stones
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <queue>
#include <iostream>
using namespace std;

int mergeStones(vector<int>& stones, int k) {
    const size_t size = stones.size();
    int r = size % (k-1);
    if(k != 2) {
        int r = size % (k-1);
        if(k != 2 && r != 1) {
            return -1;
        }
    }

    int res = 0;
    
    return res;
}

int main()
{
    vector<int> vec{3, 2, 4, 1};
    cout << mergeStones(vec, 2) << endl;
}