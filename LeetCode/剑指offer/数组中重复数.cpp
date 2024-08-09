// 找出数组中重复的数字。
// 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
// 数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
// 输入：
// [2, 3, 1, 0, 2, 5, 3]
// 输出：2 或 3 
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


class Solution
{
public:
    int findRepeatNumber(vector<int>& nums)
    {
        unordered_set<int> myset{};
        for(int it: nums)
        {
            if(myset.find(it) != myset.end())
            {
                return it;
            }    
            myset.insert(it);
        }
    return 0;
    }
};

int main()
{
    Solution s;
    int a = 0;
    vector<int> vec{2, 3, 1, 0, 2, 5, 3};
    a = s.findRepeatNumber(vec);
    cout << a;
    return 0;
}
