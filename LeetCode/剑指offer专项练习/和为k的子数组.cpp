// 给定一个整数数组和一个整数 k ，请找到该数组中和为 k 的连续子数组的个数。
#include <vector>
#include <unordered_map>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;     //key为前缀和，value为该前缀和出现的次数
    int sum = 0;
    int res = 0;
    mp.insert(make_pair(sum, 1));
    for(auto &it: nums) {
        sum += it;
        if(mp.find(sum - k) != mp.end())
            res += mp[(sum - k)];
        mp[sum]++;
    }
    return res;
}   