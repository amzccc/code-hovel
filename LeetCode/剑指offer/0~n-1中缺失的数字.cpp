// 一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
// 在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

//依次比对值和下标是否相同，二分可优化一半时间
#include <vector>
#include <iostream>
using namespace std;

int sub_process(vector<int>& nums, int begin, int end)
{
    int cmp = begin == 0? 0: nums[begin];   
    for(int i = begin; i <= end; i++)
    {
        if(nums[i] != cmp)
            break;
        ++cmp;
    }
    return cmp;
}

int missingNumber(vector<int>& nums)
{   
    int mid = nums.size() / 2;
    int result = 0;
    if(sub_process(nums, 0, mid) < nums[mid])
    {
        result = sub_process(nums, 0, mid);
    }
    else
    {
        result = sub_process(nums, mid, nums.size() - 1);
    }
    return result;
}

//test
int main()
{
    vector<int> a{0};
    cout << missingNumber(a);
}
