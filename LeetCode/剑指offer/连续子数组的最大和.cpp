// 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。
// 求所有子数组的和的最大值。
// 要求时间复杂度为O(n)。
#include <vector>
#include <iostream>
using namespace std;

int maxSubArray(vector<int>& nums){
    if(nums.size() == 0)
        return 0;
    if(nums.size() == 1)
        return nums[0];
    int max = nums[0];
    int sum = 0;
    for(int i = 0; i <nums.size(); i++)
    {   
        sum += nums[i];
        if(max < sum)
            max = sum;
        if(nums[i] < 0)
        {
            if(sum < 0)
                sum = 0;
        }
        
    }
    return max;
}

//test
int main()
{
    vector<int> vec{-2, -1};
    cout << maxSubArray(vec);
}