// 给你一个下标从 0 开始、严格递增 的整数数组 nums 和一个正整数 diff 。如果满足下述全部条件，则三元组 (i, j, k) 就是一个 算术三元组 ：

// i < j < k ，
// nums[j] - nums[i] == diff 且
// nums[k] - nums[j] == diff
// 返回不同 算术三元组 的数目。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/number-of-arithmetic-triplets
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
using namespace std;

int arithmeticTriplets(vector<int>& nums, int diff) {
    int res = 0;
    int size = nums.size();
    int second = 0;
    int third = 0;
    for(int i = 0; i < size - 2; i++) {
        if(second <= i) {
            second = i + 1;
        }
        while(second < size - 1 && nums[second] - nums[i] < diff) {
            second++;
        }
        if(second < size - 1 && nums[second] - nums[i] == diff) {
            if(third <= second) {
                third = second + 1;
            }
            while(third < size && nums[third] - nums[second] < diff) {
                third++;
            }
            if(third < size && nums[third] - nums[second] < diff) {
                res++;
            }
        }
    }
    return res;
}

int main()
{
    vector<int> nums{0,1,4,6,7,10};
    int diff = 3;
    cout << arithmeticTriplets(nums, diff);
}