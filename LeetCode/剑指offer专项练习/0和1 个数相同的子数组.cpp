// 给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。
#include <vector>
#include <unordered_map>
using namespace std;

int findMaxLength(vector<int>& nums) {  
    int res = 0;
    unordered_map<int, int> mp;     //把0看作-1，结果就等于和为0的子数组
    int sum = 0;
    mp[0] = -1;
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] == 0)
            sum--;
        else 
            sum++;
        if(mp.find(sum) != mp.end())
            res = max(res, i - mp[sum]);
        else
            mp.insert(make_pair(sum, i));
    }
    return res;
}