// 给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。
#include <vector>
using namespace std;

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int mul = 1;
    int res = 0;
    int size = nums.size();
    int index = 0;
    for(int i = 0; i < size; i++) {
        mul *= nums[i];
        while(index <= i && mul >= k) {
            mul /= nums[index];
            index++;
        }
        res += i - index + 1;
    }
    return res;
}
