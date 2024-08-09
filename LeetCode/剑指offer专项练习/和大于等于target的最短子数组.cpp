// 给定一个含有 n 个正整数的数组和一个正整数 target 。

// 找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，
// 并返回其长度。如果不存在符合条件的子数组，返回 0 。

#include <vector>
using namespace std;

int minSubArrayLen(int target, vector<int>& nums) {
    int res = nums.size() + 1;
    int l = 0;
    int r = 0;
    int sum = 0;
    while(r < nums.size()) {
        sum += nums[r];
        r++;
        while(sum >= target && l < r) {
            res = (res < r - l + 1? res: r - l);
            sum -= nums[l];
            l++;
        }
    }
    return (res == nums.size() + 1? 0: res);
}