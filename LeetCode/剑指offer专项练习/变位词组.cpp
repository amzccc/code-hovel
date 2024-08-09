// 给定一个字符串数组 strs ，将 变位词 组合在一起。 可以按任意顺序返回结果列表。

// 注意：若两个字符串中每个字符出现的次数都相同，则称它们互为变位词。

#include <unordered_map>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [fn = hash<int>{}] (const array<int, 26>& arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string& str: strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode.cn/problems/sfvd7V/solution/bian-wei-ci-zu-by-leetcode-solution-5wnz/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

