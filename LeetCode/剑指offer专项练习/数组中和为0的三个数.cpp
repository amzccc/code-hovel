// 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素a，b，c，使得 a + b + c = 0 ？
// 请找出所有和为 0 且 不重复 的三元组。

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <algorithm>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    if(nums.size() < 3)
        return {};
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for(int i = 0; i < nums.size() - 2; i++) {
        if(i > 0 && nums[i] == nums[i - 1])
            continue;
        int k = nums.size() - 1;
        int target = -nums[i];
        for(int j = i + 1; j < nums.size() - 1; j++) {
            if(j > i + 1 && nums[j] == nums[j - 1])
                continue;
            while(j < k && nums[j] + nums[k] > target)
                k--;
            if(j == k)
                break;
            if(nums[j] + nums[k] == target)
                res.push_back({nums[i], nums[j], nums[k]});
        }
    }
    return res;
}



class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }
};
